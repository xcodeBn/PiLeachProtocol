#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/routing/leach/Leach.h"
#include "inet/physicallayer/wireless/common/contract/packetlevel/SignalTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/power/storage/SimpleEpEnergyStorage.h"
#include "inet/mobility/contract/IMobility.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/networklayer/ipv4/Ipv4InterfaceData.h"
#include <list>
#include <vector>
#include <algorithm>
#include <ctime>
#include <functional>
#include <iostream>
#include <fstream>
using namespace power;
namespace inet {

Define_Module(Leach);

Leach::ForwardEntry::~ForwardEntry() {
    if (this->event != nullptr) delete this->event;
    if (this->hello != nullptr) delete this->hello;
}

Leach::Leach() : event(nullptr), forwardEntry(nullptr) {}

Leach::~Leach() {
    stop();
    delete event;
}

void Leach::initialize(int stage) {
    RoutingProtocolBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        sequencenumber = 0;
        host = getContainingNode(this);
        ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);

        clusterHeadPercentage = par("clusterHeadPercentage");
        numNodes = par("numNodes");

        dataPktSent = 0;
        dataPktReceived = 0;
        dataPktReceivedVerf = 0;
        controlPktSent = 0;
        controlPktReceived = 0;
        bsPktSent = 0;
        totalChCount = 0;

        dataPktSendDelay = uniform(0, 10);
        CHPktSendDelay = par("CHPktSendDelay");
        roundDuration = par("roundDuration");

        TDMADelayCounter = 1;

        helloInterval = par("helloInterval");
        event = new cMessage("event");

        WATCH(threshold);
        WATCH(round);
        WATCH(totalChCount);

        round = 0;
        weight = 0;
        wasCH = false;
        leachState = nch;
        roundStartTime = 0; // Initialize member variable

        // Reserve memory for vectors
        nodeMemory.reserve(numNodes);
        nodeCHMemory.reserve(numNodes);
        extractedTDMASchedule.reserve(numNodes);
    } else if (stage == INITSTAGE_ROUTING_PROTOCOLS) {
        registerService(Protocol::manet, gate("ipOut"), gate("ipIn"));
        registerProtocol(Protocol::manet, gate("ipOut"), gate("ipIn"));
    }
}
void Leach::start() {
    addToNodePosList();

    int num_802154 = 0;
    NetworkInterface *ie;
    NetworkInterface *i_face;
    const char *name;
    broadcastDelay = &par("broadcastDelay");
    for (int i = 0; i < ift->getNumInterfaces(); i++) {
        ie = ift->getInterface(i);
        name = ie->getInterfaceName();
        if (strstr(name, "wlan") != nullptr) {
            i_face = ie;
            num_802154++;
            interfaceId = i;
        }
    }

    if (num_802154 == 1) {
        interface80211ptr = i_face;
    } else {
        throw cRuntimeError("LEACH has found %i 802.15.4 interfaces", num_802154);
    }
    interface80211ptr->getProtocolDataForUpdate<Ipv4InterfaceData>()->joinMulticastGroup(Ipv4Address::LL_MANET_ROUTERS);

    event->setKind(SELF);
    scheduleAt(simTime() + uniform(0.0, par("maxVariance").doubleValue()), event);
}

void Leach::stop() {
    cancelEvent(event);
    nodeMemory.clear();
    nodeCHMemory.clear();
    extractedTDMASchedule.clear();
    TDMADelayCounter = 1;
    setLeachState(nch);
}

