#ifndef NODE_H
#define NODE_H

#include <vector>
#include "VNF_instance.h"
#include <set>
using namespace std;

class node{
    public:
        int node_id;
        int level;
        int capacity;//node capacity
        int procees; //node procees capacity 
        vector<VNF_instance>VNF;// install tpye of VNF in node  
};



#endif
