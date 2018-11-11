#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <fstream>
#include "Boardclass.h"
#include "Node.h"
//#include <time>

using namespace std;

#define matrix_size 11;
#define DBL_MAX 1000000;
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

int N,M,K;

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

int myRingPlacement(Boardclass& b, int marker_i, int marker_j){
    int ring_affect = 0;
    //right
    marker_i = marker_i + 6;
    marker_j = marker_j + 6;

    int next = marker_j + 1;
    while( next < 13 ){
        if (b.board[marker_i][next] == 4 || b.board[marker_i][next] == -1){
            break;
        }
        else if (b.board[marker_i][next] == 3){
            ring_affect ++;
            break;
        }
        next++ ;
    }

    //left
    int prev = marker_j - 1;
    while ( prev >= 0 ){
        if (b.board[marker_i][prev] == 4 || b.board[marker_i][prev] == -1){
            break;
        }
        else if (b.board[marker_i][prev] == 3){
            ring_affect ++;
            break;
        }
        prev-- ;
    }

    //down
    int down = marker_i + 1;
    while( down < 13 ){
        if (b.board[down][marker_j] == 4 || b.board[down][marker_j] == -1){
            break;
        }
        else if (b.board[down][marker_j] == 3){
            ring_affect ++;
            break;
        }
        down++ ;
    }

    //up 
    int up = marker_i - 1;
    while( up >= 0 ){
        if (b.board[up][marker_j] == 4 || b.board[up][marker_j] == -1){
            break;
        }
        else if (b.board[up][marker_j] == 3){
            ring_affect ++;
            break;
        }
        up-- ;
    }

    // down right
    next = marker_j + 1;
    down = marker_i + 1;
    while( next < 13 && down < 13 ){
        if (b.board[down][next] == 4 || b.board[down][next] == -1){
            break;
        }
        else if (b.board[down][next] == 3){
            ring_affect ++;
            break;
        }
        next++;
        down++;
    }

    // up left
    prev = marker_j - 1;
    up = marker_i - 1;
    while( prev >= 0 && up >= 0 ){
        if (b.board[up][prev] == 4 || b.board[up][prev] == -1){
            break;
        }
        else if (b.board[up][prev] == 3){
            ring_affect ++;
            break;
        }
        up--;
        prev--;
    }

    return ring_affect;

}

/* number of my markers that are affected by opponent rings */
int oppRingPlacement(Boardclass& b, int marker_i, int marker_j){
    int ring_affect = 0;
    //right

    marker_i = marker_i + 6;
    marker_j = marker_j + 6;

    int next = marker_j + 1;
    while( next < 13 ){
        if (b.board[marker_i][next] == 3 || b.board[marker_i][next] == -1){
            break;
        }
        else if (b.board[marker_i][next] == 4){
            ring_affect ++;
            break;
        }
        next++ ;
    }

    //left
    int prev = marker_j - 1;
    while ( prev >= 0 ){
        if (b.board[marker_i][prev] == 3 || b.board[marker_i][prev] == -1){
            break;
        }
        else if (b.board[marker_i][prev] == 4){
            ring_affect ++;
            break;
        }
        prev-- ;
    }

    //down
    int down = marker_i + 1;
    while( down < 13 ){
        if (b.board[down][marker_j] == 3 || b.board[down][marker_j] == -1){
            break;
        }
        else if (b.board[down][marker_j] == 4){
            ring_affect ++;
            break;
        }
        down++ ;
    }

    //up 
    int up = marker_i - 1;
    while( up >= 0 ){
        if (b.board[up][marker_j] == 3 || b.board[up][marker_j] == -1){
            break;
        }
        else if (b.board[up][marker_j] == 4){
            ring_affect ++;
            break;
        }
        up-- ;
    }

    // down right
    next = marker_j + 1;
    down = marker_i + 1;
    while( next < 13 && down < 13 ){
        if (b.board[down][next] == 3 || b.board[down][next] == -1){
            break;
        }
        else if (b.board[down][next] == 4){
            ring_affect ++;
            break;
        }
        next++;
        down++;
    }

    // up left
    prev = marker_j - 1;
    up = marker_i - 1;
    while( prev >= 0 && up >= 0 ){
        if (b.board[up][prev] == 3 || b.board[up][prev] == -1){
            break;
        }
        else if (b.board[up][prev] == 4){
            ring_affect ++;
            break;
        }
        up--;
        prev--;
    }

    return ring_affect;
}

string convtorad(int a,int b){
	//convert radial to david coordinates
	int arr[2];
	arr[0] = a;
	arr[1] = b;
	// assuming a is the x - coordinate 
	// assuming b is the y - coordinate 

	if (!(a == 0 && b == 0)){

		if ( a * b >= 0) {
			arr[0] = max(abs(a),abs(b));
		}
		else {
			arr[0] = abs(a) + abs(b);
		}
		
		if ( b == arr[0] ) {
			arr[1] = a;
			//return;
		}
		
		else if ( a == arr[0] ) {
			arr[1] =  2 * arr[0] - b; 
			//return;
		}

		else if ( b == -1 * arr[0] ) {
			arr[1] = 3 * arr[0] - a ;
			//return;
		}

		else if ( a == -1 * arr[0] ){
			arr[1] =  5 * arr[0] + b;
			//return;
		}

		else if ( a * b < 0 ){
			if ( a > 0 ){
				arr[1] = 2 * arr[0] - b;
				//return;
			}
			else if ( b > 0 ){
				arr[1] = 6 * arr[0] + a;
				//return;
			}
		}
	}
	ostringstream str1,str2;
	str1 << arr[0];
	str2 <<arr[1];
	return (str1.str() + " " + str2.str());
}

void rsre(Boardclass& b,int a1,int b1,int a2,int b2,int color){
				// cout<<"In rsre if\n";

	int p1 = a1;
	int q1 = b1;
	if(a1==a2){
		if(b2>b1){
			while(q1!=b2){
				b.board[p1+6][q1+6] = color;
				q1++;
			}
		}
		else{
			while(q1!=b2){
				b.board[p1+6][q1+6] = color;
				q1--;
			}					
		}
		b.board[a2+6][b2+6]=color;
	}
	else if(b1==b2){
		if(a2>a1){
			while(p1!=a2){
				b.board[p1+6][q1+6] = color;
				p1++;
			}
		}
		else{
			while(p1!=a2){
				b.board[p1+6][q1+6] = color;
				p1--;
			}					
		}
		b.board[a2+6][b2+6]=color;
	}
	else{
		if(b2>b1){
			while(q1!=b2){
				b.board[p1+6][q1+6] = color;
				q1++;
				p1++;
			}
		}
		else{
			while(q1!=b2){
				b.board[p1+6][q1+6] = color;
				q1--;
				p1--;
			}					
		}
		b.board[a2+6][b2+6]=color;
	}

}