void Leach::handleMessageWhenUp(cMessage *msg) {
    if (msg->isSelfMessage()) {
        // Timeout check for CHs
                if (leachState == ch && simTime() >= roundStartTime + roundDuration) {
                    EV << "Node " << host->getFullName() << " CH timeout, reverting to NCH" << endl;
                    setLeachState(nch);
                }
                // Only revert if it's time for a new election
                else if (msg->getKind() == SELF && leachState == ch) {
                    setLeachState(nch);
                }

        double randNo = uniform(0, 1);
        threshold = generateThresholdValue(round);

        if (randNo < threshold && !wasCH) {
            weight++;
            setLeachState(ch);
            wasCH = true;
            handleSelfMessage(msg);
        }

        round++;
        int intervalLength = 1.0 / clusterHeadPercentage;
        if (fmod(round, intervalLength) == 0) {
            wasCH = false;
            nodeMemory.clear();
            nodeCHMemory.clear();
            extractedTDMASchedule.clear();
            TDMADelayCounter = 1;
        }

        // Log CH count for debugging
                static int chCount = 0;
                if (leachState == ch) chCount++;

                // Move the reset to the start of a new round
                if (fmod(round, intervalLength) == 0) {
                    EV << "End of interval, resetting CH count from " << chCount << endl;
                    chCount = 0;
                }

                EV << "Round " << round << ": Total CHs = " << chCount << " at " << simTime() << endl;

        roundStartTime = simTime();
        event->setKind(SELF);
        scheduleAt(simTime() + roundDuration, event);
    } else if (check_and_cast<Packet *>(msg)->getTag<PacketProtocolTag>()->getProtocol() == &Protocol::manet) {
        processMessage(msg);
    } else {
        EV_ERROR << "Message Not Supported:" << msg->getName() << simTime() << endl;
        //throw cRuntimeError("Message not supported %s", msg->getName());
    }
    refreshDisplay();
}

void Leach::handleSelfMessage(cMessage *msg) {
    if (msg == event && event->getKind() == SELF) {
        auto ctrlPkt = makeShared<LeachControlPkt>();
        ctrlPkt->setPacketType(CH);
        Ipv4Address source = interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress();
        ctrlPkt->setChunkLength(b(128));
        ctrlPkt->setSrcAddress(source);

        auto packet = new Packet("LEACHControlPkt", ctrlPkt);
        auto addressReq = packet->addTag<L3AddressReq>();
        addressReq->setDestAddress(Ipv4Address(255, 255, 255, 255));
        addressReq->setSrcAddress(source);
        packet->addTag<InterfaceReq>()->setInterfaceId(interface80211ptr->getInterfaceId());
        packet->addTag<PacketProtocolTag>()->setProtocol(&Protocol::manet);
        packet->addTag<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);

        send(packet, "ipOut");
        addToEventLog(source, Ipv4Address(255, 255, 255, 255), "CTRL", "SENT");
        controlPktSent++;
        bubble("Sending new enrolment message");
    } else {
        delete msg;
    }
}

