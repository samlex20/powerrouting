// PowerRouting for OMNeT++ - AODVPO routing
// Marcel Ebbrecht, marcel.ebbrecht@googlemail.com
// free software, see LICENSE.md for details
// derived from inetmanet-3.5, AODVRouting.h

#ifndef __INET_AODVPORouting_H
#define __INET_AODVPORouting_H

#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/contract/IL3AddressType.h"
#include "inet/networklayer/contract/IRoutingTable.h"
#include "inet/networklayer/contract/INetfilter.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/transportlayer/contract/udp/UDPSocket.h"
#include "../aodv/AODVRouteData.h"
#include "inet/transportlayer/udp/UDPPacket.h"
#include "../aodv/AODVControlPackets_m.h"
#include <map>
#include "inet/power/contract/IEnergyStorage.h"
#include "inet/power/storage/SimpleEpEnergyStorage.h"

// typedefs for porting
typedef inet::INetfilter::IHook IHook;
typedef inet::INetfilter INetfilter;
typedef inet::ILifecycle ILifecycle;
typedef inet::INetworkDatagram INetworkDatagram;
typedef inet::InterfaceEntry InterfaceEntry;
typedef inet::L3Address L3Address;
typedef inet::IL3AddressType IL3AddressType;
typedef inet::IRoutingTable IRoutingTable;
typedef inet::IInterfaceTable IInterfaceTable;
typedef inet::IRoute IRoute;
typedef inet::LifecycleOperation LifecycleOperation;
typedef inet::IDoneCallback IDoneCallback;
typedef inet::power::IEpEnergyStorage IEpEnergyStorage;

/*
 * This class implements AODV routing protocol and Netfilter hooks
 * in the IP-layer required by this protocol.
 */

//class INET_API AODVPORouting : public cSimpleModule, public ILifecycle, public INetfilter::IHook, public cListener
class AODVPORouting : public cSimpleModule, public ILifecycle, public INetfilter::IHook, public cListener
{
  protected:
    /*
     * It implements a unique identifier for an arbitrary RREQ message
     * in the network. See: rreqsArrivalTime.
     */
    class RREQIdentifier
    {
      public:
        L3Address originatorAddr;
        unsigned int rreqID;
        RREQIdentifier(const L3Address& originatorAddr, unsigned int rreqID) : originatorAddr(originatorAddr), rreqID(rreqID) {};
        bool operator==(const RREQIdentifier& other) const
        {
            return this->originatorAddr == other.originatorAddr && this->rreqID == other.rreqID;
        }
    };

    class RREQIdentifierCompare
    {
      public:
        bool operator()(const RREQIdentifier& lhs, const RREQIdentifier& rhs) const
        {
            return lhs.rreqID < rhs.rreqID;
        }
    };

    // context
    IL3AddressType *addressType = nullptr;    // to support both IPv4 and v6 addresses.

    // environment
    cModule *host = nullptr;
    IRoutingTable *routingTable = nullptr;
    IInterfaceTable *interfaceTable = nullptr;
    INetfilter *networkProtocol = nullptr;

    // AODV parameters: the following parameters are configurable, see the NED file for more info.
    unsigned int rerrRatelimit = 0;
    unsigned int aodvUDPPort = 0;
    bool askGratuitousRREP = false;
    bool useHelloMessages = false;
    simtime_t maxJitter;
    simtime_t activeRouteTimeout;
    simtime_t helloInterval;
    unsigned int netDiameter = 0;
    unsigned int rreqRetries = 0;
    unsigned int rreqRatelimit = 0;
    unsigned int timeoutBuffer = 0;
    unsigned int ttlStart = 0;
    unsigned int ttlIncrement = 0;
    unsigned int ttlThreshold = 0;
    unsigned int localAddTTL = 0;
    unsigned int allowedHelloLoss = 0;
    simtime_t nodeTraversalTime;
    cPar *jitterPar = nullptr;
    cPar *periodicJitter = nullptr;

