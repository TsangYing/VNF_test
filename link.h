#ifndef LINK_H
#define LINK_H
#include "node.h"
#include <vector>
using namespace std;



class link_non_directionality{
    public:
        int id;
        node source_node;
        node destination_node;
        int bandwidth_capacity;
};

// class link_directionality{
//     public:
//         link_non_directionality a;
//         link_non_directionality b;
//         link_directionality(){
//             b.source_id = a.destination_id;
//             b.destination_id = a.source_id;
//             b.capacity = a.capacity;
//         };
// };


#endif