void Leach::processMessage(cMessage *msg) {
    Ipv4Address selfAddr = interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress();
    auto receivedCtrlPkt = staticPtrCast<LeachControlPkt>(check_and_cast<Packet *>(msg)->peekData<LeachControlPkt>()->dupShared());
    Packet *receivedPkt = check_and_cast<Packet *>(msg);
    auto& leachControlPkt = receivedPkt->popAtFront<LeachControlPkt>();

    auto packetType = leachControlPkt->getPacketType();

    if (msg->arrivedOn("ipIn")) {
        if (packetType == CH) {
            controlPktReceived++;
            Ipv4Address CHAddr = receivedCtrlPkt->getSrcAddress();
            addToEventLog(CHAddr, selfAddr, "CTRL", "REC");

            auto signalPowerInd = receivedPkt->getTag<SignalPowerInd>();
            double rxPower = signalPowerInd->getPower().get();

            addToNodeMemory(selfAddr, CHAddr, rxPower);
            sendAckToCH(selfAddr, CHAddr);
        } else if (packetType == ACK && leachState == ch) {
            Ipv4Address nodeAddr = receivedCtrlPkt->getSrcAddress();
            addToEventLog(nodeAddr, selfAddr, "ACK", "REC");

            addToNodeCHMemory(nodeAddr);
            EV << "CH " << host->getFullName() << " nodeCHMemory size: " << nodeCHMemory.size() << endl;
            if (nodeCHMemory.size() >= 1) { // Lowered threshold
                sendSchToNCH(selfAddr);
            }
        } else if (packetType == SCH) {
            Ipv4Address CHAddr = receivedCtrlPkt->getSrcAddress();
            addToEventLog(CHAddr, selfAddr, "SCH", "REC");

            int scheduleArraySize = receivedCtrlPkt->getScheduleArraySize();
            for (int counter = 0; counter < scheduleArraySize; counter++) {
                ScheduleEntry tempScheduleEntry = receivedCtrlPkt->getSchedule(counter);
                TDMAScheduleEntry extractedTDMAScheduleEntry;
                extractedTDMAScheduleEntry.nodeAddress = tempScheduleEntry.getNodeAddress();
                extractedTDMAScheduleEntry.TDMAdelay = tempScheduleEntry.getTDMAdelay();
                extractedTDMASchedule.push_back(extractedTDMAScheduleEntry);
            }

            double receivedTDMADelay = -1;
            for (auto& it : extractedTDMASchedule) {
                if (it.nodeAddress == selfAddr) {
                    receivedTDMADelay = it.TDMAdelay;
                    break;
                }
            }

            if (receivedTDMADelay > -1) {
                sendDataToCH(selfAddr, CHAddr, receivedTDMADelay);
            }
        } else if (packetType == DATA) {
            Ipv4Address NCHAddr = receivedCtrlPkt->getSrcAddress();
            addToEventLog(NCHAddr, selfAddr, "DATA", "REC");
            std::string fingerprint = receivedCtrlPkt->getFingerprint();

            if (checkFingerprint(fingerprint)) {
                dataPktReceivedVerf++;
            }
            dataPktReceived++;
            sendDataToBS(selfAddr, fingerprint);
        } else if (packetType == BS) {
            delete msg;
        }
    } else {
        throw cRuntimeError("Message arrived on unknown gate %s", msg->getArrivalGate()->getName());
    }
}

void Leach::handleStopOperation(LifecycleOperation *operation) {
    cancelEvent(event);
}

void Leach::handleCrashOperation(LifecycleOperation *operation) {
    cancelEvent(event);
}

double Leach::generateThresholdValue(int round) {
    int intervalLength = 1.0 / clusterHeadPercentage;
    double thresholdVal = clusterHeadPercentage / (1 - clusterHeadPercentage * fmod(round, intervalLength));
    if (thresholdVal >= 1) {
        round = 0;
    }
    return thresholdVal;
}

// Add checks when adding elements:
void Leach::addToNodeMemory(Ipv4Address nodeAddr, Ipv4Address CHAddr, double energy) {
    if (!isCHAddedInMemory(CHAddr)) {
        if (nodeMemory.size() >= nodeMemory.capacity()) {
            EV << "Warning: nodeMemory exceeding reserved capacity" << endl;
        }
        nodeMemoryObject node;
        node.nodeAddr = nodeAddr;
        node.CHAddr = CHAddr;
        node.energy = energy;
        nodeMemory.push_back(node);
    }
}

void Leach::addToNodeCHMemory(Ipv4Address NCHAddr) {
    if (!isNCHAddedInCHMemory(NCHAddr)) {
        TDMAScheduleEntry scheduleEntry;
        scheduleEntry.nodeAddress = NCHAddr;
        scheduleEntry.TDMAdelay = TDMADelayCounter;
        nodeCHMemory.push_back(scheduleEntry);
        TDMADelayCounter++;
    }
}

bool Leach::isCHAddedInMemory(Ipv4Address CHAddr) {
    for (auto& it : nodeMemory) {
        if (it.CHAddr == CHAddr) return true;
    }
    return false;
}

bool Leach::isNCHAddedInCHMemory(Ipv4Address NCHAddr) {
    for (auto& it : nodeCHMemory) {
        if (it.nodeAddress == NCHAddr) return true;
    }
    return false;
}

