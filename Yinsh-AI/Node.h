#include <string>
#include <cstring>
#include <vector>
#include "Boardclass.h"
#ifndef NODE_H
#define NODE_H

using namespace std;

class Node
{

public:
	Boardclass state;
	double h;
	string move;
	//int num_child;
	vector<Node*> children;

    Node(Boardclass b);
  
};
 
#endif