    // the following parameters are calculated from the parameters defined above
    // see the NED file for more info
    simtime_t deletePeriod;
    simtime_t myRouteTimeout;
    simtime_t blacklistTimeout;
    simtime_t netTraversalTime;
    simtime_t nextHopWait;
    simtime_t pathDiscoveryTime;

    // start modification
    // signal for measure of routing overhead
    static simsignal_t routingOverheadSignal;
    // end modification

    // state
    unsigned int rreqId = 0;    // when sending a new RREQ packet, rreqID incremented by one from the last id used by this node
    unsigned int sequenceNum = 0;    // it helps to prevent loops in the routes (RFC 3561 6.1 p11.)
    std::map<L3Address, WaitForRREP *> waitForRREPTimers;    // timeout for Route Replies
    std::map<RREQIdentifier, simtime_t, RREQIdentifierCompare> rreqsArrivalTime;    // maps RREQ id to its arriving time
    L3Address failedNextHop;    // next hop to the destination who failed to send us RREP-ACK
    std::map<L3Address, simtime_t> blacklist;    // we don't accept RREQs from blacklisted nodes
    unsigned int rerrCount = 0;    // num of originated RERR in the last second
    unsigned int rreqCount = 0;    // num of originated RREQ in the last second
    simtime_t lastBroadcastTime;    // the last time when any control packet was broadcasted
    std::map<L3Address, unsigned int> addressToRreqRetries;    // number of re-discovery attempts per address

    // self messages
    cMessage *waitForRREP = nullptr;    // timer to send hello messages (only if the feature is enabled)
    cMessage *helloMsgTimer = nullptr;    // timer to send hello messages (only if the feature is enabled)
    cMessage *expungeTimer = nullptr;    // timer to clean the routing table out
    cMessage *counterTimer = nullptr;    // timer to set rrerCount = rreqCount = 0 in each second
    cMessage *rrepAckTimer = nullptr;    // timer to wait for RREP-ACKs (RREP-ACK timeout)
    cMessage *blacklistTimer = nullptr;    // timer to clean the blacklist out

    // lifecycle
    simtime_t rebootTime;    // the last time when the node rebooted
    bool isOperational = false;

    // internal
    std::multimap<L3Address, INetworkDatagram *> targetAddressToDelayedPackets;    // queue for the datagrams we have no route for

    // parameters for energy-optimization
    IEpEnergyStorage *energyStorage = nullptr;
    double relativeCharge = 0;
    double hopPenaltyDouble = 0;
    double hopPenaltyDoublePreroundup = 0;
    int hopPenalty = 0;
    double powerSensitivity = 0;
    double powerSensitivityMin = 0;
    double powerSensitivityMax = 0;
    double powerSensitivityDefault = 0;
    double powerBias = 0;
    double powerBiasMin = 0;
    double powerBiasDefault = 0;
    double powerTrigger = 0;
    double powerTriggerMin = 0;
    double powerTriggerMax = 0;
    double powerTriggerDefault = 0;
    double powerTriggerDouble = 0;
    double timePenalty = 0;
    double timePenaltyMin = 0;
    double timePenaltyMax = 0;
    double timePenaltyDefault = 0;
    int powerTriggerCalculated = 999999999;
    int powerTriggerLast = 999999999;
    AODVRREP *waitPacket;
    L3Address waitAddress;
    int waitTimer;

  protected:

    void handleMessage(cMessage *msg) override;
    void initialize(int stage) override;
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }

    /* Route Discovery */
    void startRouteDiscovery(const L3Address& target, unsigned int timeToLive = 0);
    void completeRouteDiscovery(const L3Address& target);
    bool hasOngoingRouteDiscovery(const L3Address& destAddr);
    void cancelRouteDiscovery(const L3Address& destAddr);

    /* Routing Table management */
    virtual void updateRoutingTable(IRoute *route, const L3Address& nextHop, unsigned int hopCount, bool hasValidDestNum, unsigned int destSeqNum, bool isActive, simtime_t lifeTime);
    IRoute *createRoute(const L3Address& destAddr, const L3Address& nextHop, unsigned int hopCount, bool hasValidDestNum, unsigned int destSeqNum, bool isActive, simtime_t lifeTime);
    bool updateValidRouteLifeTime(const L3Address& destAddr, simtime_t lifetime);
    void scheduleExpungeRoutes();
    void expungeRoutes();

    /* Control packet creators */
    AODVRREPACK *createRREPACK();
    AODVRREP *createHelloMessage();
    AODVRREQ *createRREQ(const L3Address& destAddr);
    AODVRREP *createRREP(AODVRREQ *rreq, IRoute *destRoute, IRoute *originatorRoute, const L3Address& sourceAddr);
    AODVRREP *createGratuitousRREP(AODVRREQ *rreq, IRoute *originatorRoute);
    AODVRERR *createRERR(const std::vector<UnreachableNode>& unreachableNodes);

    /* Control Packet handlers */
    void handleRREP(AODVRREP *rrep, const L3Address& sourceAddr);
    void handleRREQ(AODVRREQ *rreq, const L3Address& sourceAddr, unsigned int timeToLive);
    void handleRERR(AODVRERR *rerr, const L3Address& sourceAddr);
    void handleHelloMessage(AODVRREP *helloMessage);
    void handleRREPACK(AODVRREPACK *rrepACK, const L3Address& neighborAddr);

    /* Control Packet sender methods */
    void sendRREQ(AODVRREQ *rreq, const L3Address& destAddr, unsigned int timeToLive);
    void sendRREPACK(AODVRREPACK *rrepACK, const L3Address& destAddr);
    void sendRREP(AODVRREP *rrep, const L3Address& destAddr, unsigned int timeToLive);
    void sendGRREP(AODVRREP *grrep, const L3Address& destAddr, unsigned int timeToLive);

    /* Control Packet forwarders */
    void forwardRREP(AODVRREP *rrep, const L3Address& destAddr, unsigned int timeToLive);
    void forwardRREQ(AODVRREQ *rreq, unsigned int timeToLive);

    /* Self message handlers */
    void handleRREPACKTimer();
    void handleBlackListTimer();
    void sendHelloMessagesIfNeeded();
    void handleWaitForRREP(WaitForRREP *rrepTimer);

    /* General functions to handle route errors */
    void sendRERRWhenNoRouteToForward(const L3Address& unreachableAddr);
    void handleLinkBreakSendRERR(const L3Address& unreachableAddr);
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;

    /* Netfilter hooks */
    Result ensureRouteForDatagram(INetworkDatagram *datagram);
    virtual Result datagramPreRoutingHook(INetworkDatagram *datagram, const InterfaceEntry *inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, L3Address& nextHopAddress) override { Enter_Method("datagramPreRoutingHook"); return ensureRouteForDatagram(datagram); }
    virtual Result datagramForwardHook(INetworkDatagram *datagram, const InterfaceEntry *inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, L3Address& nextHopAddress) override;
    virtual Result datagramPostRoutingHook(INetworkDatagram *datagram, const InterfaceEntry *inputInterfaceEntry, const InterfaceEntry *& outputInterfaceEntry, L3Address& nextHopAddress) override { return ACCEPT; }
    virtual Result datagramLocalInHook(INetworkDatagram *datagram, const InterfaceEntry *inputInterfaceEntry) override { return ACCEPT; }
    virtual Result datagramLocalOutHook(INetworkDatagram *datagram, const InterfaceEntry *& outputInterfaceEntry, L3Address& nextHopAddress) override { Enter_Method("datagramLocalOutHook"); return ensureRouteForDatagram(datagram); }
    void delayDatagram(INetworkDatagram *datagram);

    /* Helper functions */
    L3Address getSelfIPAddress() const;
    void sendAODVPacket(AODVControlPacket *packet, const L3Address& destAddr, unsigned int timeToLive, double delay);
    void clearState();

    /* Lifecycle */
    virtual bool handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback) override;

    // calculate the penalty and trigger
    int calculatePenalty();
    int calculateTrigger();

  public:
    AODVPORouting();
    virtual ~AODVPORouting();
};

#endif    // ifndef AODVPORouting_H_