void Leach::generateTDMASchedule() {
    // Clear previous schedule
    nodeCHMemory.clear();
    TDMADelayCounter = 1.0;

    // Get all nodes that have acknowledged this CH
    for (auto& node : nodeMemory) {
        if (node.CHAddr == interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress()) {
            TDMAScheduleEntry scheduleEntry;
            scheduleEntry.nodeAddress = node.nodeAddr;
            scheduleEntry.TDMAdelay = TDMADelayCounter;
            nodeCHMemory.push_back(scheduleEntry);
            TDMADelayCounter++;
        }
    }

    EV << "Generated TDMA schedule with " << nodeCHMemory.size() << " slots" << endl;
}

void Leach::setLeachState(LeachState ls) {
    EV << "Node " << host->getFullName() << " state: "
       << (leachState == ch ? "CH" : "NCH") << " -> " << (ls == ch ? "CH" : "NCH")
       << " at " << simTime() << endl;
    leachState = ls;
    refreshDisplay();
}

void Leach::sendAckToCH(Ipv4Address nodeAddr, Ipv4Address CHAddr) {
    auto ackPkt = makeShared<LeachAckPkt>();
    ackPkt->setPacketType(ACK);
    ackPkt->setChunkLength(b(128));
    ackPkt->setSrcAddress(nodeAddr);

    auto ackPacket = new Packet("LeachAckPkt", ackPkt);
    auto addressReq = ackPacket->addTag<L3AddressReq>();
    addressReq->setDestAddress(getIdealCH(nodeAddr));
    addressReq->setSrcAddress(nodeAddr);
    ackPacket->addTag<InterfaceReq>()->setInterfaceId(interface80211ptr->getInterfaceId());
    ackPacket->addTag<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    ackPacket->addTag<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);

    send(ackPacket, "ipOut");
    addToEventLog(nodeAddr, getIdealCH(nodeAddr), "ACK", "SENT");
}

void Leach::sendSchToNCH(Ipv4Address selfAddr) {
    auto schedulePkt = makeShared<LeachSchedulePkt>();
    schedulePkt->setPacketType(SCH);
    schedulePkt->setChunkLength(b(128));
    schedulePkt->setSrcAddress(selfAddr);

    for (auto& it : nodeCHMemory) {
        ScheduleEntry scheduleEntry;
        scheduleEntry.setNodeAddress(it.nodeAddress);
        scheduleEntry.setTDMAdelay(it.TDMAdelay);
        schedulePkt->appendSchedule(scheduleEntry);
    }

    auto schedulePacket = new Packet("LeachSchedulePkt", schedulePkt);
    auto scheduleReq = schedulePacket->addTag<L3AddressReq>();
    scheduleReq->setDestAddress(Ipv4Address(255, 255, 255, 255));
    scheduleReq->setSrcAddress(selfAddr);
    schedulePacket->addTag<InterfaceReq>()->setInterfaceId(interface80211ptr->getInterfaceId());
    schedulePacket->addTag<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    schedulePacket->addTag<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);

    send(schedulePacket, "ipOut");
    addToEventLog(selfAddr, Ipv4Address(255, 255, 255, 255), "SCH", "SENT");
}

void Leach::sendDataToCH(Ipv4Address nodeAddr, Ipv4Address CHAddr, double TDMAslot) {
    auto dataPkt = makeShared<LeachDataPkt>();
    dataPkt->setPacketType(DATA);
    double temperature = uniform(0, 1);
    double humidity = uniform(0, 1);
    std::string fingerprint = resolveFingerprint(nodeAddr, getIdealCH(nodeAddr));

    dataPkt->setChunkLength(b(128));
    dataPkt->setTemperature(temperature);
    dataPkt->setHumidity(humidity);
    dataPkt->setSrcAddress(nodeAddr);
    dataPkt->setFingerprint(fingerprint.c_str());
    addToPacketLog(fingerprint);

    auto dataPacket = new Packet("LEACHDataPkt", dataPkt);
    auto addressReq = dataPacket->addTag<L3AddressReq>();
    addressReq->setDestAddress(getIdealCH(nodeAddr));
    addressReq->setSrcAddress(nodeAddr);
    dataPacket->addTag<InterfaceReq>()->setInterfaceId(interface80211ptr->getInterfaceId());
    dataPacket->addTag<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    dataPacket->addTag<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);

    sendDelayed(dataPacket, TDMAslot, "ipOut");
    addToEventLog(nodeAddr, getIdealCH(nodeAddr), "DATA", "SENT");
    dataPktSent++;
}

