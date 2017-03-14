#ifndef __IFACE_H_INCLUDED__
#define __IFACE_H_INCLUDED__

// forward declared dependencies
class IpAddr;

// include dependencies
#include <string>
#include "ipaddr.h"

namespace ns3lxc {
class Iface;
class Node;
class Link;
// declarations
class IfaceProvider {
public:
    std::map<std::string, std::string> ifacesProvidedSubNames; //maps this level's iface names to lower level's
    std::map<std::string, ns3lxc::IfaceProvider *> ifacesProvided; //keep a ref to the providers we contain
    ns3lxc::Iface *getIface(std::string ifaceName);
};

class IfaceAccepter {
public:
    std::map<std::string, std::string> ifacesAcceptedSubNames; //maps this level's iface names to lower level's
    std::map<std::string, ns3lxc::IfaceAccepter *> ifacesAccepted; //keep a ref to who below us accepts ifaces
    int connectIface(std::string ifaceName, Iface *iface);
};

class Iface : public IfaceProvider {
public:
	std::string name;
	ns3lxc::Node *node;
	ns3lxc::Link *link;
	IpAddr *address;
	ns3lxc::Iface *getIface(std::string ifaceName) { return this; }

    Iface();
};

}

#endif