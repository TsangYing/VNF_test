#ifndef FLOW_H
#define FLOW_H

#include <vector>
#include "VNF_instance.h"
using namespace std;

class flow_type{
    public: 
        int  ID;//
        int bandwidth;
        vector<VNF_type>type_demand;//   
};



#endif
