#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "Node.h"
#include "Boardclass.h"

using namespace std;

// constructor
Node::Node(int p1){
	//state.copy_board(b);
	//num_child = 0;
	//move = "";
	visited = 0;
	p = p1;
	h = 0;
}
