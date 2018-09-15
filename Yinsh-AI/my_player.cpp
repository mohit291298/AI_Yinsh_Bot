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
#define DBL_MAX 10000;
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

string convtorad(int a,int b){
	//convert radial to david coordinates
	int arr[2];
	arr[0] = a;
	arr[1] = b;
	// assuming a is the x - coordinate 
	// assuming b is the y - coordinate 

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

	else if ( a * b <= 0 ){
		if ( a > 0 ){
			arr[1] = 2 * arr[0] - b;
			//return;
		}
		else if ( b > 0 ){
			arr[1] = 6 * arr[0] + a;
			//return;
		}
	}
	ostringstream str1,str2;
	str1 << arr[0];
	str2 <<arr[1];
	return (str1.str() + " " + str2.str());
}

void rsre(Boardclass& b,int a1,int b1,int a2,int b2,int color){
	int p1 = a1;
	int q1 = b1;
	if(a1==a2){
		if(b2>b1){
			while(q1!=b2){
				b.board[p1+5][q1+5] = color;
				q1++;
			}
		}
		else{
			while(q1!=b2){
				b.board[p1+5][q1+5] = color;
				q1--;
			}					
		}
		b.board[a2+5][b2+5]=color;
	}
	else if(b1==b2){
		if(a2>a1){
			while(p1!=a2){
				b.board[p1+5][q1+5] = color;
				p1++;
			}
		}
		else{
			while(p1!=a2){
				b.board[p1+5][q1+5] = color;
				p1--;
			}					
		}
		b.board[a2+5][b2+5]=0;
	}
	else{
		if(b2>b1){
			while(q1!=b2){
				b.board[p1+5][q1+5] = color;
				q1++;
				p1++;
			}
		}
		else{
			while(q1!=b2){
				b.board[p1+5][q1+5] = color;
				q1--;
				p1--;
			}					
		}
		b.board[a2+5][b2+5]=0;
	}

}

void extend_after_S(Node*& n,Boardclass& b,vector<int>& row,int p,string str){
	// vector<int> row;
	// row.swap(b.find_row(p));
	int num_rings;
	string str1,str2,str3;
	std::vector<int> temp_row;
	if(p!=1)
		num_rings = b.opp_ringsonboard;
	else
		num_rings = b.my_ringsonboard;
	if(row.size()==0 || num_rings<=2){
		//reverse_board(t.move[0],p);
		Node* t = new Node((p%2) + 1);
		//cout<<t->p<<"\n";
		//t->visited = 1;
		t->move = str;
		//cout<<str<<"\n";
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
			if(p!=1){
				for(int i=0;i<b.opp_ringsonboard;i++){
					tempx = b.opp_rings_x[i];
					tempy = b.opp_rings_y[i];
					str2 = str1 + " X " + convtorad(tempx,tempy);
					
					for(int j=i;j<(b.opp_ringsonboard -1);j++){
						b.opp_rings_x[j] = b.opp_rings_x[j+1];
						b.opp_rings_y[j] = b.opp_rings_y[j+1];
					}
					b.opp_ringsonboard--;
					b.board[b.opp_rings_x[i] + 5][b.opp_rings_y[i] + 5] = 0;

					temp_row = b.find_row(p);
					extend_after_S(n,b,temp_row,p,str2);
					
					for(int j = (b.opp_ringsonboard+1);j>i;j--){
						b.opp_rings_x[j] = b.opp_rings_x[j-1];
						b.opp_rings_y[j] = b.opp_rings_y[j-1];
					}
					b.opp_rings_x[i] = tempx;
					b.opp_rings_y[i] = tempy;
					b.opp_ringsonboard++;
					b.board[b.opp_rings_x[i] + 5][b.opp_rings_y[i] + 5] = 4;
				}
				rsre(b,x1,y1,x2,y2,2);
			}
			else{
				for(int i=0;i<b.my_ringsonboard;i++){
					tempx = b.my_rings_x[i];
					tempy = b.my_rings_y[i];
					str2 = str1 + " X " + convtorad(tempx,tempy);
					
					for(int j=i;j<(b.my_ringsonboard -1);j++){
						b.my_rings_x[j] = b.my_rings_x[j+1];
						b.my_rings_y[j] = b.my_rings_y[j+1];
					}
					b.my_ringsonboard--;
					b.board[b.my_rings_x[i] + 5][b.my_rings_y[i] + 5] = 0;

					temp_row = b.find_row(p);
					extend_after_S(n,b,temp_row,p,str2);
					
					for(int j = (b.my_ringsonboard+1);j>i;j--){
						b.my_rings_x[j] = b.my_rings_x[j-1];
						b.my_rings_y[j] = b.my_rings_y[j-1];
					}
					b.my_rings_x[i] = tempx;
					b.my_rings_y[i] = tempy;
					b.my_ringsonboard++;
					b.board[b.my_rings_x[i] + 5][b.my_rings_y[i] + 5] = 3;
				}
				rsre(b,x1,y1,x2,y2,1);
			}
			it1 = it1 + 4;
		}

	}
}

