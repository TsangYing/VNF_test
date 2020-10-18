#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include "flow_instance.h"
#include "flow_type.h"
#include "link.h"
#include "node.h"
#include "VNF_instance.h"
#include "VNF_type.h"

using namespace std;
#define node_capacity  100;
#define node_process  100;
//#define node_level  5;
#define link_bandwidth 100;
void Topo_node(int);
void Topo_link(int);
vector<node>graph_n;
vector<link_non_directionality>graph_l;


int main( void ){   
    unsigned seed;
    seed = (unsigned)time(NULL); // 取得時間序列
    srand(seed); // 以時間序列當亂數種子
    int node_number;
    int link_number;
    int VNF_type_number;
    int flow_type_number;
    int amount_of_demand;
    cin>>node_number>>link_number>>VNF_type_number>>flow_type_number>>amount_of_demand;
    Topo_node(node_number);
    Topo_link(link_number);
    
    return 0; 
}

void Topo_node(int x){
     for (int i = 0; i < x; i++)
    {
        node tmp;
        tmp.node_id = i;
        tmp.capacity = node_capacity;
        tmp.procees = node_process;
        //tmp.level = rand()%node_level;
        graph_n.push_back(tmp);
    }
//--------------test--------------
    // for (int i = 0; i < graph.size(); i++)
    // {
    //     cout<<"node id:"<<graph[i].node_id<<" capacity:"<<graph[i].capacity<<" procees:"<<graph[i].procees<<endl;
    // }
} 

void Topo_link(int x){
    int check_parameter_min  =  graph_n.size()-1;
    int check_parameter_Max  =  graph_n.size()*(graph_n.size()-1)/2;
    if(x<check_parameter_min||x>check_parameter_Max){
        cout<<"error parameter";
        return;
    }
    int link_amount_check = 0;
    vector<node>use_node;
    vector<node>unuse_node;
    node first_node = graph_n[rand()%graph_n.size()];
    use_node.push_back(first_node);
    for (int i = 0; i < graph_n.size(); i++){
        if(graph_n[i].node_id==first_node.node_id)
            continue;
        else
            unuse_node.push_back(graph_n[i]);
    }
    for (int i = 0; i < unuse_node.size(); i++){
        node connect_node = use_node[rand()%use_node.size()];
        link_non_directionality tmp;
        tmp.id = graph_l.size();
        tmp.source_node = unuse_node[i];
        tmp.destination_node = connect_node;
        tmp.bandwidth_capacity = link_bandwidth;
        graph_l.push_back(tmp);
        use_node.push_back(unuse_node[i]);
        link_amount_check+=1;         
    }

    while (link_amount_check<x){
        int N1 = rand()%graph_n.size();
        int N2 = rand()%graph_n.size();
        bool link_check = true; 
        for (int i = 0; i < graph_l.size(); i++){
            if((graph_l[i].source_node.node_id==N1&&graph_l[i].destination_node.node_id==N2)||(graph_l[i].source_node.node_id==N2&&graph_l[i].destination_node.node_id==N1)){
                link_check = false;
            }
            else if(N1==N2){
                link_check = false;
            }
        }
        if(link_check==false)
            continue;
        else{
            link_non_directionality tmp;
            tmp.id = graph_l.size();
            tmp.source_node = graph_n[N1];
            tmp.destination_node = graph_n[N2];
            tmp.bandwidth_capacity = link_bandwidth;
            graph_l.push_back(tmp);
            link_amount_check+=1;
        }
        
    }
    
    

    
//--------------test--------------
        for (int i = 0; i < graph_l.size(); i++)
    {
        cout<<"node id:"<<graph_l[i].id<<" source:"<<graph_l[i].source_node.node_id<<" destination:"<<graph_l[i].destination_node.node_id<<endl;
    }
} 

// void Topo_link(int x){
//     int check_parameter  =  graph_n.size()-1;
//     if(x<check_parameter){
//         cout<<"error parameter";
//         return;
//     }

//     vector<int>check;
//     for (int i = 0; i < graph_n.size(); i++)
//     {
//         int tmp = i;
//         check.push_back(tmp);
//     }

//     random_shuffle ( check.begin(), check.end() );

//     for(int i=1;i<check.size();i++){
//         link_non_directionality tmp;
//         tmp.source_node =  graph_n[i-1];
//         tmp.destination_node = graph_n[i];
//         graph_l.push_back(tmp);
//     }


//     for(int i=0;i<x-check_parameter;i++){
//         int b = rand()%graph_n.size();
//         int c = rand()%graph_n.size();

//         for (int i = 0; i < graph_l.size(); i++)
//         {
            
//         }
//         if (b==c)
//             continue;
//         else{
//             link_non_directionality tmp;
//             tmp.source_node =  graph_n[b];
//             tmp.destination_node = graph_n[c];
//             graph_l.push_back(tmp);
//         }

//     }
//     bool check_connect = false;
//     while (check_connect != true)
//     {
//         vector<int>check;
//         for (int i = 0; i < graph_n.size(); i++)
//         {
//             int tmp = i;
//             check.push_back(tmp);
//         }


//         random_shuffle ( check.begin(), check.end() );

        





        
//         int a = 0;
//         while(a>=x){
//             int b = rand()%graph_n.size();
//             int c = rand()%graph_n.size();
//             for (int i = 0; i < graph_l.size(); i++)
//             {
                
//             }
            

//             if (b==c)
//                 continue;
//             else{
//                 link_non_directionality tmp;
//                 tmp.source_node =  graph_n[b];
//                 tmp.destination_node = graph_n[c];
//                 graph_l.push_back(tmp);
//             }
//         }

//         for (int i = 0; i < graph_l.size(); i++)
//         {
//             for (int j = 0; j < check.size(); j++)
//             {
//                 if(graph_l[i].source_node.node_id==check[j] || graph_l[i].destination_node.node_id==check[j])
//                 {
//                     check[j]=0;
//                 }
//             }
//         }

//         for (int i = 0; i < check.size(); i++)
//         {
//             if(check[i]==0){
//                 continue;
//                 if(i==check.size()-1)
//                     check_connect = true;
//             }
//             else{
//                 break;
//             }
//         }


//     }
// //--------------test--------------
//     cout<<"linknumber     soucer    destination";
//     for (int i = 0; i < graph_l.size(); i++)
//     {
//         cout<<i<<"  "<<graph_l[i].source_node.node_id<<"    "<<graph_l[i].destination_node.node_id;
//     }

// }