void Leach::sendDataToBS(Ipv4Address CHAddr, std::string fingerprint) {
    auto bsPkt = makeShared<LeachBSPkt>();
    bsPkt->setPacketType(BS);
    bsPkt->setChunkLength(b(128));
    bsPkt->setCHAddr(CHAddr);
    bsPkt->setFingerprint(fingerprint.c_str());

    auto bsPacket = new Packet("LEACHBsPkt", bsPkt);
    auto addressReq = bsPacket->addTag<L3AddressReq>();
    addressReq->setDestAddress(Ipv4Address(10, 0, 0, 1));
    addressReq->setSrcAddress(CHAddr);
    bsPacket->addTag<InterfaceReq>()->setInterfaceId(interface80211ptr->getInterfaceId());
    bsPacket->addTag<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    bsPacket->addTag<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);

    send(bsPacket, "ipOut");
    bsPktSent++;
    setLeachState(nch);
}

Ipv4Address Leach::getIdealCH(Ipv4Address nodeAddr) {
    Ipv4Address tempIdealCHAddr;
    double tempRxPower = -1.0;  // Set to negative to detect if no CH found

    for (auto& it : nodeMemory) {
        if (it.nodeAddr == nodeAddr && it.energy > tempRxPower) {
            tempRxPower = it.energy;
            tempIdealCHAddr = it.CHAddr;
        }
    }

    if (tempRxPower < 0) {
        EV << "Warning: No CH found for node " << nodeAddr.str() << endl;
        // Return a default or broadcast address
        return Ipv4Address(255, 255, 255, 255);
    }

    return tempIdealCHAddr;
}

std::string Leach::resolveFingerprint(Ipv4Address nodeAddr, Ipv4Address CHAddr) {
    std::string CHAddrResolved = std::to_string(CHAddr.getInt());
    std::string nodeAddrResolved = std::to_string(nodeAddr.getInt());
    std::string simTimeResolved = std::to_string(simTime().dbl());

    std::hash<std::string> hashFn;
    size_t hashResolved = hashFn(CHAddrResolved + nodeAddrResolved + simTimeResolved);
    return std::to_string(hashResolved);
}

bool Leach::checkFingerprint(std::string fingerprint) {
    for (auto& it : packetLog) {
        if (it.fingerprint == fingerprint) return true;
    }
    return false;
}

void Leach::addToPacketLog(std::string fingerprint) {
    packetLogEntry packet;
    packet.fingerprint = fingerprint;
    packetLog.push_back(packet);
}

void Leach::addToEventLog(Ipv4Address srcAddr, Ipv4Address destAddr, std::string packet, std::string type) {
    const char* srcNodeName = L3AddressResolver().findHostWithAddress(srcAddr)->getFullName();
    const char* destNodeName;
    if (destAddr.isLimitedBroadcastAddress()) {
        destNodeName = "Broadcast";
    } else {
        cModule* destModule = L3AddressResolver().findHostWithAddress(destAddr);
        if (destModule) {
            destNodeName = destModule->getFullName();
        } else {
            destNodeName = "Unknown";
            EV << "Warning: Could not resolve destination name for " << destAddr.str() << endl;
        }
    }

    J residualCapacity = J(0);
    try {
        SimpleEpEnergyStorage *energyStorageModule = check_and_cast<SimpleEpEnergyStorage*>(host->getSubmodule("energyStorage"));
        residualCapacity = energyStorageModule->getResidualEnergyCapacity();
    } catch (const cRuntimeError& e) {
        EV << "Energy storage error: " << e.what() << endl;
    }

    eventLogEntry nodeEvent;
    nodeEvent.srcNodeName = srcNodeName;
    nodeEvent.destNodeName = destNodeName;
    nodeEvent.time = simTime().dbl() * 1000;
    nodeEvent.packet = packet;
    nodeEvent.type = type;
    nodeEvent.residualCapacity = residualCapacity;
    nodeEvent.state = (leachState == ch ? "ch" : "nch");
    eventLog.push_back(nodeEvent);
}