void extend_before_S(vector<Boardclass> &blist,vector<string> &strlist,Boardclass& b,vector<int> &row,int p,string str){
	// vector<int> row;
	// row.swap(b.find_row(p));
	std::vector<int> temp_row;
	string str1,str2,str3;
	int num_rings;
	if(p!=1)
		num_rings = b.opp_ringsonboard;
	else
		num_rings = b.my_ringsonboard;
	if(row.size()==0 || num_rings<=2){
		//reverse_board(t.move[0],p);
		Boardclass bcopy;
		bcopy.copy_board(b);
		blist.push_back(bcopy);
		strlist.push_back(str);
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
			if(str.length()==0)
				str1 = str +("RS "+ convtorad(x1,y1) +" RE " + convtorad(x2,y2));
			else
				str1 = str +(" RS "+ convtorad(x1,y1) +" RE " + convtorad(x2,y2));
			if(p!=1){
				for(int i=0;i<b.opp_ringsonboard;i++){
					tempx = b.opp_rings_x[i];
					tempy = b.opp_rings_y[i];
					str2 = str1 + " X " + convtorad(tempx,tempy);
					
					for(int j=i;j<(b.opp_ringsonboard -1);j++){
						b.opp_rings_x[j] = b.opp_rings_x[j+1];
						b.opp_rings_y[j] = b.opp_rings_y[j+1];
					}
					b.opp_ringsonboard--;
					b.board[b.opp_rings_x[i] + 5][b.opp_rings_y[i] + 5] = 0;
					temp_row = b.find_row(p);
					extend_before_S(blist,strlist,b,temp_row,p,str2);
					
					for(int j = (b.opp_ringsonboard+1);j>i;j--){
						b.opp_rings_x[j] = b.opp_rings_x[j-1];
						b.opp_rings_y[j] = b.opp_rings_y[j-1];
					}
					b.opp_rings_x[i] = tempx;
					b.opp_rings_y[i] = tempy;
					b.opp_ringsonboard++;
					b.board[b.opp_rings_x[i] + 5][b.opp_rings_y[i] + 5] = 4;
				}
				rsre(b,x1,y1,x2,y2,2);
			}
			else{
				for(int i=0;i<b.my_ringsonboard;i++){
					tempx = b.my_rings_x[i];
					tempy = b.my_rings_y[i];
					str2 = str1 + " X " + convtorad(tempx,tempy);
					
					for(int j=i;j<(b.my_ringsonboard -1);j++){
						b.my_rings_x[j] = b.my_rings_x[j+1];
						b.my_rings_y[j] = b.my_rings_y[j+1];
					}
					b.my_ringsonboard--;
					b.board[b.my_rings_x[i]+ 5][b.my_rings_y[i] + 5] = 0;

					temp_row = b.find_row(p);
					extend_before_S(blist,strlist,b,temp_row,p,str2);
					
					for(int j = (b.my_ringsonboard+1);j>i;j--){
						b.my_rings_x[j] = b.my_rings_x[j-1];
						b.my_rings_y[j] = b.my_rings_y[j-1];
					}
					b.my_rings_x[i] = tempx;
					b.my_rings_y[i] = tempy;
					b.my_ringsonboard++;
					b.board[b.my_rings_x[i] + 5][b.my_rings_y[i] + 5] = 3;
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

		std::vector<Boardclass> blist;
		std::vector<string> strlist;
		temp_row = b.find_row(p);
		extend_before_S(blist,strlist,b,temp_row,p,str);
		for(int k=0;k<(blist.size());k++){
			//cout<<"-------------------------------------------------------------";
			if(p!=1)
				num_rings = blist[k].opp_ringsonboard;
			else
				num_rings = blist[k].my_ringsonboard;

			for(int i=0;i<num_rings;i++){
				if(p!=1){
					x = blist[k].opp_rings_x[i];
					y = blist[k].opp_rings_y[i];
				}
				else{
					x = blist[k].my_rings_x[i];
					y = blist[k].my_rings_y[i];
				}
				ring_rad = convtorad(x,y);

				//5 rings code
				//cout<<x<<" "<<y<<"\n";
				y1 = y+1;
				x1 = x;
				flag = 0;
				//cout<<"before 1 if\n";
				if(y1<=5){
					val = blist[k].board[x1+5][y1+5];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){
							if(strlist[k].length()==0)
								str1 = strlist[k] + ("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
							blist[k].update_board(str1,p);
							//cout<<"before find row\n";
							temp_row = blist[k].find_row(p);
							//cout<<"after find row\n";
							// n->move = "345";
							extend_after_S(n,blist[k],temp_row,p,str1);
							blist[k].reverse_update(str1,p);
						}		
						else{
							flag =1;
							while(val==1 || val==2){
								y1++;
								if(y1>5)
									break;
								val = blist[k].board[x1+5][y1+5];
							}
							if(val==0 && y1<=5){
							if(strlist[k].length()==0)
								str1 = strlist[k]+("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
								blist[k].update_board(str1,p);
							temp_row = blist[k].find_row(p);
							extend_after_S(n,blist[k],temp_row,p,str1);
								blist[k].reverse_update(str1,p);					
							}
						}
						y1++;
						if(y1>5 || flag==1)
							break;
						val = blist[k].board[x1+5][y1+5];
					}
				}
				y1 = y-1;
				x1 = x;
				flag = 0;

				if(y1>=-5){
					val = blist[k].board[x1+5][y1+5];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){

							if(strlist[k].length()==0)
								str1 = strlist[k]+("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
								blist[k].update_board(str1,p);
							temp_row = blist[k].find_row(p);
							//cout<<temp_row.size()<<"\n";
							extend_after_S(n,blist[k],temp_row,p,str1);
								blist[k].reverse_update(str1,p);					

						}
						else{
							flag = 1;
							while(val==1 || val==2){
								y1--;
								if(y1<-5)
									break;
								val = blist[k].board[x1+5][y1+5];
							}
							if(val==0 && y1>=-5){
							if(strlist[k].length()==0)
								str1 = strlist[k]+("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
								blist[k].update_board(str1,p);
							temp_row = blist[k].find_row(p);
							extend_after_S(n,blist[k],temp_row,p,str1);
								blist[k].reverse_update(str1,p);					
							}
						}
						y1--;
						if(y1<-5 || flag == 1)
							break;
						val = blist[k].board[x1+5][y1+5];
					}
				}
				//cout<<"before 3 if\n";
				y1 = y;
				x1 = x+1;
				flag =0;
				if(x1<=5){
					val = blist[k].board[x1+5][y1+5];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){
							if(strlist[k].length()==0)
								str1 = strlist[k]+("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
								blist[k].update_board(str1,p);
							temp_row = blist[k].find_row(p);
							extend_after_S(n,blist[k],temp_row,p,str1);
								blist[k].reverse_update(str1,p);					
						}
						else{
							flag = 1;
							while(val==1 || val==2){
								x1++;
								if(x1>5)
									break;
								val = blist[k].board[x1+5][y1+5];
							}
							if(val==0 && x1<=5){
							if(strlist[k].length()==0)
								str1 = strlist[k]+("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
								blist[k].update_board(str1,p);
							temp_row = blist[k].find_row(p);
							extend_after_S(n,blist[k],temp_row,p,str1);
								blist[k].reverse_update(str1,p);					
							}
						}
						x1++;
						if(x1>5 || flag ==1)
							break;
						val = blist[k].board[x1+5][y1+5];
					}
				}
				y1 = y;
				x1 = x-1;
				flag =0;
				if(x1>=-5){
					val = blist[k].board[x1+5][y1+5];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){
							if(strlist[k].length()==0)
								str1 = strlist[k]+("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
								blist[k].update_board(str1,p);
							temp_row = blist[k].find_row(p);
							extend_after_S(n,blist[k],temp_row,p,str1);
								blist[k].reverse_update(str1,p);					
						}
						else{
							flag = 1;
							while(val==1 || val==2){
								x1--;
								if(x1<-5)
									break;
								val = blist[k].board[x1+5][y1+5];
							}
							if(val==0 && x1>=-5){
							if(strlist[k].length()==0)
								str1 = strlist[k]+("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
								blist[k].update_board(str1,p);
							temp_row = blist[k].find_row(p);
							extend_after_S(n,blist[k],temp_row,p,str1);
								blist[k].reverse_update(str1,p);					
							}
						}
						x1--;
						if(x1<-5 || flag==1)
							break;
						val = blist[k].board[x1+5][y1+5];
					}
				}
				y1 = y+1;
				x1 = x+1;
				flag =0;
				if(y1<=5 && x1<=5){
					val = blist[k].board[x1+5][y1+5];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){
							if(strlist[k].length()==0)
								str1 = strlist[k]+("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
								blist[k].update_board(str1,p);
							temp_row = blist[k].find_row(p);
							extend_after_S(n,blist[k],temp_row,p,str1);
								blist[k].reverse_update(str1,p);					
						}
						else{
							flag = 1;
							while(val==1 || val==2){
								y1++;
								x1++;
								if(y1>5 || x1>5)
									break;
								val = blist[k].board[x1+5][y1+5];
							}
							if(val==0 && y1<=5 && x1<=5){
							if(strlist[k].length()==0)
								str1 = strlist[k]+("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
								blist[k].update_board(str1,p);
							temp_row = blist[k].find_row(p);
							extend_after_S(n,blist[k],temp_row,p,str1);
								blist[k].reverse_update(str1,p);					
							}
						}
						y1++;
						x1++;
						if(y1>5 || x1>5 || flag==1)
							break;
						val = blist[k].board[x1+5][y1+5];
					}
				}
				y1 = y-1;
				x1 = x-1;
				flag =0;
				if(y1>=-5 && x1>=-5){
					val = blist[k].board[x1+5][y1+5];
					while(val == 0 || val == 1 || val == 2){
						if(val==0){
							if(strlist[k].length()==0)
								str1 = strlist[k]+("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
								blist[k].update_board(str1,p);
							temp_row = blist[k].find_row(p);
							extend_after_S(n,blist[k],temp_row,p,str1);
								blist[k].reverse_update(str1,p);					
						}
						else{
							flag =1;
							while(val==1 || val==2){
								y1--;
								x1--;
								if(y1<-5 || x1<-5)
									break;
								val = blist[k].board[x1+5][y1+5];
							}
							if(val==0 && y1>=-5 && x1>=-5){
							if(strlist[k].length()==0)
								str1 = strlist[k]+("S "+ ring_rad +" M " + convtorad(x1,y1));
							else
								str1 = strlist[k] + (" S "+ ring_rad +" M " + convtorad(x1,y1));
								blist[k].update_board(str1,p);
							temp_row = blist[k].find_row(p);
							extend_after_S(n,blist[k],temp_row,p,str1);
								blist[k].reverse_update(str1,p);					
							}
						}
						y1--;
						x1--;
						if(y1<-5 || x1<-5 || flag==1)
							break;
						val = blist[k].board[x1+5][y1+5];
					}
				}
			}
		}
	}
	n->visited = 1;
}

double calculateHeuristic(Node*& n){
	return 0;
}
void createTree ( Node*& n, int depth, int max_depth, int p, Boardclass& b ) {

    if (depth > max_depth) {return;}
    if (depth == max_depth) {
        n->h = calculateHeuristic(n);
        //cout<<depth<<"\n";
        return;
    }
    // cout<<"in create tree\n";
    // cout<<depth<<"\n";
    if ( depth < max_depth ){
        double parent_heuristic;
        if(p!=1){
        	parent_heuristic = DBL_MAX;
        }
        else{
        	parent_heuristic = -DBL_MAX;
        }
   //      			cout<<"SUCCESSOR BEFORE-------------------------------------------------------------";
			// cout<<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<b.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }

        successor(b, n, p);
   //      			cout<<"SUCCESSOR AFTER-------------------------------------------------------------";
			// cout<<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<b.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }

        // cout<<"after successor\n";
        // cout<<n->children.size()<<"\n";
        for ( int i = 0; i < n->children.size(); i++ ){
   //      	Node* tem = n->children[i];
   //      	cout<<tem->p<<"\n";
   //      	cout<<tem->move + "\n";
   //      	cout<<"BEFORE update\n";
   //      	cout<<n->children[i]->move<<"\n";
			// cout<<"\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<b.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }

            b.update_board( n->children[i]->move, p );
			// cout<<"AFTER UPDATE\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++)
			// 		cout<<b.board[i1][j1]<<" ";
			// 	cout<<"\n";
			// }

   //          cout<<"depth increases\n";
            createTree( (n->children.at(i)), (depth + 1), max_depth, ((p%2) + 1), b);
            // cout<<"AFTER REVERSE\n";
            b.reverse_update( n->children[i]->move, p );
			// cout<<"AFTER REVERSE\n";
			// for(int i1=0;i1<11;i1++){
			// 	for(int j1=0;j1<11;j1++){
			// 		cout<<b.board[i1][j1]<<" ";
			// 	}
			// 	cout<<"\n";
			// }

            if (p == 1){
                // parent_heuristic = -DBL_MAX;
                if ( parent_heuristic < n->children.at(i)->h ){
                    parent_heuristic = n->children.at(i)->h;
                }
            }
            else if ( p == 2 ){
                // parent_heuristic = DBL_MAX;
                if ( parent_heuristic > n->children.at(i)->h ){
                    parent_heuristic = n->children.at(i)->h;
                }
            }
            // cout<<"end of 1 iteration for loop\n";
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
	player++;
	cerr<<player<<"\n";
	cerr<<n<<"\n";
	cerr<<time_left<<"\n";
	// cout<<player;
	// cout<<convtorad(-2,0)<<"\n";
	// int arrr[2];
	// main_board.convtodavid(2,10,arrr);
	// cout<<arrr[0]<<" "<<arrr[1]<<"\n";
	
	if(player==2){
		getline(cin, str);
		cerr<<str<<"\n";
		main_board.update_board(str,2);
	}
	for(int i=0;i<=4;i++){
		// cout<<"iiiii\n";
		int j,k;
		j = (rand()%10-5);
		k = (rand()%10) - 5;;
		string m;
		while(1){
			if(main_board.board[j+5][k+5]==0){
				m = "P "+convtorad(j,k);
				main_board.update_board(m,1);
				break;
			}
			j = (rand()%10-5);
			k = (rand()%10) - 5;;
		}
		cout<<m<<"\n";
		cerr<<m<<"\n";
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
	
	while(1){

		//cout<<"your move";//code it
		Node* nod_pointer = new Node(1);
		createTree ( nod_pointer, 0, 2, 1, main_board);
		main_board.update_board(nod_pointer->children[0]->move,1);
		cout<<nod_pointer->children[0]->move<<"\n";

		cout<<"\n";
		for(int i=0;i<11;i++){
			for(int j=0;j<11;j++)
				cout<<main_board.board[i][j]<<" ";
			cout<<"\n";
		}
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