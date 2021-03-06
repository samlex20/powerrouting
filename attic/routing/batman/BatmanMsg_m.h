//
// Generated file, do not edit! Created by nedtool 5.1 from powerrouting/routing/batman/BatmanMsg.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __BATMANMSG_M_H
#define __BATMANMSG_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "inet/networklayer/common/L3Address.h"
#define DIRECTLINK 0x40
#define UNIDIRECTIONAL 0x80

#ifdef __USE_MINHOP__
#define BatPacketSize 17
#else
#define BatPacketSize 16
#endif

#define BATMAN_HNA_MSG_SIZE 5

typedef inet::L3Address L3Address;
// }}

/**
 * Struct generated from powerrouting/routing/batman/BatmanMsg.msg:27 by nedtool.
 */
struct vis_data
{
    vis_data();
    uint8_t type;
    uint8_t data;
    L3Address ip;
};

// helpers for local use
void __doPacking(omnetpp::cCommBuffer *b, const vis_data& a);
void __doUnpacking(omnetpp::cCommBuffer *b, vis_data& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const vis_data& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, vis_data& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from powerrouting/routing/batman/BatmanMsg.msg:34 by nedtool.
 */
struct HnaElement
{
    HnaElement();
    L3Address addr;
    uint8_t netmask;
};

// helpers for local use
void __doPacking(omnetpp::cCommBuffer *b, const HnaElement& a);
void __doUnpacking(omnetpp::cCommBuffer *b, HnaElement& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const HnaElement& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, HnaElement& obj) { __doUnpacking(b, obj); }

/**
 * Class generated from <tt>powerrouting/routing/batman/BatmanMsg.msg:40</tt> by nedtool.
 * <pre>
 * packet BatmanPacket
 * {
 *     byteLength = BatPacketSize;
 *     uint8_t version;  // batman version field
 *     uint8_t flags;    // 0x80: UNIDIRECTIONAL link, 0x40: DIRECTLINK flag, ...
 *     uint8_t ttl;
 *     uint8_t gatewayFlags;  // flags related to gateway functions: gateway class
 *     unsigned short seqNumber;
 *     unsigned short gatewayPort;
 *     L3Address orig;
 *     L3Address prevSender;
 *     uint8_t tq;           // Quality
 *     uint8_t hops;
 *     HnaElement hnaMsg[];    ///< Packet body.
 * }
 * </pre>
 */
class BatmanPacket : public ::omnetpp::cPacket
{
  protected:
    uint8_t version;
    uint8_t flags;
    uint8_t ttl;
    uint8_t gatewayFlags;
    unsigned short seqNumber;
    unsigned short gatewayPort;
    L3Address orig;
    L3Address prevSender;
    uint8_t tq;
    uint8_t hops;
    HnaElement *hnaMsg; // array ptr
    unsigned int hnaMsg_arraysize;

  private:
    void copy(const BatmanPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const BatmanPacket&);

  public:
    BatmanPacket(const char *name=nullptr, short kind=0);
    BatmanPacket(const BatmanPacket& other);
    virtual ~BatmanPacket();
    BatmanPacket& operator=(const BatmanPacket& other);
    virtual BatmanPacket *dup() const override {return new BatmanPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual uint8_t getVersion() const;
    virtual void setVersion(uint8_t version);
    virtual uint8_t getFlags() const;
    virtual void setFlags(uint8_t flags);
    virtual uint8_t getTtl() const;
    virtual void setTtl(uint8_t ttl);
    virtual uint8_t getGatewayFlags() const;
    virtual void setGatewayFlags(uint8_t gatewayFlags);
    virtual unsigned short getSeqNumber() const;
    virtual void setSeqNumber(unsigned short seqNumber);
    virtual unsigned short getGatewayPort() const;
    virtual void setGatewayPort(unsigned short gatewayPort);
    virtual L3Address& getOrig();
    virtual const L3Address& getOrig() const {return const_cast<BatmanPacket*>(this)->getOrig();}
    virtual void setOrig(const L3Address& orig);
    virtual L3Address& getPrevSender();
    virtual const L3Address& getPrevSender() const {return const_cast<BatmanPacket*>(this)->getPrevSender();}
    virtual void setPrevSender(const L3Address& prevSender);
    virtual uint8_t getTq() const;
    virtual void setTq(uint8_t tq);
    virtual uint8_t getHops() const;
    virtual void setHops(uint8_t hops);
    virtual void setHnaMsgArraySize(unsigned int size);
    virtual unsigned int getHnaMsgArraySize() const;
    virtual HnaElement& getHnaMsg(unsigned int k);
    virtual const HnaElement& getHnaMsg(unsigned int k) const {return const_cast<BatmanPacket*>(this)->getHnaMsg(k);}
    virtual void setHnaMsg(unsigned int k, const HnaElement& hnaMsg);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const BatmanPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, BatmanPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>powerrouting/routing/batman/BatmanMsg.msg:56</tt> by nedtool.
 * <pre>
 * packet visPacket
 * {
 *     L3Address senderIp;
 *     unsigned char version;
 *     unsigned char gwClass;
 *     unsigned char tqMax;
 *     vis_data visData[];
 * }
 * </pre>
 */
class visPacket : public ::omnetpp::cPacket
{
  protected:
    L3Address senderIp;
    unsigned char version;
    unsigned char gwClass;
    unsigned char tqMax;
    vis_data *visData; // array ptr
    unsigned int visData_arraysize;

  private:
    void copy(const visPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const visPacket&);

  public:
    visPacket(const char *name=nullptr, short kind=0);
    visPacket(const visPacket& other);
    virtual ~visPacket();
    visPacket& operator=(const visPacket& other);
    virtual visPacket *dup() const override {return new visPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual L3Address& getSenderIp();
    virtual const L3Address& getSenderIp() const {return const_cast<visPacket*>(this)->getSenderIp();}
    virtual void setSenderIp(const L3Address& senderIp);
    virtual unsigned char getVersion() const;
    virtual void setVersion(unsigned char version);
    virtual unsigned char getGwClass() const;
    virtual void setGwClass(unsigned char gwClass);
    virtual unsigned char getTqMax() const;
    virtual void setTqMax(unsigned char tqMax);
    virtual void setVisDataArraySize(unsigned int size);
    virtual unsigned int getVisDataArraySize() const;
    virtual vis_data& getVisData(unsigned int k);
    virtual const vis_data& getVisData(unsigned int k) const {return const_cast<visPacket*>(this)->getVisData(k);}
    virtual void setVisData(unsigned int k, const vis_data& visData);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const visPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, visPacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef __BATMANMSG_M_H

