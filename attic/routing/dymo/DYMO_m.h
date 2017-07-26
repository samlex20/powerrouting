//
// Generated file, do not edit! Created by nedtool 5.1 from powerrouting/routing/dymo/DYMO.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __DYMO_M_H
#define __DYMO_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "inet/networklayer/common/L3Address.h"
#include "DYMOdefs.h"

typedef inet::L3Address L3Address;
// }}

/**
 * Class generated from <tt>powerrouting/routing/dymo/DYMO.msg:37</tt> by nedtool.
 * <pre>
 * class AddressBlock
 * {
 *     L3Address address;
 *     int prefixLength;
 *     bool hasValidityTime;
 *     simtime_t validityTime;
 *     bool hasMetric;
 *     double metric;
 *     bool hasMetricType;
 *     DYMOMetricType metricType = (DYMOMetricType)-1;
 *     bool hasSequenceNumber;
 *     DYMOSequenceNumber sequenceNumber = 0;
 * }
 * 
 * //
 * // DYMO timer messages
 * //
 * </pre>
 */
class AddressBlock : public ::omnetpp::cObject
{
  protected:
    L3Address address;
    int prefixLength;
    bool hasValidityTime;
    ::omnetpp::simtime_t validityTime;
    bool hasMetric;
    double metric;
    bool hasMetricType;
    DYMOMetricType metricType;
    bool hasSequenceNumber;
    DYMOSequenceNumber sequenceNumber;

  private:
    void copy(const AddressBlock& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AddressBlock&);

