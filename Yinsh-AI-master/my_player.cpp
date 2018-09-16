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
		b.board[a2+5][b2+5]=color;
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
		b.board[a2+5][b2+5]=color;
	}

}

void extend_after_S(Node*& n,Boardclass& b,vector<int>& row,int p,string str){
	// vector<int> row;
	// row.swap(b.find_row(p));
	// cout<<"In 1 extend_after_S if\n";
	int num_rings;
	string str1,str2,str3;
	std::vector<int> temp_row;
			int opp_rings_x[5],opp_rings_y[5],my_rings_x[5],my_rings_y[5];
		int num_opp,num_my;

	b.find_rings(opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);

	if(p!=1)
		num_rings = num_opp;
	else
		num_rings = num_my;
	if(row.size()==0 || num_rings<=2){
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
			int opp_rings_x[5],opp_rings_y[5],my_rings_x[5],my_rings_y[5];
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
					b.board[opp_rings_x[i] + 5][opp_rings_y[i] + 5] = 0;

					temp_row = b.find_row(p);
					extend_after_S(n,b,temp_row,p,str2);
					
					// for(int j = (b.opp_ringsonboard+1);j>i;j--){
					// 	b.opp_rings_x[j] = b.opp_rings_x[j-1];
					// 	b.opp_rings_y[j] = b.opp_rings_y[j-1];
					// }
					opp_rings_x[i] = tempx;
					opp_rings_y[i] = tempy;
					b.opp_ringsonboard++;
					b.board[opp_rings_x[i] + 5][opp_rings_y[i] + 5] = 4;
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
					b.board[my_rings_x[i] + 5][my_rings_y[i] + 5] = 0;

					temp_row = b.find_row(p);
					extend_after_S(n,b,temp_row,p,str2);
					
					// for(int j = (b.my_ringsonboard+1);j>i;j--){
					// 	b.my_rings_x[j] = b.my_rings_x[j-1];
					// 	b.my_rings_y[j] = b.my_rings_y[j-1];
					// }
					my_rings_x[i] = tempx;
					my_rings_y[i] = tempy;
					b.my_ringsonboard++;
					b.board[my_rings_x[i] + 5][my_rings_y[i] + 5] = 3;
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
			int opp_rings_x[5],opp_rings_y[5],my_rings_x[5],my_rings_y[5];
		int num_opp,num_my;

	b.find_rings(opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);

	if(p!=1)
		num_rings = num_opp;
	else
		num_rings = num_my;
	if(row.size()==0 || num_rings<=2){
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
			int opp_rings_x[5],opp_rings_y[5],my_rings_x[5],my_rings_y[5];
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
					b.board[opp_rings_x[i] + 5][opp_rings_y[i] + 5] = 0;

					temp_row = b.find_row(p);
					extend_before_S(strlist,b,temp_row,p,str2);
					
					// for(int j = (b.opp_ringsonboard+1);j>i;j--){
					// 	b.opp_rings_x[j] = b.opp_rings_x[j-1];
					// 	b.opp_rings_y[j] = b.opp_rings_y[j-1];
					// }
					opp_rings_x[i] = tempx;
					opp_rings_y[i] = tempy;
					b.opp_ringsonboard++;
					b.board[opp_rings_x[i] + 5][opp_rings_y[i] + 5] = 4;
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
					b.board[my_rings_x[i] + 5][my_rings_y[i] + 5] = 0;

					temp_row = b.find_row(p);
					extend_before_S(strlist,b,temp_row,p,str2);
					
					// for(int j = (b.my_ringsonboard+1);j>i;j--){
					// 	b.my_rings_x[j] = b.my_rings_x[j-1];
					// 	b.my_rings_y[j] = b.my_rings_y[j-1];
					// }
					my_rings_x[i] = tempx;
					my_rings_y[i] = tempy;
					b.my_ringsonboard++;
					b.board[my_rings_x[i] + 5][my_rings_y[i] + 5] = 3;
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
		int opp_rings_x[5],opp_rings_y[5],my_rings_x[5],my_rings_y[5];
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
			
			if(num_rings<=2){
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
				if(y1<=5){
				// cout<<"In 1 if\n";
					val = b.board[x1+5][y1+5];
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
								if(y1>5)
									break;
								val = b.board[x1+5][y1+5];
							}
							if(val==0 && y1<=5){
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
						if(y1>5 || flag==1)
							break;
						val = b.board[x1+5][y1+5];
					}
				}
				y1 = y-1;
				x1 = x;
				flag = 0;

				if(y1>=-5){
				// cout<<"In 2 if\n";

					val = b.board[x1+5][y1+5];
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
								if(y1<-5)
									break;
								val = b.board[x1+5][y1+5];
							}
							if(val==0 && y1>=-5){
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
						if(y1<-5 || flag == 1)
							break;
						val = b.board[x1+5][y1+5];
					}
				}
				//cout<<"before 3 if\n";
				y1 = y;
				x1 = x+1;
				flag =0;
				if(x1<=5){
				// cout<<"In 3 if\n";
					val = b.board[x1+5][y1+5];
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
								if(x1>5)
									break;
								val = b.board[x1+5][y1+5];
							}
							if(val==0 && x1<=5){
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
						if(x1>5 || flag ==1)
							break;
						val = b.board[x1+5][y1+5];
					}
				}
				y1 = y;
				x1 = x-1;
				flag =0;
				if(x1>=-5){
				// cout<<"In 4 if\n";
					val = b.board[x1+5][y1+5];
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
								if(x1<-5)
									break;
								val = b.board[x1+5][y1+5];
							}
							if(val==0 && x1>=-5){
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
						if(x1<-5 || flag==1)
							break;
						val = b.board[x1+5][y1+5];
					}
				}
				y1 = y+1;
				x1 = x+1;
				flag =0;
				if(y1<=5 && x1<=5){
				// cout<<"In 5 if\n";

					val = b.board[x1+5][y1+5];
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
								if(y1>5 || x1>5)
									break;
								val = b.board[x1+5][y1+5];
							}
							if(val==0 && y1<=5 && x1<=5){
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
						if(y1>5 || x1>5 || flag==1)
							break;
						val = b.board[x1+5][y1+5];
					}
				}
				y1 = y-1;
				x1 = x-1;
				flag =0;
				if(y1>=-5 && x1>=-5){
				// cout<<"In 6 if\n";

					val = b.board[x1+5][y1+5];
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
								if(y1<-5 || x1<-5)
									break;
								val = b.board[x1+5][y1+5];
							}
							if(val==0 && y1>=-5 && x1>=-5){
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
						if(y1<-5 || x1<-5 || flag==1)
							break;
						val = b.board[x1+5][y1+5];
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
	cerr<<"compute heuristic started\n";
	double h;
	double my_marker =0.0;
	double opp_marker = 0.0;
	h = 1024*(5 - num_my) - 1000*(5 - num_opp);
	int count =0;
	for (int i = -5; i <=5; i++){
		for (int j = -5; j <=5; j++){
			if (b.board[i+5][j+5] == 1) { my_marker = my_marker + 1;}
			if(b.board[i+5][j+5]==2){
				count++;
				// opp_marker = opp_marker + 1;
			}
			else{
				if(count!=0){
					if(count <= 3)
						h = h - pow(4,count);
					else if(count>3)
						h = h - 512;
				}
				count = 0;
			}
		}
				if(count!=0){
					if(count <= 3)
						h = h - pow(4,count);
					else if(count>3)
						h = h - 512;
				}
				count = 0;
	}
//	cerr<<"compute heuristic started\n";

	count = 0;	
	for (int j = -5; j <=5; j++){
		for (int i = -5; i <=5; i++){
			// if (b.board[i+5][j+5] == 1) { my_marker = my_marker + 1;}
			if(b.board[i+5][j+5]==2){
				count++;
				// opp_marker = opp_marker + 1;
			}
			else{
				if(count!=0){
					if(count <= 3)
						h = h - pow(4,count);
					else if(count>3)
						h = h - 512;
				}
				count = 0;
			}
		}
				if(count!=0){
					if(count <= 3)
						h = h - pow(4,count);
					else if(count>3)
						h = h - 512;
				}
				count = 0;
	}
//	cerr<<"compute heuristic started\n";

	count =0;
	int i = -5;
	int j;
	for(int z=-5;z<=5;z++){
		j = z;
		while(i<=5 && j<=5){
			if(b.board[i+5][j+5]==2){
				count++;
			}
			else{
				if(count!=0){
					if(count <= 3)
						h = h - pow(4,count);
					else if(count>3)
						h = h - 512;
				}
				count = 0;
			}
		i++;
		j++;						
		}
				if(count!=0){
					if(count <= 3)
						h = h - pow(4,count);
					else if(count>3)
						h = h - 512;
				}
				count = 0;
		i = -5;		
	}
//	cerr<<"compute heuristic started\n";

	count = 0;
	j = -5;
	for(int z=-4;z<=5;z++){
		i = z;
		while(i<=5 && j<=5){
//			cerr<<"compute heuristic started\n";
			if(b.board[i+5][j+5]==2){
				count++;
			}
			else{
				if(count!=0){
					if(count <= 3)
						h = h - pow(4,count);
					else if(count>3)
						h = h - 512;
				}
				count = 0;
			}
			i++;
			j++;			
		}
				if(count!=0){
					if(count <= 3)
						h = h - pow(4,count);
					else if(count>3)
						h = h - 512;
				}
				count = 0;
		j = -5;
	}

	h = h + 20*(my_marker);
	// cout<<h<<"\n";
	cerr<<"heuristic ends\n";
	return h;
}
void createTree ( Node*& n, int depth, int max_depth, int p, Boardclass& b,double alpha,double beta) {

     cerr<<"in create tree\n";
	int opp_rings_x[5],opp_rings_y[5],my_rings_x[5],my_rings_y[5];
	int num_opp,num_my;
//	cerr<<"create tree started\n";
	b.find_rings(opp_rings_x,opp_rings_y,my_rings_x,my_rings_y,num_opp,num_my);

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
    cerr<<"in create tree\n";

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
	// Boardclass tempb;
	int i1;
	// 	Node* nod_pointer = new Node(1);
	// int move = 0;
	// int flag;
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

		createTree ( nod_pointer, 0, 3, 1, main_board,-10000,10000);
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
		// cerr<<nod_pointer->children.size()<<"\n";
		for(i1 =0;i1<nod_pointer->children.size();i1++){
			if((abs(nod_pointer->h - nod_pointer->children[i1]->h))<=1){
				cout<<nod_pointer->children[i1]->move<<"\n";
				main_board.update_board(nod_pointer->children[i1]->move,1);
				break;				
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
		cerr<<"waiting\n";
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