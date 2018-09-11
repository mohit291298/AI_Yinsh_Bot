#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "Node.h"
#include "Boardclass.h"

using namespace std;

// constructor
Node::Node(Boardclass b){
	state.copy_board(b);
	//num_child = 0;
	move = "";
	h = 0;
}