void Leach::addToNodePosList() {
    IMobility *mobilityModule = check_and_cast<IMobility *>(host->getSubmodule("mobility"));
    Coord pos = mobilityModule->getCurrentPosition();

    nodePositionEntry nodePosition;
    nodePosition.nodeName = host->getFullName();
    nodePosition.posX = pos.getX();
    nodePosition.posY = pos.getY();
    nodePositionList.push_back(nodePosition);
}

void Leach::addToNodeWeightList() {
    nodeWeightObject nodeWeight;
    nodeWeight.nodeName = host->getFullName();
    nodeWeight.weight = weight;
    nodeWeightList.push_back(nodeWeight);
}

void Leach::generateEventLogCSV() {
    std::ofstream eventLogFile("eventLog.csv");
    eventLogFile << "Time,Node,Rx-Tx Node,Packet,Type,Energy,State" << std::endl;
    for (auto& it : eventLog) {
        std::string resolvedResidualCapacity = it.residualCapacity.str().erase(it.residualCapacity.str().size() - 2, 2);
        if (it.type == "SENT") {
            eventLogFile << it.time << "," << it.srcNodeName << "," << it.destNodeName << "," << it.packet << "," << it.type << ","
                         << resolvedResidualCapacity << "," << it.state << std::endl;
        } else {
            eventLogFile << it.time << "," << it.destNodeName << "," << it.srcNodeName << "," << it.packet << "," << it.type << ","
                         << resolvedResidualCapacity << "," << it.state << std::endl;
        }
    }
    eventLogFile.close();
}

void Leach::generateNodePosCSV() {
    std::ofstream nodePosFile("nodePos.csv");
    nodePosFile << "Node,X,Y,weight" << std::endl;
    for (auto& positionIterator : nodePositionList) {
        for (auto& weightIterator : nodeWeightList) {
            if (positionIterator.nodeName == weightIterator.nodeName) {
                nodePosFile << positionIterator.nodeName << "," << positionIterator.posX << "," << positionIterator.posY << ","
                            << weightIterator.weight << std::endl;
                break;
            }
        }
    }
    nodePosFile.close();
}

void Leach::generatePacketLogCSV() {
    std::ofstream packetLogFile("packetLog.csv");
    packetLogFile << "Data-Sent" << std::endl;
    for (auto& packetLogIterator : packetLog) {
        packetLogFile << packetLogIterator.fingerprint << std::endl;
    }
    packetLogFile.close();
}

void Leach::refreshDisplay() const {
    const char *icon;
    switch (leachState) {
        case nch:
            icon = "misc/sensor2";
            break;
        case ch:
            icon = "device/antennatower";
            break;
        default:
            throw cRuntimeError("Unknown LEACH status");
    }
    auto& displayString = getDisplayString();
    displayString.setTagArg("i", 0, icon);
    host->getDisplayString().setTagArg("i", 0, icon);
}

void Leach::finish() {
    addToNodeWeightList();
    generateEventLogCSV();
    generateNodePosCSV();
    generatePacketLogCSV();

    EV << "Total control packets sent by CH: " << controlPktSent << endl;
    EV << "Total control packets received by NCHs from CH: " << controlPktReceived << endl;
    EV << "Total data packets sent to CH: " << dataPktSent << endl;
    EV << "Total data packets received by CH from NCHs: " << dataPktReceived << endl;
    EV << "Total data packets received by CH from NCHs verified: " << dataPktReceivedVerf << endl;
    EV << "Total BS packets sent by CH: " << bsPktSent << endl;

    recordScalar("#dataPktSent", dataPktSent);
    recordScalar("#dataPktReceived", dataPktReceived);
    recordScalar("#dataPktReceivedVerf", dataPktReceivedVerf);
    recordScalar("#controlPktSent", controlPktSent);
    recordScalar("#controlPktReceived", controlPktReceived);
    recordScalar("#bsPktSent", bsPktSent);
}

} // namespace inet
