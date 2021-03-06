// PowerRouting for OMNeT++ - Batman ManetAddress
// Marcel Ebbrecht, marcel.ebbrecht@googlemail.com
// free software, see LICENSE.md for details
// derived from inetmanet-3.5, ManetAddress.h


#ifndef __INET_MANETADDRESS_H
#define __INET_MANETADDRESS_H

#include "inet/networklayer/contract/ipv4/IPv4Address.h"
#include "inet/networklayer/contract/ipv6/IPv6Address.h"
#include "inet/networklayer/common/L3Address.h"
#include "inet/linklayer/common/MACAddress.h"

typedef inet::IPv4Address IPv4Address;
typedef inet::IPv6Address IPv6Address;
typedef inet::L3Address L3Address;
typedef inet::MACAddress MACAddress;

/*
 * Stores an IPv4, IPv6 or an MACAddress address with prefix. This class should be used in
 * manetrouting, to guarantee IPv4/IPv6/MACAddress transparency.
 *
 * Storage is efficient: an object occupies size of an IPv6 address
 * (128 bits=16 bytes) plus two short int (address type and prefix length).
 */
// TODO: move into Address.h and rename to AddressPrefix
class ManetNetworkAddress
{
  public:
    ManetNetworkAddress() : prefixLength(0) {}
    ManetNetworkAddress(const ManetNetworkAddress& o) : address(o.address), prefixLength(o.prefixLength) {}
    ManetNetworkAddress(const L3Address& o, short unsigned int masklen) : address(o), prefixLength(masklen) { setPrefixLen(masklen); }
    explicit ManetNetworkAddress(IPv4Address addr, short unsigned int masklen=32) { set(addr, masklen); }
    explicit ManetNetworkAddress(const IPv6Address& addr, short unsigned int masklen=128) { set(addr, masklen); }
    explicit ManetNetworkAddress(const L3Address& addr) { set(addr); }
    explicit ManetNetworkAddress(MACAddress addr, short unsigned int masklen=48) { set(addr, masklen); }

    void set(IPv4Address addr, short unsigned int masklen = 32);
    void set(const IPv6Address& addr, short unsigned int masklen = 128);
    void set(const L3Address& addr);
    void set(const L3Address& addr, short unsigned int masklen);
    void set(MACAddress addr, short unsigned int masklen = 48);

    void setPrefixLen(short unsigned int masklen);

    const L3Address& getAddress() const { return address; }
    short unsigned int getPrefixLength() const { return prefixLength; }
    L3Address::AddressType getType() const { return address.getType(); }

    std::string str() const;

    /**
     * compare this and o and returns:
     * -1 if this < other
     *  0 if this == other
     *  1 if this > other
     */
    short int compare(const ManetNetworkAddress& other) const;

    bool operator ==(const ManetNetworkAddress& other) const { return prefixLength==other.prefixLength && address==other.address; }
    bool operator !=(const ManetNetworkAddress& other) const { return !operator==(other); }
    bool operator <(const ManetNetworkAddress& other) const { return compare(other) < 0; }
    bool operator <=(const ManetNetworkAddress& other) const { return compare(other) <= 0; }
    bool operator >(const ManetNetworkAddress& other) const { return compare(other) > 0; }
    bool operator >=(const ManetNetworkAddress& other) const { return compare(other) >= 0; }

    bool contains(const L3Address& other) const;
    bool contains(const ManetNetworkAddress& other) const;

  protected:
    // member variables:
    L3Address address;
    short unsigned int prefixLength;
};

inline std::ostream& operator<<(std::ostream& os, const ManetNetworkAddress& addr)
{
    return os << addr.str();
}

#endif  // __INET_MANETADDRESS_H

