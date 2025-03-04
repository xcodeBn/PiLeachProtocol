#ifndef __INET_LEACHBS_H__
#define __INET_LEACHBS_H__

#include "inet/common/INETDefs.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/common/NetworkInterface.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/routing/base/RoutingProtocolBase.h"
#include "inet/routing/leach/LeachPkts_m.h"
#include <map>

namespace inet {

class INET_API LeachBS : public RoutingProtocolBase {
  private:
    int bsPktReceived = 0;
    NetworkInterface *interface80211ptr = nullptr;
    int interfaceId = -1;
    unsigned int sequencenumber = 0;
    cModule *host = nullptr;
    std::map<Ipv4Address, int> packetsPerCH;  // Map to track packets from each CH
    cOutVector packetsPerCHVector;  // For real-time visualization

  protected:
    IInterfaceTable *ift = nullptr;

    struct packetRecLogEntry {
        std::string fingerprint;
    };
    std::vector<packetRecLogEntry> packetRecLog;

  public:
    LeachBS();
    virtual ~LeachBS();

  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;

    virtual void handleStartOperation(LifecycleOperation *operation) override { start(); }
    virtual void handleStopOperation(LifecycleOperation *operation) override { stop(); }
    virtual void handleCrashOperation(LifecycleOperation *operation) override { stop(); }
    void start();
    void stop();
    void finish() override;

    void addToPacketRecLog(std::string fingerprint);
    void generatePacketRecLogCSV();
    void generateCHStatsCSV();  // New method to generate CH statistics

    // Added real-time logging method
    void logPacketReception(int packetNumber, const Ipv4Address& sourceAddr, const std::string& fingerprint);

    // Modified to include source address
    void addToPacketRecLog(std::string fingerprint, const Ipv4Address& sourceAddr);
};

} // namespace inet

#endif // __INET_LEACHBS_H__
