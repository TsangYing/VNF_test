#ifndef VNF_INSTANCE_H
#define VNF_INSTANCE_H

#include "VNF_type.h"

class VNF_instance{
    public:
        VNF_type VNF;
        int instance_id; //number of instance  
        int admitted;     
};

#endif