void extend_after_S(Node*& n,Boardclass& b,vector<int>& row,int p,string str){
	// vector<int> row;
	// row.swap(b.find_row(p));
	// cout<<"In 1 extend_after_S if\n";
	int num_rings;
	string str1,str2,str3;
	std::vector<int> temp_row;
			int opp_rings_x[6],opp_rings_y[6],my_rings_x[6],my_rings_y[6];
		int num_opp,num_my;

	b.find_rings(opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);

	if(p!=1)
		num_rings = num_opp;
	else
		num_rings = num_my;
	if(row.size()==0 || num_rings<=(M-3)){
		//reverse_board(t.move[0],p);
		Node* t = new Node((p%2) + 1);
		//cout<<t->p<<"\n";
		//t->visited = 1;
		t->move = str;
				// cout<<"Node created\n";

		// cout<<str<<"\n";
		// n->move = "123";
		n->children.push_back(t);
	}
	else{
		int it1=0;
		int it2 = row.size();
		int x1,y1,x2,y2;
		int tempx,tempy;
		while(it1<it2){
			x1 = row[it1];
			y1 = row[it1 + 1];
			x2 = row[it1 + 2];
			y2  = row[it1 + 3];
			rsre(b,x1,y1,x2,y2,0);
			str1 = str + (" RS "+ convtorad(x1,y1) +" RE " + convtorad(x2,y2));
			int opp_rings_x[6],opp_rings_y[6],my_rings_x[6],my_rings_y[6];
			int num_opp,num_my;
			b.find_rings(opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);
			if(p!=1){
				for(int i=0;i<num_opp;i++){
					tempx = opp_rings_x[i];
					tempy = opp_rings_y[i];
					str2 = str1 + " X " + convtorad(tempx,tempy);
					
					// for(int j=i;j<(b.opp_ringsonboard -1);j++){
					// 	b.opp_rings_x[j] = b.opp_rings_x[j+1];
					// 	b.opp_rings_y[j] = b.opp_rings_y[j+1];
					// }
					b.opp_ringsonboard--;
					b.board[opp_rings_x[i] + 6][opp_rings_y[i] + 6] = 0;

					temp_row = b.find_row(p);
					extend_after_S(n,b,temp_row,p,str2);
					
					// for(int j = (b.opp_ringsonboard+1);j>i;j--){
					// 	b.opp_rings_x[j] = b.opp_rings_x[j-1];
					// 	b.opp_rings_y[j] = b.opp_rings_y[j-1];
					// }
					opp_rings_x[i] = tempx;
					opp_rings_y[i] = tempy;
					b.opp_ringsonboard++;
					b.board[opp_rings_x[i] + 6][opp_rings_y[i] + 6] = 4;
				}
				rsre(b,x1,y1,x2,y2,2);
			}
			else{
				for(int i=0;i<num_my;i++){
					tempx = my_rings_x[i];
					tempy = my_rings_y[i];
					str2 = str1 + " X " + convtorad(tempx,tempy);
					
					// for(int j=i;j<(b.my_ringsonboard -1);j++){
					// 	b.my_rings_x[j] = b.my_rings_x[j+1];
					// 	b.my_rings_y[j] = b.my_rings_y[j+1];
					// }
					b.my_ringsonboard--;
					b.board[my_rings_x[i] + 6][my_rings_y[i] + 6] = 0;

					temp_row = b.find_row(p);
					extend_after_S(n,b,temp_row,p,str2);
					
					// for(int j = (b.my_ringsonboard+1);j>i;j--){
					// 	b.my_rings_x[j] = b.my_rings_x[j-1];
					// 	b.my_rings_y[j] = b.my_rings_y[j-1];
					// }
					my_rings_x[i] = tempx;
					my_rings_y[i] = tempy;
					b.my_ringsonboard++;
					b.board[my_rings_x[i] + 6][my_rings_y[i] + 6] = 3;
				}
				rsre(b,x1,y1,x2,y2,1);
			}
			it1 = it1 + 4;
		}

	}
}

void extend_before_S(vector<string> &strlist,Boardclass& b,vector<int> &row,int p,string str){
	// vector<int> row;
	// row.swap(b.find_row(p));
					// cout<<"In extend_before_S if\n";

	std::vector<int> temp_row;
	string str1,str2,str3;
	int num_rings;
			int opp_rings_x[6],opp_rings_y[6],my_rings_x[6],my_rings_y[6];
		int num_opp,num_my;

	b.find_rings(opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);

	if(p!=1)
		num_rings = num_opp;
	else
		num_rings = num_my;
	if(row.size()==0 || num_rings<= (M -3)){
		//reverse_board(t.move[0],p);
		// Boardclass bcopy;
		// Node* bcopy = new Boardclass();
		// bcopy->copy_board(b);
		// bcopy->reverse_update(str,p);
		// blist.push_back(bcopy);
		strlist.push_back(str);
	}
	else{
		// cout<<"Danger\n";
		int it1=0;
		int it2 = row.size();
		int x1,y1,x2,y2;
		int tempx,tempy;
		while(it1<it2){
			x1 = row[it1];
			y1 = row[it1 + 1];
			x2 = row[it1 + 2];
			y2  = row[it1 + 3];
			rsre(b,x1,y1,x2,y2,0);
			if(str.length()==0)
				str1 = str +("RS "+ convtorad(x1,y1) +" RE " + convtorad(x2,y2));
			else
				str1 = str +(" RS "+ convtorad(x1,y1) +" RE " + convtorad(x2,y2));
			int opp_rings_x[6],opp_rings_y[6],my_rings_x[6],my_rings_y[6];
			int num_opp,num_my;
			b.find_rings(opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);
			if(p!=1){
				for(int i=0;i<num_opp;i++){
					tempx = opp_rings_x[i];
					tempy = opp_rings_y[i];
					str2 = str1 + " X " + convtorad(tempx,tempy);
					
					// for(int j=i;j<(b.opp_ringsonboard -1);j++){
					// 	b.opp_rings_x[j] = b.opp_rings_x[j+1];
					// 	b.opp_rings_y[j] = b.opp_rings_y[j+1];
					// }
					b.opp_ringsonboard--;
					b.board[opp_rings_x[i] + 6][opp_rings_y[i] + 6] = 0;

					temp_row = b.find_row(p);
					extend_before_S(strlist,b,temp_row,p,str2);
					
					// for(int j = (b.opp_ringsonboard+1);j>i;j--){
					// 	b.opp_rings_x[j] = b.opp_rings_x[j-1];
					// 	b.opp_rings_y[j] = b.opp_rings_y[j-1];
					// }
					opp_rings_x[i] = tempx;
					opp_rings_y[i] = tempy;
					b.opp_ringsonboard++;
					b.board[opp_rings_x[i] + 6][opp_rings_y[i] + 6] = 4;
				}
				rsre(b,x1,y1,x2,y2,2);
			}
			else{
				for(int i=0;i<num_my;i++){
					tempx = my_rings_x[i];
					tempy = my_rings_y[i];
					str2 = str1 + " X " + convtorad(tempx,tempy);
					
					// for(int j=i;j<(b.my_ringsonboard -1);j++){
					// 	b.my_rings_x[j] = b.my_rings_x[j+1];
					// 	b.my_rings_y[j] = b.my_rings_y[j+1];
					// }
					b.my_ringsonboard--;
					b.board[my_rings_x[i] + 6][my_rings_y[i] + 6] = 0;

					temp_row = b.find_row(p);
					extend_before_S(strlist,b,temp_row,p,str2);
					
					// for(int j = (b.my_ringsonboard+1);j>i;j--){
					// 	b.my_rings_x[j] = b.my_rings_x[j-1];
					// 	b.my_rings_y[j] = b.my_rings_y[j-1];
					// }
					my_rings_x[i] = tempx;
					my_rings_y[i] = tempy;
					b.my_ringsonboard++;
					b.board[my_rings_x[i] + 6][my_rings_y[i] + 6] = 3;
				}
				rsre(b,x1,y1,x2,y2,1);
			}
			it1 = it1 + 4;
		}

	}
}