  public:
    AddressBlock();
    AddressBlock(const AddressBlock& other);
    virtual ~AddressBlock();
    AddressBlock& operator=(const AddressBlock& other);
    virtual AddressBlock *dup() const override {return new AddressBlock(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual L3Address& getAddress();
    virtual const L3Address& getAddress() const {return const_cast<AddressBlock*>(this)->getAddress();}
    virtual void setAddress(const L3Address& address);
    virtual int getPrefixLength() const;
    virtual void setPrefixLength(int prefixLength);
    virtual bool getHasValidityTime() const;
    virtual void setHasValidityTime(bool hasValidityTime);
    virtual ::omnetpp::simtime_t getValidityTime() const;
    virtual void setValidityTime(::omnetpp::simtime_t validityTime);
    virtual bool getHasMetric() const;
    virtual void setHasMetric(bool hasMetric);
    virtual double getMetric() const;
    virtual void setMetric(double metric);
    virtual bool getHasMetricType() const;
    virtual void setHasMetricType(bool hasMetricType);
    virtual DYMOMetricType& getMetricType();
    virtual const DYMOMetricType& getMetricType() const {return const_cast<AddressBlock*>(this)->getMetricType();}
    virtual void setMetricType(const DYMOMetricType& metricType);
    virtual bool getHasSequenceNumber() const;
    virtual void setHasSequenceNumber(bool hasSequenceNumber);
    virtual DYMOSequenceNumber& getSequenceNumber();
    virtual const DYMOSequenceNumber& getSequenceNumber() const {return const_cast<AddressBlock*>(this)->getSequenceNumber();}
    virtual void setSequenceNumber(const DYMOSequenceNumber& sequenceNumber);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AddressBlock& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AddressBlock& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>powerrouting/routing/dymo/DYMO.msg:54</tt> by nedtool.
 * <pre>
 * message RREQTimer
 * {
 *     L3Address target;
 * }
 * </pre>
 */
class RREQTimer : public ::omnetpp::cMessage
{
  protected:
    L3Address target;

  private:
    void copy(const RREQTimer& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RREQTimer&);

  public:
    RREQTimer(const char *name=nullptr, short kind=0);
    RREQTimer(const RREQTimer& other);
    virtual ~RREQTimer();
    RREQTimer& operator=(const RREQTimer& other);
    virtual RREQTimer *dup() const override {return new RREQTimer(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual L3Address& getTarget();
    virtual const L3Address& getTarget() const {return const_cast<RREQTimer*>(this)->getTarget();}
    virtual void setTarget(const L3Address& target);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RREQTimer& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RREQTimer& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>powerrouting/routing/dymo/DYMO.msg:58</tt> by nedtool.
 * <pre>
 * message RREQWaitRREPTimer extends RREQTimer
 * {
 *     int retryCount;
 * }
 * </pre>
 */
class RREQWaitRREPTimer : public ::RREQTimer
{
  protected:
    int retryCount;

  private:
    void copy(const RREQWaitRREPTimer& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RREQWaitRREPTimer&);

  public:
    RREQWaitRREPTimer(const char *name=nullptr, short kind=0);
    RREQWaitRREPTimer(const RREQWaitRREPTimer& other);
    virtual ~RREQWaitRREPTimer();
    RREQWaitRREPTimer& operator=(const RREQWaitRREPTimer& other);
    virtual RREQWaitRREPTimer *dup() const override {return new RREQWaitRREPTimer(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getRetryCount() const;
    virtual void setRetryCount(int retryCount);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RREQWaitRREPTimer& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RREQWaitRREPTimer& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>powerrouting/routing/dymo/DYMO.msg:62</tt> by nedtool.
 * <pre>
 * message RREQBackoffTimer extends RREQTimer
 * {
 *     int retryCount;
 * }
 * </pre>
 */
class RREQBackoffTimer : public ::RREQTimer
{
  protected:
    int retryCount;

  private:
    void copy(const RREQBackoffTimer& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RREQBackoffTimer&);

  public:
    RREQBackoffTimer(const char *name=nullptr, short kind=0);
    RREQBackoffTimer(const RREQBackoffTimer& other);
    virtual ~RREQBackoffTimer();
    RREQBackoffTimer& operator=(const RREQBackoffTimer& other);
    virtual RREQBackoffTimer *dup() const override {return new RREQBackoffTimer(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getRetryCount() const;
    virtual void setRetryCount(int retryCount);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RREQBackoffTimer& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RREQBackoffTimer& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>powerrouting/routing/dymo/DYMO.msg:66</tt> by nedtool.
 * <pre>
 * message RREQHolddownTimer extends RREQTimer
 * {
 * }
 * 
 * //
 * // DYMO packets
 * //
 * </pre>
 */
class RREQHolddownTimer : public ::RREQTimer
{
  protected:

  private:
    void copy(const RREQHolddownTimer& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RREQHolddownTimer&);

  public:
    RREQHolddownTimer(const char *name=nullptr, short kind=0);
    RREQHolddownTimer(const RREQHolddownTimer& other);
    virtual ~RREQHolddownTimer();
    RREQHolddownTimer& operator=(const RREQHolddownTimer& other);
    virtual RREQHolddownTimer *dup() const override {return new RREQHolddownTimer(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RREQHolddownTimer& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RREQHolddownTimer& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>powerrouting/routing/dymo/DYMO.msg:73</tt> by nedtool.
 * <pre>
 * packet DYMOPacket
 * {
 *     int hopLimit;
 * }
 * </pre>
 */
class DYMOPacket : public ::omnetpp::cPacket
{
  protected:
    int hopLimit;

  private:
    void copy(const DYMOPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DYMOPacket&);

  public:
    DYMOPacket(const char *name=nullptr, short kind=0);
    DYMOPacket(const DYMOPacket& other);
    virtual ~DYMOPacket();
    DYMOPacket& operator=(const DYMOPacket& other);
    virtual DYMOPacket *dup() const override {return new DYMOPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getHopLimit() const;
    virtual void setHopLimit(int hopLimit);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DYMOPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DYMOPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>powerrouting/routing/dymo/DYMO.msg:77</tt> by nedtool.
 * <pre>
 * packet RteMsg extends DYMOPacket
 * {
 *     int hopCount;
 *     AddressBlock originatorNode;
 *     AddressBlock targetNode;
 *     AddressBlock addedNode[];
 * }
 * </pre>
 */
class RteMsg : public ::DYMOPacket
{
  protected:
    int hopCount;
    AddressBlock originatorNode;
    AddressBlock targetNode;
    AddressBlock *addedNode; // array ptr
    unsigned int addedNode_arraysize;

  private:
    void copy(const RteMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RteMsg&);

  public:
    RteMsg(const char *name=nullptr, short kind=0);
    RteMsg(const RteMsg& other);
    virtual ~RteMsg();
    RteMsg& operator=(const RteMsg& other);
    virtual RteMsg *dup() const override {return new RteMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual AddressBlock& getOriginatorNode();
    virtual const AddressBlock& getOriginatorNode() const {return const_cast<RteMsg*>(this)->getOriginatorNode();}
    virtual void setOriginatorNode(const AddressBlock& originatorNode);
    virtual AddressBlock& getTargetNode();
    virtual const AddressBlock& getTargetNode() const {return const_cast<RteMsg*>(this)->getTargetNode();}
    virtual void setTargetNode(const AddressBlock& targetNode);
    virtual void setAddedNodeArraySize(unsigned int size);
    virtual unsigned int getAddedNodeArraySize() const;
    virtual AddressBlock& getAddedNode(unsigned int k);
    virtual const AddressBlock& getAddedNode(unsigned int k) const {return const_cast<RteMsg*>(this)->getAddedNode(k);}
    virtual void setAddedNode(unsigned int k, const AddressBlock& addedNode);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RteMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RteMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>powerrouting/routing/dymo/DYMO.msg:87</tt> by nedtool.
 * <pre>
 * //
 * // DYMO RREQ packet
 * //
 * packet RREQ extends RteMsg
 * {
 * }
 * </pre>
 */
class RREQ : public ::RteMsg
{
  protected:

  private:
    void copy(const RREQ& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RREQ&);

  public:
    RREQ(const char *name=nullptr, short kind=0);
    RREQ(const RREQ& other);
    virtual ~RREQ();
    RREQ& operator=(const RREQ& other);
    virtual RREQ *dup() const override {return new RREQ(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RREQ& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RREQ& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>powerrouting/routing/dymo/DYMO.msg:93</tt> by nedtool.
 * <pre>
 * //
 * // DYMO RREP packet
 * //
 * packet RREP extends RteMsg
 * {
 * }
 * </pre>
 */
class RREP : public ::RteMsg
{
  protected:

  private:
    void copy(const RREP& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RREP&);

  public:
    RREP(const char *name=nullptr, short kind=0);
    RREP(const RREP& other);
    virtual ~RREP();
    RREP& operator=(const RREP& other);
    virtual RREP *dup() const override {return new RREP(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RREP& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RREP& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>powerrouting/routing/dymo/DYMO.msg:99</tt> by nedtool.
 * <pre>
 * //
 * // DYMO RREP ACK packet
 * //
 * packet RREP_ACK extends DYMOPacket
 * {
 * }
 * </pre>
 */
class RREP_ACK : public ::DYMOPacket
{
  protected:

  private:
    void copy(const RREP_ACK& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RREP_ACK&);

  public:
    RREP_ACK(const char *name=nullptr, short kind=0);
    RREP_ACK(const RREP_ACK& other);
    virtual ~RREP_ACK();
    RREP_ACK& operator=(const RREP_ACK& other);
    virtual RREP_ACK *dup() const override {return new RREP_ACK(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RREP_ACK& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RREP_ACK& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>powerrouting/routing/dymo/DYMO.msg:105</tt> by nedtool.
 * <pre>
 * //
 * // DYMO RERR packet
 * //
 * packet RERR extends DYMOPacket
 * {
 *     L3Address PktSource;
 *     AddressBlock unreachableNode[];
 * }
 * </pre>
 */
class RERR : public ::DYMOPacket
{
  protected:
    L3Address PktSource;
    AddressBlock *unreachableNode; // array ptr
    unsigned int unreachableNode_arraysize;

  private:
    void copy(const RERR& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RERR&);

  public:
    RERR(const char *name=nullptr, short kind=0);
    RERR(const RERR& other);
    virtual ~RERR();
    RERR& operator=(const RERR& other);
    virtual RERR *dup() const override {return new RERR(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual L3Address& getPktSource();
    virtual const L3Address& getPktSource() const {return const_cast<RERR*>(this)->getPktSource();}
    virtual void setPktSource(const L3Address& PktSource);
    virtual void setUnreachableNodeArraySize(unsigned int size);
    virtual unsigned int getUnreachableNodeArraySize() const;
    virtual AddressBlock& getUnreachableNode(unsigned int k);
    virtual const AddressBlock& getUnreachableNode(unsigned int k) const {return const_cast<RERR*>(this)->getUnreachableNode(k);}
    virtual void setUnreachableNode(unsigned int k, const AddressBlock& unreachableNode);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RERR& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RERR& obj) {obj.parsimUnpack(b);}


#endif // ifndef __DYMO_M_H

