// PowerRouting for OMNeT++ - AODV router definition
// Marcel Ebbrecht, marcel.ebbrecht@googlemail.com
// free software, see LICENSE.md for details
// derived from inetmanet-3.5, AODVRouter.ned

package powerrouting.node.dymopo;

import inet.node.inet.WirelessHost;
import inet.routing.dymo.IDYMO;
import inet.node.dymo.DYMORouter;


//
// It models a ~WirelessHost extended with ~AODVRouting submodule.
//
// AODV is an on-demand MANET routing protocol. Each node
// works similar to a 'router': they manage their own routing
// tables, send request for routes and consult the IP layer via
// Netfilter hooks for data forwarding.
//
// Scenerios where AODV routing is desired use this module as a
// host module.
//
// For more info about AODVRouting, see the corresponding module:
// ~AODVRouting and its C++ implementation with the same name.
//
// The AODV v.2 (known as DYMOPO) is also implemented: ~DYMOPO,
// ~DYMOPORouter.
//
module DYMOPORouter extends DYMORouter
{
}