void successor(Boardclass& b, Node*& n, int p){
	int x,y,x1,y1,z1;
	string ring_rad;
	string str1,str2,str3;
	int val;
	string str = "";
	int flag =0;
	int num_rings;
	std::vector<int> temp_row;
	//cout<<"in successor\n";
	if(n->visited==0){
		int opp_rings_x[6],opp_rings_y[6],my_rings_x[6],my_rings_y[6];
		int num_opp,num_my;
		// b.find_rings(opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);

		// std::vector<Boardclass*> blist;
		std::vector<string> strlist;
		temp_row = b.find_row(p);
		// Boardclass tempb;
		// tempb.copy_board(b);
		extend_before_S(strlist,b,temp_row,p,str);
			// cout<<"BEFORE extend before\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<tempb.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }

			// cout <<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++){
			// 	if(tempb.board[i1][j1]!=b.board[i1][j1])
			// 		cout<<"After extend before ERROR---------------------------------------------\n";					
			// 		cout<<b.board[i1][j1]<<" ";
			// 	}
			// 	cout<<"\n";
			// }
			// for(int k=0;k<(strlist.size());k++){
			// 	if(strlist[k].length()!=0){
			// 		cout<<"STRINGS------------------------------------";
			// 	}
			// 	cout<<strlist[k]<<"\n";
			// }
		// cout<<"SEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n";
		// cout<<strlist[0];
		// cout<<strlist.size();
		for(int k=0;k<(strlist.size());k++){
			//cout<<"-------------------------------------------------------------";
		// tempb.copy_board(b);

			b.update_board(strlist[k],p);
		// cout<<"After update\n";
		// cout<<strlist[k]<<"\n";
		// cout<<p<<"\n";
		// 	for(int i1=0;i1<11;i1++){
		// 		for(int j1=0;j1<11;j1++)
		// 			cout<<b.board[i1][j1]<<" ";
		// 		cout<<"\n";
		// 	}		
			b.find_rings(opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);
   //          cout<<" RINGS:";
			// for(int i1=0;i1<num_my;i1++){
			// 	cout<<my_rings_x[i1]<<" "<<my_rings_y[i1]<<"\n";
			// }
			// cout<<"\n";
			// for(int i1=0;i1<num_opp;i1++){
			// 	cout<<opp_rings_x[i1]<<" "<<opp_rings_y[i1]<<"\n";
			// }

			if(p!=1)
				num_rings = num_opp;
			else
				num_rings = num_my;
			
			if(num_rings<= (M -3)){
				Node* t = new Node((p%2) + 1);
				//cout<<t->p<<"\n";
				//t->visited = 1;
				t->move = strlist[k];
						// cout<<"Node created\n";

				// cout<<str<<"\n";
				// n->move = "123";
				n->children.push_back(t);
				b.reverse_update(strlist[k],p);

				continue;
			}
			for(int i=0;i<num_rings;i++){
				if(p!=1){
					x = opp_rings_x[i];
					y = opp_rings_y[i];
				}
				else{
					x = my_rings_x[i];
					y = my_rings_y[i];
				}
				ring_rad = convtorad(x,y);

				//5 rings code
				//cout<<x<<" "<<y<<"\n";
				y1 = y+1;
				x1 = x;
				flag = 0;
				if(y1<=6){
				// cout<<"In 1 if\n";
					val = b.board[x1+6][y1+6];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){
							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;

							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);
						}		
						else{
							flag =1;
							while(val==1 || val==2){
								y1++;
								if(y1>6)
									break;
								val = b.board[x1+6][y1+6];
							}
							if(val==0 && y1<=6){
							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;
							
							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);
							}
						}
						y1++;
						if(y1>6 || flag==1)
							break;
						val = b.board[x1+6][y1+6];
					}
				}
				y1 = y-1;
				x1 = x;
				flag = 0;

				if(y1>=-6){
				// cout<<"In 2 if\n";

					val = b.board[x1+6][y1+6];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){

							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;
							
							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);

						}
						else{
							flag = 1;
							while(val==1 || val==2){
								y1--;
								if(y1<-6)
									break;
								val = b.board[x1+6][y1+6];
							}
							if(val==0 && y1>=-6){
							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;
							
							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);
							}
						}
						y1--;
						if(y1<-6 || flag == 1)
							break;
						val = b.board[x1+6][y1+6];
					}
				}
				//cout<<"before 3 if\n";
				y1 = y;
				x1 = x+1;
				flag =0;
				if(x1<=6){
				// cout<<"In 3 if\n";
					val = b.board[x1+6][y1+6];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){
							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;
							
							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);
						}
						else{
							flag = 1;
							while(val==1 || val==2){
								x1++;
								if(x1>6)
									break;
								val = b.board[x1+6][y1+6];
							}
							if(val==0 && x1<=6){
							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;
							
							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);
							}
						}
						x1++;
						if(x1>6 || flag ==1)
							break;
						val = b.board[x1+6][y1+6];
					}
				}
				y1 = y;
				x1 = x-1;
				flag =0;
				if(x1>=-6){
				// cout<<"In 4 if\n";
					val = b.board[x1+6][y1+6];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){
							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;
							
							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);
						}
						else{
							flag = 1;
							while(val==1 || val==2){
								x1--;
								if(x1<-6)
									break;
								val = b.board[x1+6][y1+6];
							}
							if(val==0 && x1>=-6){
							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;
							
							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);
							}
						}
						x1--;
						if(x1<-6 || flag==1)
							break;
						val = b.board[x1+6][y1+6];
					}
				}
				y1 = y+1;
				x1 = x+1;
				flag =0;
				if(y1<=6 && x1<=6){
				// cout<<"In 5 if\n";

					val = b.board[x1+6][y1+6];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){
							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;
							
							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);
						}
						else{
							flag = 1;
							while(val==1 || val==2){
								y1++;
								x1++;
								if(y1>6 || x1>6)
									break;
								val = b.board[x1+6][y1+6];
							}
							if(val==0 && y1<=6 && x1<=6){
							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;
							
							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);
							}
						}
						y1++;
						x1++;
						if(y1>6 || x1>6 || flag==1)
							break;
						val = b.board[x1+6][y1+6];
					}
				}
				y1 = y-1;
				x1 = x-1;
				flag =0;
				if(y1>=-6 && x1>=-6){
				// cout<<"In 6 if\n";

					val = b.board[x1+6][y1+6];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){
							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;
							
							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);
						}
						else{
							flag =1;
							while(val==1 || val==2){
								y1--;
								x1--;
								if(y1<-6 || x1<-6)
									break;
								val = b.board[x1+6][y1+6];
							}
							if(val==0 && y1>=-6 && x1>=-6){
							str1 = ("S "+ ring_rad +" M " + convtorad(x1,y1));
							if(strlist[k].length()==0)
								str2 = str1;
							else
								str2 = strlist[k] + " " + str1;
							
							b.update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = b.find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,b,temp_row,p,str2);
							b.reverse_update(str1,p);
							}
						}
						y1--;
						x1--;
						if(y1<-6 || x1<-6 || flag==1)
							break;
						val = b.board[x1+6][y1+6];
					}
				}
			}
			// cout <<"before reverse\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++){
			// 		cout<<b.board[i1][j1]<<" ";
			// 	}
			// 	cout<<"\n";
			// }

			b.reverse_update(strlist[k],p);
			// cout <<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++){
			// 	if(tempb.board[i1][j1]!=b.board[i1][j1])
			// 		cout<<"After reverse ERROR---------------------------------------------\n";					
			// 		cout<<b.board[i1][j1]<<" ";
			// 	}
			// 	cout<<"\n";
			// }

		}
	}
	n->visited = 1;
}

