#ifndef FLOW_INSTANCE_H
#define FLOW_INSTANCE_H

#include <vector>
#include "flow_type.h"
using namespace std;

class flow_instance{
    public: 
        flow_type flow ;
        int ID;
        int admitted = 0; 
        vector<VNF_instance>VNF;
};



#endif
