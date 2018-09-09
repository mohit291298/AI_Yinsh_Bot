#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <time>

using namespace std;

#define matrix_size 11;

int board[11][11];
/*
-1 -> INVALID Position
0  -> EMPTY position
1  -> MY marker
2  -> OPPONENT's marker
3  -> MY ring
4  -> OPPONENT's ring
*/

int ringsonboard;
int rings_x[5],rings_y[5];

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

void convtodavid(int a,int b,int *arr){
	//convert radial to david coordinates
	arr[0] = a;
	arr[1] = b;
	//assuming a is the x - coordinate 
	//assuming b is the y - coordinate 
	if ( b >= 0 && b <= a-1 ) {
		arr[0] = b;
		arr[1] = a;
	}

	if ( b >= a && b <= 2*a - 1 ){
		arr[0] = a;
		arr[1] = 2*a - b;
	}

	if ( b >= 2*a && b <= 3*a - 1 ){
		arr[0] = 3*a - b;
		arr[1] = 2*a - b;
	}

	if ( b >= 3*a && b <= 4*a - 1 ){
		arr[0] = 3*a - b;
		arr[1] = -a;
	}

	if ( b >= 4*a && b <= 5*a - 1 ){
		arr[0] = -a;
		arr[1] = b - 5*a;
	}

	if ( b >= 5*a && b <= 6*a - 1 ){
		arr[0] = b - 6*a;
		arr[1] = b - 5*a;
	}

}

