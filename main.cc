#include <iostream>
#include <fstream>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <string>
#include "flow_instance.h"
#include "flow_type.h"
#include "link.h"
#include "node.h"
#include "VNF_instance.h"
#include "VNF_type.h"
#include "ortools/linear_solver/linear_solver.h"



namespace operations_research {
void SimpleLpProgram() {
  // Create the linear solver with the GLOP backend.
  MPSolver solver("vnf_lp_program", MPSolver::GLOP_LINEAR_PROGRAMMING);

  // Create the variables x and y.
  for (int i = 0; i < 10; i++)
  {
    MPVariable* const x = solver.MakeNumVar(0.0, i, "x");
  }
  
  MPVariable* const x = solver.MakeNumVar(0.0, 1, "x");
  MPVariable* const y = solver.MakeNumVar(0.0, 2, "y");

  LOG(INFO) << "Number of variables = " << solver.NumVariables();

  // Create a linear constraint, 0 <= x + y <= 2.
  MPConstraint* const ct = solver.MakeRowConstraint(0.0, 2.0, "ct");
  ct->SetCoefficient(x, 1);
  ct->SetCoefficient(y, 1);

  LOG(INFO) << "Number of constraints = " << solver.NumConstraints();

  // Create the objective function, 3 * x + y.
  MPObjective* const objective = solver.MutableObjective();
  objective->SetCoefficient(x, 3);
  objective->SetCoefficient(y, 1);
  objective->SetMaximization();

  solver.Solve();

  LOG(INFO) << "Solution:" << std::endl;
  LOG(INFO) << "Objective value = " << objective->Value();
  LOG(INFO) << "x = " << x->solution_value();
  LOG(INFO) << "y = " << y->solution_value();
}
}  // namespace operations_research


vector<node>graph_n;
vector<link_non_directionality>graph_l;
vector<VNF_type>kind_of_VNF; //all type of VNF
vector<flow_type>kind_of_flow; //all type of flow
vector<flow_instance>amount_of_demand; //Total of demand
void readinput();

int main() {
  operations_research::SimpleLpProgram();
  //readinput();
  for (int i = 0; i <graph_n.size(); i++)
  {
    cout<<graph_n[i].node_id<<" "<<graph_n[i].capacity<<endl;
  }
  return EXIT_SUCCESS;
}

void readinput(){
  fstream file1,file2,file3,file4,file5,file6,file7;
  file1.open("/home/user/Desktop/C++/node.txt",ios::in);
  file2.open("/home/user/Desktop/C++/link.txt",ios::in);
  file3.open("/home/user/Desktop/C++/VNF.txt",ios::in);
  file4.open("/home/user/Desktop/C++/demand.txt",ios::in);
  if (!file1) {
		cout << "node.txt cannot be opened" << endl;
		return;
	}
  else{
    while (!file1.eof()) {
    node tmp;
		file1 >> tmp.node_id>>tmp.capacity;
		graph_n.push_back(tmp);
	  }
  file1.close();
  }
	if (!file2) {
		cout << "link.txt cannot be opened" << endl;
		return;
	}
  else{
    while (!file2.eof()) {
    link_non_directionality tmp;
		file2 >>tmp.id>>tmp.source_node.node_id>>tmp.destination_node.node_id>>tmp.bandwidth_capacity;
		graph_l.push_back(tmp);
	  }
  file2.close();
  }
	if (!file3) {
		cout << "VNF.txt cannot be opened" << endl;
		return;
	}
  else{
    while (!file3.eof()) {
    VNF_type tmp;
		file3 >>tmp.type>>tmp.capacity>>tmp.max_limit;
    kind_of_VNF.push_back(tmp);
	  }
  file3.close();
  }
  if (!file4) {
		cout << "demand.txt cannot be opened" << endl;
		return;
	}
}