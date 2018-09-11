#include <string>
#include <cstring>

#ifndef BOARDCLASS_H
#define BOARDCLASS_H

using namespace std;

class Boardclass
{

public:
	int board[11][11];
	int my_ringsonboard,opp_ringsonboard;
	int my_rings_x[5],my_rings_y[5];
	int opp_rings_x[5],opp_rings_y[5];

    Boardclass();
 
    void update_board(string str,int p);
    void convtodavid(int a,int b,int *arr);
 
};
 
#endif