double calculateHeuristic(Boardclass& b,int *opp_rings_x,int *opp_rings_y,int *my_rings_x,int *my_rings_y,int &num_opp,int &num_my){
	// cerr<<"compute heuristic started\n";
	double h;
	//double my_marker =0.0;
	double opp_marker = 0.0;
	if(num_my<(M - 2)){
		h = 950000;
		return h;
	}
	if(num_opp<(M - 2)){
		h = -950000;
		return h;
	}
	if(num_opp == (M-2))
		h = 10000*(M - num_my) - 12000*((M - num_opp));
	else
		h = 10000*(M - num_my) - 9000*((M - num_opp));

	int count =0;
	int my_count = 0;
	for (int i = -6; i <=6; i++){
		for (int j = -6; j <=6; j++){
			if(b.board[i+6][j+6]==1){
				my_count++;
				// opp_marker = opp_marker + 1;
			}
			else{
				if(my_count!=0){
					if(my_count <= (K-2))
						h = h + pow(4,my_count);
					else if(my_count>(K-2))
						h = h + 700;
				}
				my_count = 0;
			}
			if(b.board[i+6][j+6]==2){
				count++;
				// opp_marker = opp_marker + 1;
			}
			else{
				if(count!=0){
					if(count <= (K-2))
						h = h - pow(4,count);
					else if(count>(K-2)){
						if(num_opp==(M-2))
							h = h - 1200;
						else
							h = h - 600;
					}
				}
				count = 0;
			}
		}
		if(my_count!=0){
			if(my_count <= (K-2))
				h = h + pow(4,my_count);
			else if(my_count>(K-2))
				h = h + 700;
		}
		my_count = 0;

		if(count!=0){
			if(count <= (K-2))
				h = h - pow(4,count);
			else if(count>(K-2)){
				if(num_opp==(M-2))
					h = h - 1200;
				else
					h = h - 600;
			}
		}
		count = 0;
	}
//	cerr<<"compute heuristic started\n";

	count = 0;
	my_count = 0;	
	for (int j = -6; j <=6; j++){
		for (int i = -6; i <=6; i++){
			// if (b.board[i+5][j+5] == 1) { my_marker = my_marker + 1;}
			if(b.board[i+6][j+6]==1){
				my_count++;
				// opp_marker = opp_marker + 1;
			}
			else{
				if(my_count!=0){
					if(my_count <= (K-2))
						h = h + pow(4,my_count);
					else if(my_count>(K-2))
						h = h + 700;
				}
				my_count = 0;
			}

			if(b.board[i+6][j+6]==2){
				count++;
				// opp_marker = opp_marker + 1;
			}
			else{
				if(count!=0){
					if(count <= (K-2))
						h = h - pow(4,count);
					else if(count>(K-2)){
						if(num_opp==(M-2))
							h = h - 1200;
						else
							h = h - 600;
					}
				}
				count = 0;
			}
		}
		if(my_count!=0){
			if(my_count <= (K-2))
				h = h + pow(4,my_count);
			else if(my_count>(K-2))
				h = h + 700;
		}
		my_count = 0;

		if(count!=0){
			if(count <= (K-2))
				h = h - pow(4,count);
			else if(count>(K-2)){
				if(num_opp==(M-2))
					h = h - 1200;
				else
					h = h - 600;
			}
		}
		count = 0;
	}
//	cerr<<"compute heuristic started\n";

	count =0;
	my_count = 0;
	int i = -6;
	int j;
	for(int z=-6;z<=6;z++){
		j = z;
		while(i<=6 && j<=6){
			if(b.board[i+6][j+6]==1){
				my_count++;
				// opp_marker = opp_marker + 1;
			}
			else{
				if(my_count!=0){
					if(my_count <= (K-2))
						h = h + pow(4,my_count);
					else if(my_count>(K-2))
						h = h + 700;
				}
				my_count = 0;
			}

			if(b.board[i+6][j+6]==2){
				count++;
			}
			else{
				if(count!=0){
					if(count <= (K-2))
						h = h - pow(4,count);
					else if(count>(K-2)){
						if(num_opp==(M-2))
							h = h - 1200;
						else
							h = h - 600;
					}
				}
				count = 0;
			}
		i++;
		j++;						
		}
		if(my_count!=0){
			if(my_count <= (K-2))
				h = h + pow(4,my_count);
			else if(my_count>(K-2))
				h = h + 700;
		}
		my_count = 0;

		if(count!=0){
			if(count <= (K-2))
				h = h - pow(4,count);
			else if(count>(K-2)){
				if(num_opp==(M-2))
					h = h - 1200;
				else
					h = h - 600;
			}
		}
		count = 0;
		i = -6;		
	}
//	cerr<<"compute heuristic started\n";

	count = 0;
	j = -6;
	my_count = 0;
	for(int z=-5;z<=6;z++){
		i = z;
		while(i<=6 && j<=6){
//			cerr<<"compute heuristic started\n";
			if(b.board[i+6][j+6]==1){
				my_count++;
				// opp_marker = opp_marker + 1;
			}
			else{
				if(my_count!=0){
					if(my_count <= (K-2))
						h = h + pow(4,my_count);
					else if(my_count>(K-2))
						h = h + 700;
				}
				my_count = 0;
			}

			if(b.board[i+6][j+6]==2){
				count++;
			}
			else{
				if(count!=0){
					if(count <= (K-2))
						h = h - pow(4,count);
					else if(count>(K-2)){
						if(num_opp==(M-2))
							h = h - 1200;
						else
							h = h - 600;
					}
				}
				count = 0;
			}
			i++;
			j++;			
		}
		if(my_count!=0){
			if(my_count <= (K-2))
				h = h + pow(4,my_count);
			else if(my_count>(K-2)){
				h = h + 700;
			}
		}
		my_count = 0;

		if(count!=0){
			if(count <= (K-2))
				h = h - pow(4,count);
			else if(count>(K-2)){
				if(num_opp==(M-2))
					h = h - 1100;
				else
					h = h - 600;
			}
		}
		count = 0;
		j = -6;
	}
	// int x,x1;
	// int y,y1;
	// int val;
	// double h2 = 0.0;
	// double h3 = 0.0;
	// int flag = 0;
	// for(int k =0;k<num_my;k++){
	// 	x = my_rings_x[k];
	// 	y = my_rings_y[k];
	// 	y1 = y+1;
	// 	x1 = x;
	// 	flag = 0;
	// 	if(y1<=5){
	// 	// cout<<"In 1 if\n";
	// 		val = b.board[x1+5][y1+5];
	// 		while(val == 0 || val == 1 || val == 2){
	// 			if(val==0){
	// 				h2 = h2+10;
	// 			}		
	// 			else{
	// 				flag =1;
	// 				while(val==1 || val==2){
	// 					y1++;
	// 					h3 = h3 + 40;
	// 					if(y1>5)
	// 						break;
	// 					val = b.board[x1+5][y1+5];
	// 				}
	// 				if(val==0 && y1<=5){
	// 					h2 = h2 + h3;
	// 				}
	// 			}
	// 			y1++;
	// 			if(y1>5 || flag==1)
	// 				break;
	// 			val = b.board[x1+5][y1+5];
	// 		}
	// 	}
	// 	y1 = y-1;
	// 	x1 = x;
	// 	flag = 0;
	// 	h3 = 0.0;
	// 	if(y1>=-5){
	// 	// cout<<"In 2 if\n";
	// 		val = b.board[x1+5][y1+5];
	// 		while(val == 0 || val == 1 || val == 2){
	// 			if(val==0){
	// 				h2 = h2+10;
	// 			}
	// 			else{
	// 				flag = 1;
	// 				while(val==1 || val==2){
	// 					y1--;
	// 					h3 = h3 + 40;
	// 					if(y1<-5)
	// 						break;
	// 					val = b.board[x1+5][y1+5];
	// 				}
	// 				if(val==0 && y1>=-5){
	// 					h2 = h2 + h3;
	// 				}
	// 			}
	// 			y1--;
	// 			if(y1<-5 || flag == 1)
	// 				break;
	// 			val = b.board[x1+5][y1+5];
	// 		}
	// 	}
	// 	y1 = y;
	// 	x1 = x+1;
	// 	flag =0;
	// 	h3 = 0.0;
	// 	if(x1<=5){
	// 	// cout<<"In 3 if\n";
	// 		val = b.board[x1+5][y1+5];
	// 		while(val == 0 || val == 1 || val == 2){
	// 			if(val==0){
	// 				h2 = h2+10;
	// 			}
	// 			else{
	// 				flag = 1;
	// 				while(val==1 || val==2){
	// 					x1++;
	// 					h3 = h3 + 40;
	// 					if(x1>5)
	// 						break;
	// 					val = b.board[x1+5][y1+5];
	// 				}
	// 				if(val==0 && x1<=5){
	// 					h2 = h2 + h3;
	// 				}
	// 			}
	// 			x1++;
	// 			if(x1>5 || flag ==1)
	// 				break;
	// 			val = b.board[x1+5][y1+5];
	// 		}
	// 	}
	// 	y1 = y;
	// 	x1 = x-1;
	// 	flag =0;
	// 	h3 = 0.0;
	// 	if(x1>=-5){
	// 	// cout<<"In 4 if\n";
	// 		val = b.board[x1+5][y1+5];
	// 		while(val == 0 || val == 1 || val == 2){
	// 			if(val==0){
	// 				h2 = h2+10;
	// 			}
	// 			else{
	// 				flag = 1;
	// 				while(val==1 || val==2){
	// 					x1--;
	// 					h3 = h3 + 40;
	// 					if(x1<-5)
	// 						break;
	// 					val = b.board[x1+5][y1+5];
	// 				}
	// 				if(val==0 && x1>=-5){
	// 					h2 = h2 + h3;
	// 				}
	// 			}
	// 			x1--;
	// 			if(x1<-5 || flag==1)
	// 				break;
	// 			val = b.board[x1+5][y1+5];
	// 		}
	// 	}
	// 	y1 = y+1;
	// 	x1 = x+1;
	// 	flag =0;
	// 	h3 = 0.0;
	// 	if(y1<=5 && x1<=5){
	// 	// cout<<"In 5 if\n";

	// 		val = b.board[x1+5][y1+5];
	// 		while(val == 0 || val == 1 || val == 2){
	// 			if(val==0){
	// 				h2 = h2+10;
	// 			}
	// 			else{
	// 				flag = 1;
	// 				while(val==1 || val==2){
	// 					y1++;
	// 					x1++;
	// 					h3 = h3 + 40;
	// 					if(y1>5 || x1>5)
	// 						break;
	// 					val = b.board[x1+5][y1+5];
	// 				}
	// 				if(val==0 && y1<=5 && x1<=5){
	// 					h2 = h2 + h3;
	// 				}
	// 			}
	// 			y1++;
	// 			x1++;
	// 			if(y1>5 || x1>5 || flag==1)
	// 				break;
	// 			val = b.board[x1+5][y1+5];
	// 		}
	// 	}
	// 	y1 = y-1;
	// 	x1 = x-1;
	// 	flag =0;
	// 	h3 = 0.0;
	// 	if(y1>=-5 && x1>=-5){
	// 	// cout<<"In 6 if\n";

	// 		val = b.board[x1+5][y1+5];
	// 		while(val == 0 || val == 1 || val == 2){
	// 			if(val==0){
	// 				h2 = h2+10;
	// 			}
	// 			else{
	// 				flag =1;
	// 				while(val==1 || val==2){
	// 					y1--;
	// 					x1--;
	// 					h3 = h3 + 40;
	// 					if(y1<-5 || x1<-5)
	// 						break;
	// 					val = b.board[x1+5][y1+5];
	// 				}
	// 				if(val==0 && y1>=-5 && x1>=-5){
	// 					h2 = h2 + h3;
	// 				}
	// 			}
	// 			y1--;
	// 			x1--;
	// 			if(y1<-5 || x1<-5 || flag==1)
	// 				break;
	// 			val = b.board[x1+5][y1+5];
	// 		}
	// 	}
	// }
	// h = h + (h2/num_my);
	// h = h + 20*(my_marker);
	// cout<<h<<"\n";
	// cerr<<"heuristic ends\n";
	return h;
}
void createTree ( Node*& n, int depth, int max_depth, int p, Boardclass& b,double alpha,double beta) {

     // cerr<<"in create tree\n";
	int opp_rings_x[6],opp_rings_y[6],my_rings_x[6],my_rings_y[6];
	int num_opp,num_my;
//	cerr<<"create tree started\n";
	b.find_rings(opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);

	n->num_myrings = num_my;

    if (depth > max_depth) {return;}

    if (depth == max_depth || num_my <=2 || num_opp<=2) {
        n->h = calculateHeuristic(b,opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);
        // cout<<depth<<"\n";
        return;
    }
    // cout<<depth<<"\n";
    if ( depth < max_depth ){
        double parent_heuristic;
        if(p!=1){
        	parent_heuristic = DBL_MAX;
        }
        else{
        	parent_heuristic = -DBL_MAX;
        }
   //      Boardclass tempb3;
   //      			cout<<"SUCCESSOR BEFORE-------------------------------------------------------------";
			// cout<<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<b.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }
			// 			tempb3.copy_board(b);

        successor(b, n, p);
   //      			cout<<"SUCCESSOR AFTER-------------------------------------------------------------";
			// cout<<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<b.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }
			// cout <<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++){
			// 	if(tempb3.board[i1][j1]!=b.board[i1][j1])
			// 		cout<<"SUCCESSOR ERROR---------------------------------------------\n";					
			// 		cout<<b.board[i1][j1]<<" ";
			// 	}
			// 	cout<<"\n";
			// }


		//cout<<n->children.size()<<"\n";
        if(n->children.size() == 0){
        	n->h = calculateHeuristic(b,opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);
        	return;
        }
       // Boardclass tempb,tempb2;
 
        for ( int i = 0; i < n->children.size(); i++ ){
   //      	cout<<"BEFORE update\n";
   //      	cout<<n->children[i]->move<<"\n";
			// cout<<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<b.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }
   //      	cout<<"going to update board\n";
   //      	cout<<n->children[i]->move<<"\n";
   //      	cout<<p<<"\n";
			// cout<<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<b.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }
			// tempb.copy_board(b);

            b.update_board( n->children[i]->move, p );
   //          tempb2.copy_board(b);
   //      	cout<<"after update board\n";
			// cout<<"AFTER UPDATE\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<b.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }
            
            // cout<<"depth increases\n";
            createTree( (n->children.at(i)), (depth + 1), max_depth, ((p%2) + 1), b,alpha,beta);
   //          cout<<"BEFORE REVERSE\n";
   //      	cout<<n->children[i]->move<<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<b.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }
			// cout<<"AFTER UPDATE\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<tempb2.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }
			// cout <<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++){
			// 	if(tempb2.board[i1][j1]!=b.board[i1][j1])
			// 		cout<<"IN CREATE TREE CREATE TREE ERROR---------------------------------------------\n";					
			// 		cout<<b.board[i1][j1]<<" ";
			// 	}
			// 	cout<<"\n";
			// }
			// cout<<"BEFORE REVERSE\n";
			// cout<<n->children[i]->move<<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<tempb.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }
			// cout <<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++){
			// 	if(tempb2.board[i1][j1]!=b.board[i1][j1])
			// 		cout<<"IN CREATE TREE CREATE TREE ERROR---------------------------------------------\n";					
			// 		cout<<b.board[i1][j1]<<" ";
			// 	}
			// 	cout<<"\n";
			// }

            b.reverse_update( n->children[i]->move, p );
			// cout<<"AFTER REVERSE\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<b.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }

			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++){
			// 	if(tempb.board[i1][j1]!=b.board[i1][j1])
			// 		cout<<"IN CREATE TREE REVERSE ERROR---------------------------------------------\n";					
			// 		cout<<b.board[i1][j1]<<" ";
			// 	}
			// 	cout<<"\n";
			// }

            if (p == 1){
                // parent_heuristic = -DBL_MAX;
                if ( parent_heuristic < n->children.at(i)->h ){
                    parent_heuristic = n->children.at(i)->h;
                }
                alpha = max(alpha,parent_heuristic);
                if(beta <= alpha){
                	//cout<<"break\n";
                	break;
                }
            }
            else if ( p == 2 ){
                // parent_heuristic = DBL_MAX;
                if ( parent_heuristic > n->children.at(i)->h ){
                    parent_heuristic = n->children.at(i)->h;
                }
                beta = min(alpha,parent_heuristic);
                if(beta <= alpha){
                	//cout<<"break\n";
                	break;
                }
            }
            // cout<<"end of 1 iteration for loop\n";
        }
        n->h = parent_heuristic;
    }
    // cerr<<"in create tree\n";

}


