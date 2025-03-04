#include "LeachBS.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/routing/leach/Leach.h"
#include "inet/physicallayer/wireless/common/contract/packetlevel/SignalTag_m.h"
#include "inet/networklayer/ipv4/Ipv4InterfaceData.h"

#include <iostream>
#include <fstream>
#include <map>


// xcodeBn@github
// inet 4.5.0 ( works fine on this version )
namespace inet {

Define_Module(LeachBS);

LeachBS::LeachBS() {}

LeachBS::~LeachBS() {}

void LeachBS::initialize(int stage) {
    RoutingProtocolBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        sequencenumber = 0;
        host = getContainingNode(this);
        ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        bsPktReceived = 0;

        // Initialize the vector for real-time statistics visualization
        packetsPerCHVector.setName("Packets per CH");
        packetsPerCHVector.setType(cOutVector::TYPE_INT);
    } else if (stage == INITSTAGE_ROUTING_PROTOCOLS) {

//        registerService(Protocol::manet, nullptr, gate("ipIn"));
//        registerProtocol(Protocol::manet, gate("ipOut"), nullptr);
        registerService(Protocol::manet, gate("ipOut"), gate("ipIn"));
               registerProtocol(Protocol::manet, gate("ipOut"), gate("ipIn"));

    }
}

void LeachBS::start() {
    int num_80211 = 0;
    NetworkInterface *ie;
    NetworkInterface *i_face;
    const char *name;

    for (int i = 0; i < ift->getNumInterfaces(); i++) {
        ie = ift->getInterface(i);
        name = ie->getInterfaceName();
        if (strstr(name, "wlan") != nullptr) {
            i_face = ie;
            num_80211++;
            interfaceId = i;
        }
    }

    if (num_80211 == 1) {
        interface80211ptr = i_face;
    } else {
        throw cRuntimeError("LeachBS has found %i 802.11 interfaces", num_80211);
    }

    interface80211ptr->getProtocolDataForUpdate<Ipv4InterfaceData>()->joinMulticastGroup(Ipv4Address::LL_MANET_ROUTERS);
}

void LeachBS::stop() {}

void LeachBS::handleMessageWhenUp(cMessage *msg) {
    Ipv4Address nodeAddr = interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress();

    if (msg->isSelfMessage()) {
        delete msg;
    } else if (check_and_cast<Packet *>(msg)->getTag<PacketProtocolTag>()->getProtocol() == &Protocol::manet) {
        auto receivedCtrlPkt = staticPtrCast<LeachControlPkt>(check_and_cast<Packet *>(msg)->peekData<LeachControlPkt>()->dupShared());
        Packet *receivedPkt = check_and_cast<Packet *>(msg);
        auto& leachControlPkt = receivedPkt->popAtFront<LeachControlPkt>();
        auto packetType = leachControlPkt->getPacketType();

        if (msg->arrivedOn("ipIn")) {
            if (packetType == CH || packetType == ACK || packetType == SCH || packetType == DATA) {
                delete msg;
            } else if (packetType == BS) {
                bsPktReceived++;
                std::string fingerprint = receivedCtrlPkt->getFingerprint();

                // Get the source address from the packet
                auto addressTag = receivedPkt->findTag<L3AddressInd>();
                if (addressTag) {
                    Ipv4Address sourceAddr = addressTag->getSrcAddress().toIpv4();
                    packetsPerCH[sourceAddr]++; // Increment counter for this CH

                    // Display statistics during simulation
                    EV << "Received packet from CH " << sourceAddr << ", total from this CH: "
                       << packetsPerCH[sourceAddr] << endl;

                    // Record for real-time visualization
                    packetsPerCHVector.record(packetsPerCH[sourceAddr]);
                }

                addToPacketRecLog(fingerprint);
                delete msg;
            }
        } else {
            throw cRuntimeError("Message arrived on unknown gate %s", msg->getArrivalGate()->getName());
        }
    } else {
        throw cRuntimeError("Message not supported %s", msg->getName());
    }
}

void LeachBS::generatePacketRecLogCSV() {
    std::ofstream packetRecLogFile("packetRecLog.csv");
    packetRecLogFile << "Data-Rec" << std::endl;
    for (auto& packetRecLogIterator : packetRecLog) {
        packetRecLogFile << packetRecLogIterator.fingerprint << std::endl;
    }
    packetRecLogFile.close();
}

void LeachBS::generateCHStatsCSV() {
    // Open statistics file
    std::ofstream chStatsFile("ch_statistics.csv");
    chStatsFile << "ClusterHead,PacketsReceived" << std::endl;

    for (auto& entry : packetsPerCH) {
        chStatsFile << entry.first << "," << entry.second << std::endl;
    }

    chStatsFile.close();
}

void LeachBS::addToPacketRecLog(std::string fingerprint) {
    packetRecLogEntry packet;
    packet.fingerprint = fingerprint;
    packetRecLog.push_back(packet);
}

void LeachBS::finish() {
    generatePacketRecLogCSV();
    generateCHStatsCSV();

    // Display per-CH statistics
    EV << "Total data packets received by BS from CHs: " << bsPktReceived << endl;
    EV << "Per-CH statistics:" << endl;

    for (auto& entry : packetsPerCH) {
        EV << "  CH " << entry.first << ": " << entry.second << " packets" << endl;

        // Record scalar for each CH
        std::string scalarName = "packets_from_CH_" + entry.first.str();
        recordScalar(scalarName.c_str(), entry.second);
    }

    recordScalar("#bsPktReceived", bsPktReceived);
}

} // namespace inet
