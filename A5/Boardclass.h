#include <string>
#include <cstring>
#include <vector>

#ifndef BOARDCLASS_H
#define BOARDCLASS_H

using namespace std;

class Boardclass
{

public:
	int board[13][13];
	int my_ringsonboard,opp_ringsonboard;
    int N,M,K;
	// int my_rings_x[5],my_rings_y[5];
	// int opp_rings_x[5],opp_rings_y[5];

    Boardclass();
 
    void reverse_update(string str,int p);
    void update_board(string str,int p);
    void convtodavid(int a,int b,int *arr);
    void convtorad(int a,int b,int *arr);
    void copy_board(Boardclass& b);
    vector<int> find_row(int p);
    void find_rings(int *opp_rings_x,int *opp_rings_y,int *my_rings_x,int *my_rings_y,int &num_opp,int &num_my);

    // void my_set(int x,int y,int i);
    // void opp_set(int x,int y,int i);
    // void num_rings_set(int a,int b);
};
 
#endif