int main(){
	//ifstream in("file.txt");
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

	token = strtok(NULL, " ");
	int K = atoi(token);

	// cin>>N;
	// cin>>M;
	// cin>>K;
	N = n;
	M = n;
	// for(int i=0;i<11;i++){
	// 	for(int j=0;j<11;j++)
	// 		cout<<board[i][j]<<" ";
	// 	cout<<"\n";
	// }
	Boardclass main_board(N);
	
	main_board.N = N;
	main_board.M = M;
	main_board.K = K;

	time_t t;
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
	player++;
	//cerr<<player<<"\n";
	//cerr<<n<<"\n";
	//cerr<<time_left<<"\n";
	srand ((unsigned) time(&t));
	// cout<<player;
	// cout<<convtorad(-2,0)<<"\n";
	// int arrr[2];
	// main_board.convtodavid(2,10,arrr);
	// cout<<arrr[0]<<" "<<arrr[1]<<"\n";
	
	if(player==2){
		getline(cin, str);
		//cerr<<str<<"\n";
		main_board.update_board(str,2);
	}
	for(int i=0;i<=(M - 1);i++){
		// cout<<"iiiii\n";
		int j,k;
		string m;
		if(main_board.board[6][6] == 0){
			m = "P "+convtorad(0,0);
			main_board.update_board(m,1);
		}
		else{
			if(i<(M- 2)){
				j = rand()%4;
				k = rand()%4;
				j = j-2;
				k = k-2;

				while(1){
					if(main_board.board[j+6][k+6]==0){
						m = "P "+convtorad(j,k);
						main_board.update_board(m,1);
						break;
					}
					j = rand()%4;
					k = rand()%4;
					j = j-2;
					k = k-2;
				}

			}
			else{
				j = rand()%2;
				k = rand()%2;
				if(rand()%1 == 0)
					j = j+3;
				else
					j = -3 -j;
				if(rand()%1 == 0)
					k = k+3;
				else
					k = -3 -k;
				while(1){
					if(main_board.board[j+6][k+6]==0){
						m = "P "+convtorad(j,k);
						main_board.update_board(m,1);
						break;
					}
					j = rand()%2;
					k = rand()%2;
					if(rand()%1 == 0)
						j = j+3;
					else
						j = -3 -j;
					if(rand()%1 == 0)
						k = k+3;
					else
						k = -3 -k;
				}
			}
		}
		cout<<m<<"\n";
//		cerr<<m<<"\n";
		// cout<<"\n";
		// for(int i1=0;i1<11;i1++){
		// 	for(int j1=0;j1<11;j1++)
		// 		cout<<main_board.board[i1][j1]<<" ";
		// 	cout<<"\n";
		// }
		if(!(player==2 && i==4)){
			getline(cin, str);
			// cout<<"Okay "<<main_board.my_ringsonboard<<" "<<main_board.opp_ringsonboard<<"\n";
			main_board.update_board(str,2);
			// cout<<"Okay2 "<<main_board.my_ringsonboard<<" "<<main_board.opp_ringsonboard<<"\n";			
		// cout<<"\n";
		// for(int i1=0;i1<11;i1++){
		// 	for(int j1=0;j1<11;j1++)
		// 		cout<<main_board.board[i1][j1]<<" ";
		// 	cout<<"\n";
		// }

		}
	// cout<<"end\n";
	}

	// cout<<"In main1\n";
	
	if(player == 2){
		getline(cin, str);
		main_board.update_board(str,2);
	}
		// cout<<"In main\n";
	// Boardclass tempb;
	int i1;
	// 	Node* nod_pointer = new Node(1);
	// int move = 0;
	int flag,flag2;
	int opp_rings_x[6],opp_rings_y[6],my_rings_x[6],my_rings_y[6];
	int num_opp,num_my;

	while(1){
		// flag =0;
		// if(move == 1){
		// 	for(int j=0;j<nod_pointer->children[i].size();j++){
		// 		if(nod_pointer->children[i]->children[j]->move.compare(str)==0){
		// 			nod_pointer = nod_pointer->children[i]->children[j];
		// 			flag = 1;
		// 		}
		// 	}
		// 	if(flag==0){
		// 		nod_pointer->children.clear();
		// 		nod_pointer->visited = 0;
		// 	}
		// }
		// move =1;
		// createTree ( nod_pointer, 0, 4, 1, main_board,-10000,10000);

		//cout<<"your move";//code it
		Node* nod_pointer = new Node(1);
		flag2 = 0;
		createTree ( nod_pointer, 0, 1, 1, main_board,-1000000,1000000);
		main_board.find_rings(opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);
		if(num_opp == (M -2)){
			flag2 = 0;
		}
		else{
			if(num_my != nod_pointer->num_myrings){
				flag2 =0;
						// cerr<"getting used------------------------------------------------\n";
			}
			else{
				for(i1 =0;i1<nod_pointer->children.size();i1++){
					if((nod_pointer->children[i1]->num_myrings - num_my)< 0){
						cout<<nod_pointer->children[i1]->move<<"\n";
						//cerr<<nod_pointer->children[i1]->move<<"\n";
						main_board.update_board(nod_pointer->children[i1]->move,1);
						// cerr<"getting used------------------------------------------------\n";
						flag2 =1;
						break;				
					}
				}		
			}
		}
		if(flag2!=1){
			createTree ( nod_pointer, 0, 3, 1, main_board,-1000000,1000000);
			// cout<<"after create tree\n";
			// cout<<"\n";
			// for(int i=0;i<11;i++){
			// 	for(int j=0;j<11;j++){
			// 		cout<<main_board.board[i][j]<<" ";
			// 		if(tempb.board[i][j]!=main_board.board[i][j])
			// 			cout<<"ERROR---------------------------------------------\n";
			// 	}
			// 	cout<<"\n";
			// }
			flag =0;
			//cerr<<nod_pointer->children.size()<<"\n";
			for(i1 =0;i1<nod_pointer->children.size();i1++){
				if((abs(nod_pointer->h - nod_pointer->children[i1]->h))<=1){
					cout<<nod_pointer->children[i1]->move<<"\n";
					//cerr<<nod_pointer->children[i1]->move<<"\n";
					main_board.update_board(nod_pointer->children[i1]->move,1);
					flag =1;
					break;				
				}
			}		
			if(flag==0){
				cout<<nod_pointer->children[0]->move<<"\n";
				//cerr<<"flag=0"<<nod_pointer->children[0]->move<<"\n";
				main_board.update_board(nod_pointer->children[0]->move,1);

			}
		}
		// cout<<nod_pointer->children[0]->move<<"\n";

		// cout<<"after update \n";
		// for(int i=0;i<11;i++){
		// 	for(int j=0;j<11;j++)
		// 		cout<<main_board.board[i][j]<<" ";
		// 	cout<<"\n";
		// }
		// cout<< main_board.my_ringsonboard<<" "<<main_board.opp_ringsonboard<<"\n";
		// for(int i=0;i<main_board.my_ringsonboard;i++){
		// 	cout<<main_board.my_rings_x[i]<<" "<<main_board.my_rings_y[i]<<"\n";
		// }
		// cout<<"\n";
		// for(int i=0;i<main_board.opp_ringsonboard;i++){
		// 	cout<<main_board.opp_rings_x[i]<<" "<<main_board.opp_rings_y[i]<<"\n";
		// }
		//cerr<<"waiting\n";
		getline(cin, str);
		// if(str.length()==3)
		// 	return 0;

		main_board.update_board(str,2);
		
		// cout<<"Input chance\n";
		// cout<<str<<"\n";
		// for(int i=0;i<11;i++){
		// 	for(int j=0;j<11;j++)
		// 		cout<<main_board.board[i][j]<<" ";
		// 	cout<<"\n";
		// }
		// tempb.copy_board(main_board);
	}	

	// int bo[11][11]= {
	// 				{-1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1}, 
	// 				{0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1 },
	// 				{0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1 },
	// 				{0, 0, 0, 0, 0, 3, 1, 1, 1, -1, -1 },
	// 				{0, 0, 0, 0, 3, 1, 1, 1, 2, 1, -1 },
	// 				{-1, 0, 0, 0, 4, 1, 1, 0, 0, 2, -1 },
	// 				{-1, 0, 3, 0, 0, 2, 4, 4, 0, 0, 0 },
	// 				{-1, -1, 0, 0, 0, 3, 4, 0, 0, 0, 0 },
	// 				{-1, -1, -1, 0, 0, 4 ,2, 2, 0, 2, 0 },
	// 				{-1, -1, -1, -1, 0, 0, 0, 0, 0 ,0, 0 },
	// 				{-1, -1, -1, -1, -1, -1, 0 ,0 ,0 ,0 ,-1} 
	// 				};

	// 	for(int i=0;i<11;i++){
	// 		for(int j=0;j<11;j++)
	// 			main_board.board[i][j] = bo[i][j];
	// 	}
	// 	//main_board.board = bo;
	// 	main_board.opp_ringsonboard = 5;
	// 	main_board.my_ringsonboard = 5;
	// 	// main_board.my_rings_x[0] = -1;
	// 	// main_board.my_rings_y[0] = -1;
	// 	// main_board.my_rings_x[1] = 2;
	// 	// main_board.my_rings_y[1] = 0;
	// 	// main_board.my_rings_x[2] = -2;
	// 	// main_board.my_rings_y[2] = 0;
	// 	// main_board.my_rings_x[3] = 1;
	// 	// main_board.my_rings_y[3] = -3;
	// 	// main_board.my_rings_x[4] = -3;
	// 	// main_board.my_rings_y[4] = 2;

	// 	// main_board.opp_rings_x[0] = 3;
	// 	// main_board.opp_rings_y[0] =0;
	// 	// main_board.opp_rings_x[1] =0;
	// 	// main_board.opp_rings_y[1] =-1;
	// 	// main_board.opp_rings_x[2] =1;
	// 	// main_board.opp_rings_y[2] =1;
	// 	// main_board.opp_rings_x[3] =2;
	// 	// main_board.opp_rings_y[3] =1;
	// 	// main_board.opp_rings_x[4] =1;
	// 	// main_board.opp_rings_y[4] =2;

	// 	// cout<<"\n";
	// 	// for(int i=0;i<main_board.opp_ringsonboard;i++){
	// 	// 	cout<<main_board.opp_rings_x[i]<<" "<<main_board.opp_rings_y[i]<<"\n";
	// 	// }

	// 	cout<<"\n";
	// 	for(int i=0;i<11;i++){
	// 		for(int j=0;j<11;j++)
	// 			cout<<main_board.board[i][j]<<" ";
	// 		cout<<"\n";
	// 	}

	// 	main_board.update_board("S 2 3 M 3 2",2);
	// 	cout<<"S 2 3 M 3 2"<<"\n";

	// 	cout<<"after update \n";
	// 	for(int i=0;i<11;i++){
	// 		for(int j=0;j<11;j++)
	// 			cout<<main_board.board[i][j]<<" ";
	// 		cout<<"\n";
	// 	}
	// 	cout<< main_board.my_ringsonboard<<" "<<main_board.opp_ringsonboard<<"\n";
	// 	// for(int i=0;i<main_board.my_ringsonboard;i++){
	// 	// 	cout<<main_board.my_rings_x[i]<<" "<<main_board.my_rings_y[i]<<"\n";
	// 	// }
	// 	// cout<<"\n";
	// 	// for(int i=0;i<main_board.opp_ringsonboard;i++){
	// 	// 	cout<<main_board.opp_rings_x[i]<<" "<<main_board.opp_rings_y[i]<<"\n";
	// 	// }

	// 	Node* nod_pointer = new Node(1);
	// 	createTree ( nod_pointer, 0, 2, 1, main_board);
		
	// 	cout<<"after create tree\n";
	// 	for(int i=0;i<11;i++){
	// 		for(int j=0;j<11;j++)
	// 			cout<<main_board.board[i][j]<<" ";
	// 		cout<<"\n";
	// 	}
	// 	main_board.update_board(nod_pointer->children[0]->move,1);
	// 	cout<<nod_pointer->children[0]->move<<"\n";

	// 	cout<<"final\n";
	// 	for(int i=0;i<11;i++){
	// 		for(int j=0;j<11;j++)
	// 			cout<<main_board.board[i][j]<<" ";
	// 		cout<<"\n";
	// 	}


}