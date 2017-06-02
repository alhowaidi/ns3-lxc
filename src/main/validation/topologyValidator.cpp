#include <string>
#include <vector>
#include <iostream>

#include "errorCode.h"
#include "topology.h"
#include "nodeValidator.h"
#include "topologyValidator.h"

using namespace std;

void validateTopology(ns3lxc::Topology *top){
    bool fail = false;
    if(top->name == ""){
        cerr << "A Topology has no name" << endl;
        fail = true;
    }

    for(auto nodePtr : top->nodes){
        if(top->nodeMap.at(nodePtr->origName) != nodePtr){
            cerr << "Node " + nodePtr->name + " not mapped correctly" << endl;
            fail = true;
        }
        validateNode(nodePtr);
    }
    for(auto linkPtr : top->links){
        if(top->linkMap.at(linkPtr->origName) != linkPtr){
            cerr << "Link " + linkPtr->name + " not mapped correctly" << endl;
            fail = true;
        }
    }
    for(auto subTopPtr : top->subTopologies){
        if(top->topMap.at(subTopPtr->origName) != subTopPtr){
            cerr << "Sub Topology " + subTopPtr->name + " not mapped properly" << endl;
            fail = true;
        }
        validateTopology(subTopPtr.get());
    }

    if(fail){
        throw Ns3lxcException(ErrorCode::TOPOLOGY_INVALID, top->name);
    }
}