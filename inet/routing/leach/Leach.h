#ifndef __INET_LEACH_H__
#define __INET_LEACH_H__

#include "inet/common/INETDefs.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/common/NetworkInterface.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/networklayer/contract/IRoutingTable.h"
#include "inet/routing/base/RoutingProtocolBase.h"
#include "inet/routing/leach/LeachPkts_m.h"
#include "inet/power/storage/SimpleEpEnergyStorage.h"
#include "inet/mobility/contract/IMobility.h"
#include "inet/common/geometry/common/Coord.h"

namespace inet {

/**
 * @brief Implements the LEACH (Low Energy Adaptive Clustering Hierarchy) protocol for OMNeT++ and INET 4.5
 *
 * This implementation provides:
 * - Cluster Head election based on adaptive threshold
 * - Node-to-CH association and TDMA scheduling
 * - Data transmission to CH and from CH to base station
 * - Energy monitoring and state management
 */
class INET_API Leach : public RoutingProtocolBase {
  private:
    struct ForwardEntry {
        cMessage *event = nullptr;
        cMessage *hello = nullptr;
        ForwardEntry() {}
        virtual ~ForwardEntry();
    };

    bool isForwardHello = false;
    cMessage *event = nullptr;
    cPar *broadcastDelay = nullptr;
    std::list<ForwardEntry *> *forwardList = nullptr;
    NetworkInterface *interface80211ptr = nullptr;
    int interfaceId = -1;
    unsigned int sequencenumber = 0;
    cModule *host = nullptr;
    ForwardEntry *forwardEntry = nullptr;

    Ipv4Address idealCH;

    simsignal_t subIntervalTot;

    int dataPktSent = 0;
    int dataPktReceived = 0;
    int dataPktReceivedVerf = 0;
    int controlPktSent = 0;
    int controlPktReceived = 0;
    int bsPktSent = 0;
    int round = 0;
    int weight = 0;
    int totalChCount = 0;  // Added to track total CH counts over time

  protected:
    simtime_t helloInterval;
    IInterfaceTable *ift = nullptr;
    IRoutingTable *rt = nullptr;

    simtime_t dataPktSendDelay;
    simtime_t CHPktSendDelay;
    simtime_t roundDuration;

    int numNodes = 0;
    double clusterHeadPercentage = 0.0;
    double threshold = 0.0;

    double TDMADelayCounter = 1.0;

    simtime_t roundStartTime;

    struct nodeMemoryObject {
        Ipv4Address nodeAddr;
        Ipv4Address CHAddr;
        double energy;
    };

    struct TDMAScheduleEntry {
        Ipv4Address nodeAddress;
        double TDMAdelay;
    };

    struct eventLogEntry {
        std::string srcNodeName;
        std::string destNodeName;
        double time;
        std::string packet;
        std::string type;
        J residualCapacity;
        std::string state;
    };

    struct nodePositionEntry {
        std::string nodeName;
        double posX;
        double posY;
    };

    struct nodeWeightObject {
        std::string nodeName;
        int weight;
    };

    struct packetLogEntry {
        std::string fingerprint;
    };

    std::vector<nodeMemoryObject> nodeMemory;
    std::vector<TDMAScheduleEntry> nodeCHMemory;
    std::vector<TDMAScheduleEntry> extractedTDMASchedule;
    std::vector<eventLogEntry> eventLog;
    std::vector<nodePositionEntry> nodePositionList;
    std::vector<nodeWeightObject> nodeWeightList;
    std::vector<packetLogEntry> packetLog;

  public:
    Leach();
    virtual ~Leach();

    enum LeachState { nch, ch };
    LeachState leachState = nch;
    bool wasCH = false;

  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;

    void handleSelfMessage(cMessage *msg);
    void processMessage(cMessage *msg);

    virtual void handleStartOperation(LifecycleOperation *operation) override { start(); }
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;
    void start();
    void stop();
    virtual void refreshDisplay() const override;
    void finish() override;

    enum SelfMsgKinds { SELF = 1, DATA2CH, DATA2BS };

    double generateThresholdValue(int subInterval);
    void sendDataToCH(Ipv4Address nodeAddr, Ipv4Address CHAddr, double TDMAslot);
    void sendDataToBS(Ipv4Address CHAddr, std::string fingerprint);
    void sendAckToCH(Ipv4Address nodeAddr, Ipv4Address CHAddr);
    void sendSchToNCH(Ipv4Address selfAddr);

    void addToNodeMemory(Ipv4Address nodeAddr, Ipv4Address CHAddr, double energy);
    void addToNodeCHMemory(Ipv4Address NCHAddr);
    bool isCHAddedInMemory(Ipv4Address CHAddr);
    bool isNCHAddedInCHMemory(Ipv4Address NCHAddr);
    void generateTDMASchedule();
    virtual void setLeachState(LeachState ls);

    Ipv4Address getIdealCH(Ipv4Address nodeAddr);
    std::string resolveFingerprint(Ipv4Address nodeAddr, Ipv4Address CHAddr);
    bool checkFingerprint(std::string fingerprint);

    void addToPacketLog(std::string fingerprint);
    void addToEventLog(Ipv4Address srcAddr, Ipv4Address destAddr, std::string packet, std::string type);
    void addToNodePosList();
    void addToNodeWeightList();

    void generateEventLogCSV();
    void generateNodePosCSV();
    void generatePacketLogCSV();

    // Helper methods for energy management
    J getNodeCurrentEnergy() const;
    double getEnergyPercentage() const;
};

} // namespace inet

#endif // __INET_LEACH_H__