void update_board(string str){

	char cstr[str.size() +1];
	strcpy(cstr,str.c_str());
	char *token = strtok(cstr, " ");
	
	int arr[2];
	int r,s;
	if(token[0]=='P'){
		token = strtok(NULL, " ");
		r = (atoi(token));
		token = strtok(NULL, " ");
		s = (atoi(token));
		convtodavid(r,s,arr);
		int x = arr[0];
		int y = arr[1];
		board[x+5][y+5]=4;
	}
	else if(token[0]=='S'){
		token = strtok(NULL, " ");
		r = (atoi(token));
		token = strtok(NULL, " ");
		s = (atoi(token));
		convtodavid(r,s,arr);
		int x1 = arr[0];
		int y1 = arr[1];

		token = strtok(NULL, " "); //this is M

		token = strtok(NULL, " ");
		r = (atoi(token));
		token = strtok(NULL, " ");
		s = (atoi(token));
		convtodavid(r,s,arr);
		int x2 = arr[0];
		int y2 = arr[1];

		board[x1+5][y1+5] = 2;
		int a = x1;
		int b = y1;
		if(x1==x2){
			if(y2>y1){
				b++;
				while(board[a+5][b+5]==0 && b<y2){
					b++;
				}
				if(b==y2)
					board[x2+5][y2+5]=4;
				else{
					while(b<y2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						b++;
					}
					board[x2+5][y2+5]=4;
				}
			}
			else if(y2 < y1){
				b--;
				while(board[a+5][b+5]==0 && b>y2){
					b--;
				}
				if(b==y2)
					board[x2+5][y2+5]=4;
				else{
					while(b>y2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						b--;
					}
					board[x2+5][y2+5]=4;
				}
			}
		}
		else if(y1==y2){
			if(x2>x1){
				a++;
				while(board[a+5][b+5]==0 && a<x2){
					a++;
				}
				if(a==y2)
					board[x2+5][y2+5]=4;
				else{
					while(a<x2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						a++;
					}
					board[x2+5][y2+5]=4;
				}
			}
			else if(x2 < x1){
				a--;
				while(board[a+5][b+5]==0 && a>x2){
					a--;
				}
				if(a==x2)
					board[x2+5][y2+5]=4;
				else{
					while(a>x2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						a--;
					}
					board[x2+5][y2+5]=4;
				}
			}
		}
		else{
			if(y2>y1){
				b++;
				a++;
				while(board[a+5][b+5]==0 && b<y2){
					b++;
					a++;
				}
				if(b==y2)
					board[x2+5][y2+5]=4;
				else{
					while(b<y2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						b++;
						a++;
					}
					board[x2+5][y2+5]=4;
				}
			}
			else if(y2 < y1){
				b--;
				a--;
				while(board[a+5][b+5]==0 && b>y2){
					b--;
					a--;
				}
				if(b==y2)
					board[x2+5][y2+5]=4;
				else{
					while(b>y2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						b--;
						a--;
					}
					board[x2+5][y2+5]=4;
				}
			}
		}
		token = strtok(NULL, " ");
		if(token != NULL){
			// cout<<token<<"\n";
			token = strtok(NULL, " ");
			r = (atoi(token));
			token = strtok(NULL, " ");
			s = (atoi(token));
			convtodavid(r,s,arr);
			int a1 = arr[0];
			int b1 = arr[1];
			// cout<<a1<<" "<<b1<<"\n";

			token = strtok(NULL, " "); //this is RE

			token = strtok(NULL, " ");
			r = (atoi(token));
			token = strtok(NULL, " ");
			s = (atoi(token));
			convtodavid(r,s,arr);
			int a2 = arr[0];
			int b2 = arr[1];

			token = strtok(NULL, " "); //this is X

			// cout<<a2<<" "<<b2<<"\n";
			token = strtok(NULL, " ");
			r = (atoi(token));
			token = strtok(NULL, " ");
			s = (atoi(token));
			convtodavid(r,s,arr);
			int a3 = arr[0];
			int b3 = arr[1];
			// cout<<a3<<" "<<b3<<"\n";
			int p1 = a1;
			int q1 = b1;
			if(a1==a2){
				if(b2>b1){
					while(q1!=b2){
						board[p1+5][q1+5] = 0;
						q1++;
					}
				}
				else{
					while(q1!=b2){
						board[p1+5][q1+5] = 0;
						q1--;
					}					
				}
				board[a2+5][b2+5]=0;
			}
			else if(b1==b2){
				if(a2>a1){
					while(p1!=a2){
						board[p1+5][q1+5] = 0;
						p1++;
					}
				}
				else{
					while(p1!=a2){
						board[p1+5][q1+5] = 0;
						p1--;
					}					
				}
				board[a2+5][b2+5]=0;
			}
			else{
				if(b2>b1){
					while(q1!=b2){
						board[p1+5][q1+5] = 0;
						q1++;
						p1++;
					}
				}
				else{
					while(q1!=b2){
						board[p1+5][q1+5] = 0;
						q1--;
						p1--;
					}					
				}
				board[a2+5][b2+5]=0;
			}

			board[a3+5][b3+5] = 0;
		}				
	}
	else if(token[0] == 'R' && token[1]=='S')
	{
		r = (atoi(token));
		token = strtok(NULL, " ");
		s = (atoi(token));
		convtodavid(r,s,arr);
		int a1 = arr[0];
		int b1 = arr[1];

		token = strtok(NULL, " "); //this is M

		token = strtok(NULL, " ");
		r = (atoi(token));
		token = strtok(NULL, " ");
		s = (atoi(token));
		convtodavid(r,s,arr);
		int a2 = arr[0];
		int b2 = arr[1];

		token = strtok(NULL, " "); //this is M

		token = strtok(NULL, " ");
		r = (atoi(token));
		token = strtok(NULL, " ");
		s = (atoi(token));
		convtodavid(r,s,arr);
		int a3 = arr[0];
		int b3 = arr[1];

		int p1 = a1;
		int q1 = b1;
		if(a1==a2){
			if(b2>b1){
				while(q1!=b2){
					board[p1+5][q1+5] = 0;
					q1++;
				}
			}
			else{
				while(q1!=b2){
					board[p1+5][q1+5] = 0;
					q1--;
				}					
			}
			board[a2+5][b2+5]=0;
		}
		else if(b1==b2){
			if(a2>a1){
				while(p1!=a2){
					board[p1+5][q1+5] = 0;
					p1++;
				}
			}
			else{
				while(p1!=a2){
					board[p1+5][q1+5] = 0;
					p1--;
				}					
			}
			board[a2+5][b2+5]=0;
		}
		else{
			if(b2>b1){
				while(q1!=b2){
					board[p1+5][q1+5] = 0;
					q1++;
					p1++;
				}
			}
			else{
				while(q1!=b2){
					board[p1+5][q1+5] = 0;
					q1--;
					p1--;
				}					
			}
			board[a2+5][b2+5]=0;
		}
		board[a3+5][b3+5] = 0;

		token = strtok(NULL, " ");

		if(token[0]=='S'){
			token = strtok(NULL, " ");
			r = (atoi(token));
			token = strtok(NULL, " ");
			s = (atoi(token));
			convtodavid(r,s,arr);
			int x1 = arr[0];
			int y1 = arr[1];

			token = strtok(NULL, " "); //this is M

			token = strtok(NULL, " ");
			r = (atoi(token));
			token = strtok(NULL, " ");
			s = (atoi(token));
			convtodavid(r,s,arr);
			int x2 = arr[0];
			int y2 = arr[1];

			board[x1+5][y1+5] = 2;
			int a = x1;
			int b = y1;
			if(x1==x2){
				if(y2>y1){
					b++;
					while(board[a+5][b+5]==0 && b<y2){
						b++;
					}
					if(b==y2)
						board[x2+5][y2+5]=4;
					else{
						while(b<y2){
							board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							b++;
						}
						board[x2+5][y2+5]=4;
					}
				}
				else if(y2 < y1){
					b--;
					while(board[a+5][b+5]==0 && b>y2){
						b--;
					}
					if(b==y2)
						board[x2+5][y2+5]=4;
					else{
						while(b>y2){
							board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							b--;
						}
						board[x2+5][y2+5]=4;
					}
				}
			}
			else if(y1==y2){
				if(x2>x1){
					a++;
					while(board[a+5][b+5]==0 && a<x2){
						a++;
					}
					if(a==y2)
						board[x2+5][y2+5]=4;
					else{
						while(a<x2){
							board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							a++;
						}
						board[x2+5][y2+5]=4;
					}
				}
				else if(x2 < x1){
					a--;
					while(board[a+5][b+5]==0 && a>x2){
						a--;
					}
					if(a==x2)
						board[x2+5][y2+5]=4;
					else{
						while(a>x2){
							board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							a--;
						}
						board[x2+5][y2+5]=4;
					}
				}
			}
			else{
				if(y2>y1){
					b++;
					a++;
					while(board[a+5][b+5]==0 && b<y2){
						b++;
						a++;
					}
					if(b==y2)
						board[x2+5][y2+5]=4;
					else{
						while(b<y2){
							board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							b++;
							a++;
						}
						board[x2+5][y2+5]=4;
					}
				}
				else if(y2 < y1){
					b--;
					a--;
					while(board[a+5][b+5]==0 && b>y2){
						b--;
						a--;
					}
					if(b==y2)
						board[x2+5][y2+5]=4;
					else{
						while(b>y2){
							board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							b--;
							a--;
						}
						board[x2+5][y2+5]=4;
					}
				}
			}
			token = strtok(NULL, " ");
			if(token != NULL){
				token = strtok(NULL, " ");
				r = (atoi(token));
				token = strtok(NULL, " ");
				s = (atoi(token));
				convtodavid(r,s,arr);
				int a1 = arr[0];
				int b1 = arr[1];

				token = strtok(NULL, " "); //this is RE

				token = strtok(NULL, " ");
				r = (atoi(token));
				token = strtok(NULL, " ");
				s = (atoi(token));
				convtodavid(r,s,arr);
				int a2 = arr[0];
				int b2 = arr[1];

				token = strtok(NULL, " "); //this is X

				token = strtok(NULL, " ");
				r = (atoi(token));
				token = strtok(NULL, " ");
				s = (atoi(token));
				convtodavid(r,s,arr);
				int a3 = arr[0];
				int b3 = arr[1];

				int p1 = a1;
				int q1 = b1;
				if(a1==a2){
					if(b2>b1){
						while(q1!=b2){
							board[p1+5][q1+5] = 0;
							q1++;
						}
					}
					else{
						while(q1!=b2){
							board[p1+5][q1+5] = 0;
							q1--;
						}					
					}
					board[a2+5][b2+5]=0;
				}
				else if(b1==b2){
					if(a2>a1){
						while(p1!=a2){
							board[p1+5][q1+5] = 0;
							p1++;
						}
					}
					else{
						while(p1!=a2){
							board[p1+5][q1+5] = 0;
							p1--;
						}					
					}
					board[a2+5][b2+5]=0;
				}
				else{
					if(b2>b1){
						while(q1!=b2){
							board[p1+5][q1+5] = 0;
							q1++;
							p1++;
						}
					}
					else{
						while(q1!=b2){
							board[p1+5][q1+5] = 0;
							q1--;
							p1--;
						}					
					}
					board[a2+5][b2+5]=0;
				}

				board[a3+5][b3+5] = 0;
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
	// cout<<player<<" "<<n<<" "<<time_left<<"\n";
	for(int j=5;j>=-5;j--){
		for(int i=-5;i<=5;i++){
			if(j==5){
				if(i<=4 && i>=1)
					continue;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==4){
				if(i<=5 && i>=-1)
					continue;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==3){
				if(i<=5 && i>=-2)
					continue;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==2){
				if(i<=5 && i>=-3)
					continue;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==1){
				if(i<=5 && i>=-4)
					continue;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==0){
				if(i<=4 && i>=-4)
					continue;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==-1){
				if(i<=4 && i>=-5)
					continue;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==-2){
				if(i<=3 && i>=-5)
					continue;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==-3){
				if(i<=2 && i>=-5)
					continue;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==-4){
				if(i<=1 && i>=-5)
					continue;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==-5){
				if(i<=-1 && i>=-4)
					continue;
				else
					board[i+5][j+5] = -1;
			}

		}
	}

	// for(int i=0;i<11;i++){
	// 	for(int j=0;j<11;j++)
	// 		cout<<board[i][j]<<" ";
	// 	cout<<"\n";
	// }
	
	if(player==1){
		getline(cin, str);
		update_board(str);
	}
	while(1){

		//cout<<"your move";//code it
		getline(cin, str);
		update_board(str);
		cout<<"\n";
		for(int i=0;i<11;i++){
			for(int j=0;j<11;j++)
				cout<<board[i][j]<<" ";
			cout<<"\n";
		}

	}	



}