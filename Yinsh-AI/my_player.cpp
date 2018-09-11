#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include "Boardclass.h"
#include "Node.h"
//#include <time>

using namespace std;

#define matrix_size 11;

// int board[11][11];
/*-1 -> INVALID Position
0 -> EMPTY position
1 -> MY marker
2 -> OPPONENT's marker
3 -> MY ring
4 -> OPPONENT's ring
*/

// int ringsonboard;
// int rings_x[5],rings_y[5];

std::string trim(const std::string& str,
                 const std::string& whitespace = " \t")
{
    int strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    int strEnd = str.find_last_not_of(whitespace);
    int strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

//p=1 if my chance(max node)
//p=0 if opp chance(min node)

string convtorad(int x,int y){
	//convert here

	ostringstream str1,str2;
	str1 << x;
	str2 <<y;
	return (str1.str() + " " + str2.str());
}

void successor(Node n,int p){
	int x,y,x1,y1,z1;
	string ring_rad;
	int val;
	string str;
	for(int i=0;i<(n.state.my_ringsonboard);i++){
		x = n.state.my_rings_x[i];
		y = n.state.my_rings_y[i];
		ring_rad = convtorad(x,y);

		//5 rings code
		
		y1 = y++;
		x1 = x;
		if(y1<=5){
			val = n.state.board[x1+5][y1+5];
			while(val == 0 || val == 1 || val == 2){
				if(val==0){
					Node t(n.state);
					t.state.board[x+5][y+5] = 1;
					t.state.board[x1+5][y1+5] = 3;
					t.state.my_rings_x[i] = x1;
					t.state.my_rings_y[i] = y1;
					//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
					n.children.push_back(&t);
				}
				else{
					Node t(n.state);
					while(val==1 || val==2){
						t.state.board[x1+5][y1+5] = (t.state.board[x1+5][y1+5] % 2) + 1;
						y1++;
						if(y1>5)
							break;
						val = n.state.board[x1+5][y1+5];
					}
					if(val==0 && y1<=5){
						t.state.board[x+5][y+5] = 1;
						t.state.board[x1+5][y1+5] = 3;
						t.state.my_rings_x[i] = x1;
						t.state.my_rings_y[i] = y1;
						//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
						n.children.push_back(&t);					
					}
				}
				y1++;
				if(y1>5)
					break;
				val = n.state.board[x1+5][y1+5];
			}
		}
		y1 = y--;
		x1 = x;
		if(y1>=-5){
			val = n.state.board[x1+5][y1+5];
			while(val == 0 || val == 1 || val == 2){
				if(val==0){
					Node t(n.state);
					t.state.board[x+5][y+5] = 1;
					t.state.board[x1+5][y1+5] = 3;
					t.state.my_rings_x[i] = x1;
					t.state.my_rings_y[i] = y1;
					//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
					n.children.push_back(&t);
				}
				else{
					Node t(n.state);
					while(val==1 || val==2){
						t.state.board[x1+5][y1+5] = (t.state.board[x1+5][y1+5] % 2) + 1;
						y1--;
						if(y1<-5)
							break;
						val = n.state.board[x1+5][y1+5];
					}
					if(val==0 && y1>=-5){
						t.state.board[x+5][y+5] = 1;
						t.state.board[x1+5][y1+5] = 3;
						t.state.my_rings_x[i] = x1;
						t.state.my_rings_y[i] = y1;
						//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
						n.children.push_back(&t);					
					}
				}
				y1--;
				if(y1<-5)
					break;
				val = n.state.board[x1+5][y1+5];
			}
		}
		y1 = y;
		x1 = x++;
		if(x1<=5){
			val = n.state.board[x1+5][y1+5];
			while(val == 0 || val == 1 || val == 2){
				if(val==0){
					Node t(n.state);
					t.state.board[x+5][y+5] = 1;
					t.state.board[x1+5][y1+5] = 3;
					t.state.my_rings_x[i] = x1;
					t.state.my_rings_y[i] = y1;
					//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
					n.children.push_back(&t);
				}
				else{
					Node t(n.state);
					while(val==1 || val==2){
						t.state.board[x1+5][y1+5] = (t.state.board[x1+5][y1+5] % 2) + 1;
						x1++;
						if(x1>5)
							break;
						val = n.state.board[x1+5][y1+5];
					}
					if(val==0 && x1<=5){
						t.state.board[x+5][y+5] = 1;
						t.state.board[x1+5][y1+5] = 3;
						t.state.my_rings_x[i] = x1;
						t.state.my_rings_y[i] = y1;
						//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
						n.children.push_back(&t);					
					}
				}
				x1++;
				if(x1>5)
					break;
				val = n.state.board[x1+5][y1+5];
			}
		}
		y1 = y;
		x1 = x--;
		if(x1>=-5){
			val = n.state.board[x1+5][y1+5];
			while(val == 0 || val == 1 || val == 2){
				if(val==0){
					Node t(n.state);
					t.state.board[x+5][y+5] = 1;
					t.state.board[x1+5][y1+5] = 3;
					t.state.my_rings_x[i] = x1;
					t.state.my_rings_y[i] = y1;
					//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
					n.children.push_back(&t);
				}
				else{
					Node t(n.state);
					while(val==1 || val==2){
						t.state.board[x1+5][y1+5] = (t.state.board[x1+5][y1+5] % 2) + 1;
						x1--;
						if(x1<-5)
							break;
						val = n.state.board[x1+5][y1+5];
					}
					if(val==0 && x1>=-5){
						t.state.board[x+5][y+5] = 1;
						t.state.board[x1+5][y1+5] = 3;
						t.state.my_rings_x[i] = x1;
						t.state.my_rings_y[i] = y1;
						//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
						n.children.push_back(&t);					
					}
				}
				x1--;
				if(x1<-5)
					break;
				val = n.state.board[x1+5][y1+5];
			}
		}
		y1 = y++;
		x1 = x++;
		if(y1<=5 && x1<=5){
			val = n.state.board[x1+5][y1+5];
			while(val == 0 || val == 1 || val == 2){
				if(val==0){
					Node t(n.state);
					t.state.board[x+5][y+5] = 1;
					t.state.board[x1+5][y1+5] = 3;
					t.state.my_rings_x[i] = x1;
					t.state.my_rings_y[i] = y1;
					//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
					n.children.push_back(&t);
				}
				else{
					Node t(n.state);
					while(val==1 || val==2){
						t.state.board[x1+5][y1+5] = (t.state.board[x1+5][y1+5] % 2) + 1;
						y1++;
						x1++;
						if(y1>5 || x1>5)
							break;
						val = n.state.board[x1+5][y1+5];
					}
					if(val==0 && y1<=5 && x1<=5){
						t.state.board[x+5][y+5] = 1;
						t.state.board[x1+5][y1+5] = 3;
						t.state.my_rings_x[i] = x1;
						t.state.my_rings_y[i] = y1;
						//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
						n.children.push_back(&t);					
					}
				}
				y1++;
				x1++;
				if(y1>5 || x1>5)
					break;
				val = n.state.board[x1+5][y1+5];
			}
		}
		y1 = y--;
		x1 = x--;
		if(y1>=-5 && x1>=-5){
			val = n.state.board[x1+5][y1+5];
			while(val == 0 || val == 1 || val == 2){
				if(val==0){
					Node t(n.state);
					t.state.board[x+5][y+5] = 1;
					t.state.board[x1+5][y1+5] = 3;
					t.state.my_rings_x[i] = x1;
					t.state.my_rings_y[i] = y1;
					//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
					n.children.push_back(&t);
				}
				else{
					Node t(n.state);
					while(val==1 || val==2){
						t.state.board[x1+5][y1+5] = (t.state.board[x1+5][y1+5] % 2) + 1;
						y1--;
						x1--;
						if(y1<-5 || x1<-5)
							break;
						val = n.state.board[x1+5][y1+5];
					}
					if(val==0 && y1>=-5 && x1>=-5){
						t.state.board[x+5][y+5] = 1;
						t.state.board[x1+5][y1+5] = 3;
						t.state.my_rings_x[i] = x1;
						t.state.my_rings_y[i] = y1;
						//5 rings code
					t.move += ("S "+ ring_rad +" M " + convtorad(x1,y1));
						n.children.push_back(&t);					
					}
				}
				y1--;
				x1--;
				if(y1<-5 || x1<-5)
					break;
				val = n.state.board[x1+5][y1+5];
			}
		}

	}
}

int main(){

	string str;
	getline(cin, str);
	string str2 = trim(str);
	char cstr[str2.size() +1];
	strcpy(cstr,str2.c_str());
	char *token = strtok(cstr, " ");
	int player = atoi(token) - 1;
	token = strtok(NULL, " ");
	int n = atoi(token);
	token = strtok(NULL, " ");
	int time_left = atoi(token);


	// for(int i=0;i<11;i++){
	// 	for(int j=0;j<11;j++)
	// 		cout<<board[i][j]<<" ";
	// 	cout<<"\n";
	// }
	Boardclass main_board;
	// main_board.board[2][3] = 2;
	// main_board.my_ringsonboard = 3;
	// Boardclass main_board2;
	// main_board2.copy_board(main_board);

	// main_board2.board[2][3] = 6;
	// main_board2.my_ringsonboard = 9;

	// main_board.board[2][3] = 3;
	// main_board.my_ringsonboard = 4;

	// cout<<main_board.board[2][3]<<"\n";
	// cout<<main_board.my_ringsonboard<<"\n\n";
	// cout<<main_board2.board[2][3]<<"\n";
	// cout<<main_board2.my_ringsonboard<<"\n";

	if(player==1){
		getline(cin, str);
		main_board.update_board(str,2);
	}
	while(1){

		//cout<<"your move";//code it
		getline(cin, str);
		main_board.update_board(str,2);
		cout<<"\n";
		for(int i=0;i<11;i++){
			for(int j=0;j<11;j++)
				cout<<main_board.board[i][j]<<" ";
			cout<<"\n";
		}

	}	



}