#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <stdlib.h>
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
#define VNF_type_capacity 10;
#define VNF_type_max_limit 10;
#define VNF_type_process 10;
#define flow_type_max_long 10;
void Topo_node(int);
void Topo_link(int);
void Topo_VNF(int);
void Topo_flow(int);
void Topo_demand(int);
vector<node>graph_n;
vector<link_non_directionality>graph_l;
vector<VNF_type>kind_of_VNF; //all type of VNF
vector<flow_type>kind_of_flow; //all type of flow
vector<flow_instance>amount_of_demand; //Total of demand
int main( void ){   
    unsigned seed;
    seed = (unsigned)time(NULL); 
    srand(seed); 
    int node_number;
    int link_number;
    int VNF_type_number;
    int flow_type_number;
    int amount_of_demand;
    
    cin>>node_number>>link_number>>VNF_type_number>>flow_type_number>>amount_of_demand;
    Topo_node(node_number);
    Topo_link(link_number);
    Topo_VNF(VNF_type_number);
    //fout<<flow_type_number<<endl;
    Topo_flow(flow_type_number);
    Topo_demand(amount_of_demand);

    return 0; 
}

void Topo_node(int x){
    for (int i = 0; i < x; i++)
    {
        node tmp;
        tmp.node_id = i;
        tmp.capacity = node_capacity;
        //tmp.level = rand()%node_level;
        graph_n.push_back(tmp);
    }
//--------------test--------------
    // for (int i = 0; i < graph_n.size(); i++){
    //     cout<<graph_n[i].node_id<<" "<<graph_n[i].capacity<<endl;
    // }
    // cout<<endl;
//--------------------------------  
ofstream fout("node.txt");
    for (int i = 0; i < graph_n.size(); i++){
        fout<<graph_n[i].node_id<<" "<<graph_n[i].capacity<<endl;
    }
    fout<<endl;
    
} 

void Topo_link(int x){//rand link
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
    // for (int i = 0; i < graph_l.size(); i++)
    // {
    //     cout<<graph_l[i].id<<" "<<graph_l[i].source_node.node_id<<" "<<graph_l[i].destination_node.node_id<<" "<<graph_l[i].bandwidth_capacity<<endl;
    // }
    // cout<<endl;
//--------------------------------
ofstream fout("link.txt");
    for (int i = 0; i < graph_l.size(); i++)
    {
        fout<<graph_l[i].id<<" "<<graph_l[i].source_node.node_id<<" "<<graph_l[i].destination_node.node_id<<" "<<graph_l[i].bandwidth_capacity<<endl;
    }
    fout<<endl;
} 

void Topo_VNF(int x){
    for (int i = 0; i < x; i++)
    {
        VNF_type tmp;
        tmp.type = i;
        tmp.capacity = VNF_type_capacity;
        tmp.max_limit = VNF_type_max_limit;
        tmp.procees = 1+rand()%VNF_type_process;
        kind_of_VNF.push_back(tmp);
    }
//--------------test--------------
    // for (int i = 0; i < kind_of_VNF.size(); i++)
    // {
    //      cout<<kind_of_VNF[i].type<<" "<<kind_of_VNF[i].capacity<<" "<<kind_of_VNF[i].max_limit<<endl;
    // }
    // cout<<endl;
//--------------------------------
ofstream fout("VNF.txt");
    for (int i = 0; i < kind_of_VNF.size(); i++)
    {
         fout<<kind_of_VNF[i].type<<" "<<kind_of_VNF[i].capacity<<" "<<kind_of_VNF[i].max_limit<<endl;
    }
    fout<<endl;
}

void Topo_flow(int x){
    for (int i = 0; i < x; i++)
    {
        flow_type tmp;
        tmp.ID = i;
        int y = 1+rand()%flow_type_max_long;//long of demand
        for (int j = 0; j < y; j++)
        {
            int z = rand()%kind_of_VNF.size();
            tmp.type_demand.push_back(kind_of_VNF[z]);
            tmp.bandwidth+=kind_of_VNF[z].procees;
        }
        tmp.bandwidth/=y;
        kind_of_flow.push_back(tmp);
    }
//--------------test--------------
    // for (int i = 0; i <  kind_of_flow.size(); i++)
    // {
    //      cout<<"flow id:"<< kind_of_flow[i].ID<<endl;
    //      for (int j = 0; j <  kind_of_flow[i].type_demand.size(); j++)
    //      {
    //          cout<< kind_of_flow[i].type_demand[j].type<<" ";
    //      }
    //      cout<<endl<<"bandwidth:"<<kind_of_flow[i].bandwidth<<endl;
         
    // }
    ofstream fout("flow.txt");
    for (int i = 0; i <  kind_of_flow.size(); i++)
    {
         fout<< kind_of_flow[i].ID<<endl;
         for (int j = 0; j <  kind_of_flow[i].type_demand.size(); j++)
         {
             fout<< kind_of_flow[i].type_demand[j].type<<" ";
         }
         fout<<endl<<kind_of_flow[i].bandwidth<<endl;
         
    }
}

void Topo_demand(int x){
   for (int i = 0; i < x; i++)
    {
        flow_instance tmp;
        int y = rand()%kind_of_flow.size();
        tmp.flow = kind_of_flow[y];
        tmp.ID =i;
        amount_of_demand.push_back(tmp);
    } 
//--------------test--------------
//   for (int i = 0; i <  amount_of_demand.size(); i++)
//     {
//          cout<< amount_of_demand[i].ID<<" "<<amount_of_demand[i].flow.type_demand.size()<<endl;
//          for (int j = 0; j <  amount_of_demand[i].flow.type_demand.size(); j++)
//          {
//              cout<< amount_of_demand[i].flow.type_demand[j].type<<" ";
//          }
//          cout<<endl<<amount_of_demand[i].flow.bandwidth<<endl;
         
//     }
//--------------------------------
ofstream fout("demand.txt");
    for (int i = 0; i <  amount_of_demand.size(); i++)
    {
         fout<< amount_of_demand[i].ID<<" "<<amount_of_demand[i].flow.type_demand.size()<<" ";
         for (int j = 0; j <  amount_of_demand[i].flow.type_demand.size(); j++)
         {
             fout<< amount_of_demand[i].flow.type_demand[j].type<<" ";
         }
         fout<<" "<<amount_of_demand[i].flow.bandwidth<<endl;
    }

}