#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <utility>
#include <iostream>
#include <sstream> 
#include "Boardclass.h"

using namespace std;

// Date constructor
Boardclass::Boardclass()
{
	my_ringsonboard = 0;
	opp_ringsonboard = 0;
    for(int j=5;j>=-5;j--){
		for(int i=-5;i<=5;i++){
			if(j==5){
				if(i<=4 && i>=1)
					board[i+5][j+5] = 0;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==4){
				if(i<=5 && i>=-1)
					board[i+5][j+5] = 0;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==3){
				if(i<=5 && i>=-2)
					board[i+5][j+5] = 0;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==2){
				if(i<=5 && i>=-3)
					board[i+5][j+5] = 0;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==1){
				if(i<=5 && i>=-4)
					board[i+5][j+5] = 0;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==0){
				if(i<=4 && i>=-4)
					board[i+5][j+5] = 0;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==-1){
				if(i<=4 && i>=-5)
					board[i+5][j+5] = 0;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==-2){
				if(i<=3 && i>=-5)
					board[i+5][j+5] = 0;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==-3){
				if(i<=2 && i>=-5)
					board[i+5][j+5] = 0;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==-4){
				if(i<=1 && i>=-5)
					board[i+5][j+5] = 0;
				else
					board[i+5][j+5] = -1;
			}
			else if(j==-5){
				if(i<=-1 && i>=-4)
					board[i+5][j+5] = 0;
				else
					board[i+5][j+5] = -1;
			}
		}
	}
}
 
// Date member function

void Boardclass::convtodavid(int a,int b,int *arr){
	//convert radial to david coordinates
	arr[0] = a;
	arr[1] = b;
	// assuming a is the x - coordinate 
	// assuming b is the y - coordinate 
	if ( a == 0  && b == 0){
		return;
	}

	if ( b >= 0 && b <= a-1 ) {
		arr[0] = b;
		arr[1] = a;
		return;
	}

	if ( b >= a && b <= 2*a - 1 ){
		arr[0] = a;
		arr[1] = 2*a - b;
		return;
	}

	if ( b >= 2*a && b <= 3*a - 1 ){
		arr[0] = 3*a - b;
		arr[1] = 2*a - b;
		return;
	}

	if ( b >= 3*a && b <= 4*a - 1 ){
		arr[0] = 3*a - b;
		arr[1] = -a;
		return;
	}

	if ( b >= 4*a && b <= 5*a - 1 ){
		arr[0] = -a;
		arr[1] = b - 5*a;
		return;
	}

	if ( b >= 5*a && b <= 6*a - 1 ){
		arr[0] = b - 6*a;
		arr[1] = b - 5*a;
		return;
	}

}


void Boardclass::convtorad(int a,int b,int *arr){
	//convert radial to david coordinates
	arr[0] = a;
	arr[1] = b;
	//assuming a is the x - coordinate 
	//assuming b is the y - coordinate 

if ( a * b >= 0) {
		arr[0] = max(abs(a),abs(b));
	}
	else {
		arr[0] = abs(a) + abs(b);
	}
	
	if ( b == arr[0] ) {
		arr[1] = a;
		return;
	}
	
	if ( a == arr[0] ) {
		arr[1] =  2 * arr[0] - b; 
		return;
	}

	if ( b == -1 * arr[0] ) {
		arr[1] = 3 * arr[0] - a ;
		return;
	}

	if ( a == -1 * arr[0] ){
		arr[1] =  5 * arr[0] + b;
		return;
	}

	if ( a * b <= 0 ){
		if ( a > 0 ){
			arr[1] = 2 * arr[0] - b;
			return;
		}
		if ( b > 0 ){
			arr[1] = 6 * arr[0] + a;
			return;
		}
	}

}

// void my_set(int x,int y,int i){
// 	my_rings_x[i] = x;
// 	my_rings_y[i] = y;
// }
// void opp_set(int x,int y,int i);
// void num_rings_set(int a,int b);

void Boardclass::copy_board(Boardclass& b){
	for(int i=0;i<11;i++){
		for(int j=0;j<11;j++)
			board[i][j] = b.board[i][j];
	}
	my_ringsonboard = b.my_ringsonboard;
	opp_ringsonboard = b.opp_ringsonboard;
	// for(int i=0;i<5;i++){
	// 	my_rings_x[i] = b.my_rings_x[i];
	// 	my_rings_y[i] = b.my_rings_y[i];
	// 	opp_rings_x[i] = b.opp_rings_x[i];
	// 	opp_rings_y[i] = b.opp_rings_y[i];
	// }

}
void Boardclass::find_rings(int *opp_rings_x,int *opp_rings_y,int *my_rings_x,int *my_rings_y,int &num_opp,int &num_my){
	num_my = 0;
	num_opp = 0;
	for(int i=-5;i<=5;i++){
		for(int j=-5;j<=5;j++){
			if(board[i+5][j+5]==3){
				my_rings_x[num_my] = i;
				my_rings_y[num_my] = j;
				num_my++;
			}
			else if(board[i+5][j+5]==4){
				opp_rings_x[num_opp] = i;
				opp_rings_y[num_opp] = j;
				num_opp++;
			}
		}
	}
}
void Boardclass::update_board(string str,int p){
	if(str.length()==0)
		return;
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
		if(p!=1){
			board[x+5][y+5]=4;
			// opp_rings_x[opp_ringsonboard] = x;
			// opp_rings_y[opp_ringsonboard] = y;
			opp_ringsonboard++;

		}
		else{
			board[x+5][y+5]=3;
			// my_rings_x[my_ringsonboard] = x;
			// my_rings_y[my_ringsonboard] = y;
			my_ringsonboard++;
		}
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
		// cout<<x1<<" "<<y1<<"\n";
		// cout<<x2<<" "<<y2<<"\n";
		// int prev;
		if(p!=1){
			board[x1+5][y1+5]=2;
			// for(int i=0;i<opp_ringsonboard;i++){
			// 	cout<<opp_rings_x[i]<<" "<<opp_rings_y[i]<<"\n";
			// 	if(opp_rings_x[i]==x1 && opp_rings_y[i]==y1){
			// 		prev = i;
			// 		break;
			// 	}
			// }
		}
		else{
			board[x1+5][y1+5]=1;
			// for(int i=0;i<my_ringsonboard;i++){
			// 	if(my_rings_x[i]==x1 && my_rings_y[i]==y1){
			// 		prev = i;
			// 		break;
			// 	}
			// }
		}
		// cout<<"PREV"<<prev<<"\n";
		int a = x1;
		int b = y1;
		if(x1==x2){
			if(y2>y1){
				// cout<<"in correct loop\n";
		//		cout<<prev<<"\n";
				b++;
				while(board[a+5][b+5]==0 && b<y2){
					b++;
				}
				if(b==y2){
					if(p!=1){
						// cout<<"ring to do\n";
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{

						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
				}
				else{
					while(b<y2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						b++;
					}
					if(p!=1){
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{
						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
				}
			}
			else if(y2 < y1){
				b--;
				while(board[a+5][b+5]==0 && b>y2){
					b--;
				}
				if(b==y2){
					if(p!=1){
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{
						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
				}
				else{
					while(b>y2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						b--;
					}
					if(p!=1){
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{
						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
				}
			}
		}
		else if(y1==y2){
			if(x2>x1){
				a++;
				while(board[a+5][b+5]==0 && a<x2){
					a++;
				}
				if(a==x2){
					if(p!=1){
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{
						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
				}
				else{
					while(a<x2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						a++;
					}
					if(p!=1){
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{
						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
				}
			}
			else if(x2 < x1){
				a--;
				while(board[a+5][b+5]==0 && a>x2){
					a--;
				}
				if(a==x2){
					if(p!=1){
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{
						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
				}
				else{
					while(a>x2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						a--;
					}
					if(p!=1){
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{
						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
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
				if(b==y2){
					if(p!=1){
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{
						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
				}
				else{
					while(b<y2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						b++;
						a++;
					}
					if(p!=1){
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{
						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
				}
			}
			else if(y2 < y1){
				b--;
				a--;
				while(board[a+5][b+5]==0 && b>y2){
					b--;
					a--;
				}
				if(b==y2){
					if(p!=1){
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{
						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
				}
				else{
					while(b>y2){
						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
						b--;
						a--;
					}
					if(p!=1){
						board[x2+5][y2+5]=4;
						// opp_rings_x[prev] = x2;
						// opp_rings_y[prev] = y2;
						//opp_ringsonboard++;

					}
					else{
						board[x2+5][y2+5]=3;
						// my_rings_x[prev] = x2;
						// my_rings_y[prev] = y2;
						//my_ringsonboard++;
					}
				}
			}
		}
		token = strtok(NULL, " ");
		while(token != NULL){
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
			int prev2=0;
			if(p!=1){
				//board[x1+5][y1+5]=2;
				// for(int i=0;i<opp_ringsonboard;i++){
				// 	if(prev2==1){
				// 		if(i==(opp_ringsonboard-1))
				// 			break;
				// 		opp_rings_x[i] = opp_rings_x[i+1];
				// 		opp_rings_y[i] = opp_rings_y[i+1];
				// 	}
				// 	else if(opp_rings_x[i]==a3 && opp_rings_y[i]==b3){
				// 		if(i==(opp_ringsonboard-1))
				// 			break;
				// 		opp_rings_x[i] = opp_rings_x[i+1];
				// 		opp_rings_y[i] = opp_rings_y[i+1];
				// 		prev2 = 1;
				// 	}
				// }
				opp_ringsonboard--;
			}
			else{
				//board[x1+5][y1+5]=1;
				// for(int i=0;i<my_ringsonboard;i++){
				// 	if(prev2==1){
				// 		if(i==(my_ringsonboard-1))
				// 			break;
				// 		my_rings_x[i] = my_rings_x[i+1];
				// 		my_rings_y[i] = my_rings_y[i+1];
				// 	}
				// 	else if(my_rings_x[i]==a3 && my_rings_y[i]==b3){
				// 		if(i==(my_ringsonboard-1))
				// 			break;
				// 		my_rings_x[i] = my_rings_x[i+1];
				// 		my_rings_y[i] = my_rings_y[i+1];
				// 		prev2 = 1;
				// 	}
				// }
				my_ringsonboard--;
			}
			token = strtok(NULL, " ");
		}				
	}
	else if(token[0] == 'R' && token[1]=='S')
	{
		// cout<<"in correct loop\n";
		while(token != NULL){
			token = strtok(NULL, " ");
			r = (atoi(token));
			token = strtok(NULL, " ");
			s = (atoi(token));
			convtodavid(r,s,arr);
			int a1 = arr[0];
			int b1 = arr[1];
			// cout<<a1<<" "<<b1<<"\n";
			token = strtok(NULL, " "); //this is M

			token = strtok(NULL, " ");
			r = (atoi(token));
			token = strtok(NULL, " ");
			s = (atoi(token));
			convtodavid(r,s,arr);
			int a2 = arr[0];
			int b2 = arr[1];
			// cout<<a2<<" "<<b2<<"\n";
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
						// cout<<"inner correct\n";
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
			int prev2=0;
			if(p!=1){
				//board[x1+5][y1+5]=2;
				// for(int i=0;i<opp_ringsonboard;i++){
				// 	if(prev2==1){
				// 		if(i==(opp_ringsonboard-1))
				// 			break;
				// 		opp_rings_x[i] = opp_rings_x[i+1];
				// 		opp_rings_y[i] = opp_rings_y[i+1];
				// 	}
				// 	else if(opp_rings_x[i]==a3 && opp_rings_y[i]==b3){
				// 		if(i==(opp_ringsonboard-1))
				// 			break;
				// 		opp_rings_x[i] = opp_rings_x[i+1];
				// 		opp_rings_y[i] = opp_rings_y[i+1];
				// 		prev2 = 1;
				// 	}
				// }
				opp_ringsonboard--;
			}
			else{
				//board[x1+5][y1+5]=1;
				// for(int i=0;i<my_ringsonboard;i++){
				// 	if(prev2==1){
				// 		if(i==(my_ringsonboard-1))
				// 			break;
				// 		my_rings_x[i] = my_rings_x[i+1];
				// 		my_rings_y[i] = my_rings_y[i+1];
				// 	}
				// 	else if(my_rings_x[i]==a3 && my_rings_y[i]==b3){
				// 		if(i==(my_ringsonboard-1))
				// 			break;
				// 		my_rings_x[i] = my_rings_x[i+1];
				// 		my_rings_y[i] = my_rings_y[i+1];
				// 		prev2 = 1;
				// 	}
				// }
				my_ringsonboard--;
			}

			token = strtok(NULL, " ");
			// cout<<"TOKEN END"<<token<<"\n";
			if(token != NULL){
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

					// int prev;
					if(p!=1){
						board[x1+5][y1+5]=2;
						// for(int i=0;i<opp_ringsonboard;i++){
						// 	if(opp_rings_x[i]==x1 && opp_rings_y[i]==y1){
						// 		prev = i;
						// 		break;
						// 	}
						// }
					}
					else{
						board[x1+5][y1+5]=1;
						// for(int i=0;i<my_ringsonboard;i++){
						// 	if(my_rings_x[i]==x1 && my_rings_y[i]==y1){
						// 		prev = i;
						// 		break;
						// 	}
						// }
					}
					int a = x1;
					int b = y1;
					if(x1==x2){
						if(y2>y1){
							b++;
							while(board[a+5][b+5]==0 && b<y2){
								b++;
							}
							if(b==y2){
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
							}
							else{
								while(b<y2){
									board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
									b++;
								}
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
							}
						}
						else if(y2 < y1){
							b--;
							while(board[a+5][b+5]==0 && b>y2){
								b--;
							}
							if(b==y2){
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
							}
							else{
								while(b>y2){
									board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
									b--;
								}
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
							}
						}
					}
					else if(y1==y2){
						if(x2>x1){
							a++;
							while(board[a+5][b+5]==0 && a<x2){
								a++;
							}
							if(a==x2){
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
							}
							else{
								while(a<x2){
									board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
									a++;
								}
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
							}
						}
						else if(x2 < x1){
							a--;
							while(board[a+5][b+5]==0 && a>x2){
								a--;
							}
							if(a==x2){
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
							}
							else{
								while(a>x2){
									board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
									a--;
								}
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
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
							if(b==y2){
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
							}
							else{
								while(b<y2){
									board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
									b++;
									a++;
								}
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
							}
						}
						else if(y2 < y1){
							b--;
							a--;
							while(board[a+5][b+5]==0 && b>y2){
								b--;
								a--;
							}
							if(b==y2){
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
							}
							else{
								while(b>y2){
									board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
									b--;
									a--;
								}
								if(p!=1){
									board[x2+5][y2+5]=4;
									// opp_rings_x[prev] = x2;
									// opp_rings_y[prev] = y2;
									//opp_ringsonboard++;

								}
								else{
									board[x2+5][y2+5]=3;
									// my_rings_x[prev] = x2;
									// my_rings_y[prev] = y2;
									//my_ringsonboard++;
								}
							}
						}
					}
					token = strtok(NULL, " ");
					while(token != NULL){
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
						int prev2=0;
						if(p!=1){
							//board[x1+5][y1+5]=2;
							// for(int i=0;i<opp_ringsonboard;i++){
							// 	if(prev2==1){
							// 		if(i==(opp_ringsonboard-1))
							// 			break;
							// 		opp_rings_x[i] = opp_rings_x[i+1];
							// 		opp_rings_y[i] = opp_rings_y[i+1];
							// 	}
							// 	else if(opp_rings_x[i]==a3 && opp_rings_y[i]==b3){
							// 		if(i==(opp_ringsonboard-1))
							// 			break;
							// 		opp_rings_x[i] = opp_rings_x[i+1];
							// 		opp_rings_y[i] = opp_rings_y[i+1];
							// 		prev2 = 1;
							// 	}
							// }
							opp_ringsonboard--;
						}
						else{
							//board[x1+5][y1+5]=1;
							// for(int i=0;i<my_ringsonboard;i++){
							// 	if(prev2==1){
							// 		if(i==(my_ringsonboard-1))
							// 			break;
							// 		my_rings_x[i] = my_rings_x[i+1];
							// 		my_rings_y[i] = my_rings_y[i+1];
							// 	}
							// 	else if(my_rings_x[i]==a3 && my_rings_y[i]==b3){
							// 		if(i==(my_ringsonboard-1))
							// 			break;
							// 		my_rings_x[i] = my_rings_x[i+1];
							// 		my_rings_y[i] = my_rings_y[i+1];
							// 		prev2 = 1;
							// 	}
							// }
							my_ringsonboard--;
						}
						token = strtok(NULL, " ");
					}				
				}
			}
		}
	}
	// cout<<"function end\n";
}

//Call this function as follows:
//Str is the string of move of the child(when u want to go back to parent)
//p is the player no. of the parent or you can say 1+(player no. of child)%2

void Boardclass::reverse_update(string str,int p){
	if(str.length()==0)
		return;
	char cstr[str.size() +1];
	strcpy(cstr,str.c_str());
	char *token = strtok(cstr, " ");
	std::vector<string> vec;
	while(token != NULL){
		std::string st(token);
		vec.push_back(st);
		token = strtok(NULL, " ");	
	}
	int r,s;
	int arr[2];
	int iter = (vec.size() - 1);
	while(iter > 0){
		if(vec.at(iter - 2)[0]=='M'){
			stringstream geek((vec.at(iter)));
			geek >> s;
			stringstream geek1((vec.at(iter-1)));
			geek1 >> r;
			convtodavid(r,s,arr);
			int x1 = arr[0];
			int y1 = arr[1];

			stringstream geek2((vec.at(iter-3)));
			geek2 >> s;
			stringstream geek3((vec.at(iter-4)));
			geek3 >> r;
			convtodavid(r,s,arr);
			int x2 = arr[0];
			int y2 = arr[1];

//		int prev;
			if(p!=1){
				board[x1+5][y1+5]=0;
				// for(int i=0;i<opp_ringsonboard;i++){
				// 	if(opp_rings_x[i]==x1 && opp_rings_y[i]==y1){
				// 		prev = i;
				// 		break;
				// 	}
				// }
			}
			else{
				board[x1+5][y1+5]=0;
				// for(int i=0;i<my_ringsonboard;i++){
				// 	if(my_rings_x[i]==x1 && my_rings_y[i]==y1){
				// 		prev = i;
				// 		break;
				// 	}
				// }
			}
			int a = x1;
			int b = y1;
			if(x1==x2){
				if(y2>y1){
					b++;
					while(board[a+5][b+5]==0 && b<y2){
						b++;
					}
					if(b==y2){
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;

						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
					}
					else{
						while(b<y2){
							if(board[a+5][b+5] == 0){
								board[a+5][b+5] = 0;
							}
							else{
								board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							}
							b++;
						}
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;

						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
					}
				}
				else if(y2 < y1){
					b--;
					while(board[a+5][b+5]==0 && b>y2){
						b--;
					}
					if(b==y2){
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;

						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
					}
					else{
						while(b>y2){
							if(board[a+5][b+5] == 0){
								board[a+5][b+5] = 0;
							}
							else{
								board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							}
							b--;
						}
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;

						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
					}
				}
			}
			else if(y1==y2){
				if(x2>x1){
					a++;
					while(board[a+5][b+5]==0 && a<x2){
						a++;
					}
					if(a==x2){
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;

						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
					}
					else{
						while(a<x2){
							if(board[a+5][b+5] == 0){
								board[a+5][b+5] = 0;
							}
							else{
								board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							}
							a++;
						}
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;

						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
					}
				}
				else if(x2 < x1){
					a--;
					while(board[a+5][b+5]==0 && a>x2){
						a--;
					}
					if(a==x2){
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;

						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
					}
					else{
						while(a>x2){
							if(board[a+5][b+5] == 0){
								board[a+5][b+5] = 0;
							}
							else{
								board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							}
							a--;
						}
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;
						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
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
					if(b==y2){
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;

						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
					}
					else{
						while(b<y2){
							if(board[a+5][b+5] == 0){
								board[a+5][b+5] = 0;
							}
							else{
								board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							}
							b++;
							a++;
						}
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;

						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
					}
				}
				else if(y2 < y1){
					b--;
					a--;
					while(board[a+5][b+5]==0 && b>y2){
						b--;
						a--;
					}
					if(b==y2){
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;

						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
					}
					else{
						while(b>y2){
							if(board[a+5][b+5] == 0){
								board[a+5][b+5] = 0;
							}
							else{
								board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
							}
							b--;
							a--;
						}
						if(p!=1){
							board[x2+5][y2+5]=4;
							// opp_rings_x[prev] = x2;
							// opp_rings_y[prev] = y2;
							//opp_ringsonboard++;

						}
						else{
							board[x2+5][y2+5]=3;
							// my_rings_x[prev] = x2;
							// my_rings_y[prev] = y2;
							//my_ringsonboard++;
						}
					}
				}
			}
			iter = iter - 6;
		}
		else if(vec.at(iter - 2)[0]=='R'){
			stringstream geek((vec.at(iter)));
			geek >> s;
			stringstream geek1((vec.at(iter-1)));
			geek1 >> r;
			convtodavid(r,s,arr);
			int a2 = arr[0];
			int b2 = arr[1];

			stringstream geek2((vec.at(iter-3)));
			geek2 >> s;
			stringstream geek3((vec.at(iter-4)));
			geek3 >> r;
			convtodavid(r,s,arr);
			int a1 = arr[0];
			int b1 = arr[1];
			int p1 = a1;
			int q1 = b1;
			if(a1==a2){
				if(b2>b1){
					while(q1!=b2){
						board[p1+5][q1+5] = p;
						q1++;
					}
				}
				else{
					while(q1!=b2){
						board[p1+5][q1+5] = p;
						q1--;
					}					
				}
				board[a2+5][b2+5]=p;
			}
			else if(b1==b2){
				if(a2>a1){
					while(p1!=a2){
						board[p1+5][q1+5] = p;
						p1++;
					}
				}
				else{
					while(p1!=a2){
						board[p1+5][q1+5] = p;
						p1--;
					}					
				}
				board[a2+5][b2+5]=p;
			}
			else{
				if(b2>b1){
					while(q1!=b2){
						board[p1+5][q1+5] = p;
						q1++;
						p1++;
					}
				}
				else{
					while(q1!=b2){
						board[p1+5][q1+5] = p;
						q1--;
						p1--;
					}					
				}
				board[a2+5][b2+5]=p;
			}			
			iter = iter - 6;
		}
		else if(vec.at(iter - 2)[0]=='X'){
			stringstream geek((vec.at(iter)));
			geek >> s;
			stringstream geek1((vec.at(iter-1)));
			geek1 >> r;
			convtodavid(r,s,arr);
			int a3 = arr[0];
			int b3 = arr[1];
			board[a3+5][b3+5] = p+2;
			int prev2=0;
			if(p!=1){
				//board[x1+5][y1+5]=2;
				// opp_rings_x[opp_ringsonboard] = a3;
				// opp_rings_y[opp_ringsonboard] = b3;

				opp_ringsonboard++;
			}
			else{
				//board[x1+5][y1+5]=1;
				// my_rings_x[my_ringsonboard] = a3;
				// my_rings_y[my_ringsonboard] = b3;

				my_ringsonboard++;
			}
			iter = iter - 3;
		}
		else{
		}
		//cout<<iter<<"\n";
	}

	// int arr[2];
	// int r,s;
	// // if(token[0]=='P'){
	// // 	cout<<"Danger\n";
	// // 	token = strtok(NULL, " ");
	// // 	r = (atoi(token));
	// // 	token = strtok(NULL, " ");
	// // 	s = (atoi(token));
	// // 	convtodavid(r,s,arr);
	// // 	int x = arr[0];
	// // 	int y = arr[1];
	// // 	if(p!=1){
	// // 		board[x+5][y+5]=0;
	// // 		// opp_rings_x[opp_ringsonboard] = x;
	// // 		// opp_rings_y[opp_ringsonboard] = y;
	// // 		opp_ringsonboard++;

	// // 	}
	// // 	else{
	// // 		board[x+5][y+5]=0;
	// // 		// my_rings_x[my_ringsonboard] = x;
	// // 		// my_rings_y[my_ringsonboard] = y;
	// // 		my_ringsonboard++;
	// // 	}
	// // }
	// if(token[0]=='S'){
	// 	token = strtok(NULL, " ");
	// 	r = (atoi(token));
	// 	token = strtok(NULL, " ");
	// 	s = (atoi(token));
	// 	convtodavid(r,s,arr);
	// 	int x2 = arr[0];
	// 	int y2 = arr[1];

	// 	token = strtok(NULL, " "); //this is M

	// 	token = strtok(NULL, " ");
	// 	r = (atoi(token));
	// 	token = strtok(NULL, " ");
	// 	s = (atoi(token));
	// 	convtodavid(r,s,arr);
	// 	int x1 = arr[0];
	// 	int y1 = arr[1];

	// 	int prev;
	// 	if(p!=1){
	// 		board[x1+5][y1+5]=0;
	// 		// for(int i=0;i<opp_ringsonboard;i++){
	// 		// 	if(opp_rings_x[i]==x1 && opp_rings_y[i]==y1){
	// 		// 		prev = i;
	// 		// 		break;
	// 		// 	}
	// 		// }
	// 	}
	// 	else{
	// 		board[x1+5][y1+5]=0;
	// 		// for(int i=0;i<my_ringsonboard;i++){
	// 		// 	if(my_rings_x[i]==x1 && my_rings_y[i]==y1){
	// 		// 		prev = i;
	// 		// 		break;
	// 		// 	}
	// 		// }
	// 	}
	// 	int a = x1;
	// 	int b = y1;
	// 	if(x1==x2){
	// 		if(y2>y1){
	// 			b++;
	// 			while(board[a+5][b+5]==0 && b<y2){
	// 				b++;
	// 			}
	// 			if(b==y2){
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 			else{
	// 				while(b<y2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 					b++;
	// 				}
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 		}
	// 		else if(y2 < y1){
	// 			b--;
	// 			while(board[a+5][b+5]==0 && b>y2){
	// 				b--;
	// 			}
	// 			if(b==y2){
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 			else{
	// 				while(b>y2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 					b--;
	// 				}
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	else if(y1==y2){
	// 		if(x2>x1){
	// 			a++;
	// 			while(board[a+5][b+5]==0 && a<x2){
	// 				a++;
	// 			}
	// 			if(a==x2){
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 			else{
	// 				while(a<x2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 					a++;
	// 				}
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 		}
	// 		else if(x2 < x1){
	// 			a--;
	// 			while(board[a+5][b+5]==0 && a>x2){
	// 				a--;
	// 			}
	// 			if(a==x2){
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 			else{
	// 				while(a>x2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 					a--;
	// 				}
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	else{
	// 		if(y2>y1){
	// 			b++;
	// 			a++;
	// 			while(board[a+5][b+5]==0 && b<y2){
	// 				b++;
	// 				a++;
	// 			}
	// 			if(b==y2){
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 			else{
	// 				while(b<y2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 					b++;
	// 					a++;
	// 				}
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 		}
	// 		else if(y2 < y1){
	// 			b--;
	// 			a--;
	// 			while(board[a+5][b+5]==0 && b>y2){
	// 				b--;
	// 				a--;
	// 			}
	// 			if(b==y2){
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 			else{
	// 				while(b>y2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 					b--;
	// 					a--;
	// 				}
	// 				if(p!=1){
	// 					board[x2+5][y2+5]=4;
	// 					// opp_rings_x[prev] = x2;
	// 					// opp_rings_y[prev] = y2;
	// 					//opp_ringsonboard++;

	// 				}
	// 				else{
	// 					board[x2+5][y2+5]=3;
	// 					// my_rings_x[prev] = x2;
	// 					// my_rings_y[prev] = y2;
	// 					//my_ringsonboard++;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	token = strtok(NULL, " ");
	// 	while(token != NULL){
	// 		// cout<<token<<"\n";
	// 		token = strtok(NULL, " ");
	// 		r = (atoi(token));
	// 		token = strtok(NULL, " ");
	// 		s = (atoi(token));
	// 		convtodavid(r,s,arr);
	// 		int a1 = arr[0];
	// 		int b1 = arr[1];
	// 		// cout<<a1<<" "<<b1<<"\n";

	// 		token = strtok(NULL, " "); //this is RE

	// 		token = strtok(NULL, " ");
	// 		r = (atoi(token));
	// 		token = strtok(NULL, " ");
	// 		s = (atoi(token));
	// 		convtodavid(r,s,arr);
	// 		int a2 = arr[0];
	// 		int b2 = arr[1];

	// 		token = strtok(NULL, " "); //this is X

	// 		// cout<<a2<<" "<<b2<<"\n";
	// 		token = strtok(NULL, " ");
	// 		r = (atoi(token));
	// 		token = strtok(NULL, " ");
	// 		s = (atoi(token));
	// 		convtodavid(r,s,arr);
	// 		int a3 = arr[0];
	// 		int b3 = arr[1];
	// 		// cout<<a3<<" "<<b3<<"\n";
	// 		int p1 = a1;
	// 		int q1 = b1;
	// 		if(a1==a2){
	// 			if(b2>b1){
	// 				while(q1!=b2){
	// 					board[p1+5][q1+5] = p;
	// 					q1++;
	// 				}
	// 			}
	// 			else{
	// 				while(q1!=b2){
	// 					board[p1+5][q1+5] = p;
	// 					q1--;
	// 				}					
	// 			}
	// 			board[a2+5][b2+5]=p;
	// 		}
	// 		else if(b1==b2){
	// 			if(a2>a1){
	// 				while(p1!=a2){
	// 					board[p1+5][q1+5] = p;
	// 					p1++;
	// 				}
	// 			}
	// 			else{
	// 				while(p1!=a2){
	// 					board[p1+5][q1+5] = p;
	// 					p1--;
	// 				}					
	// 			}
	// 			board[a2+5][b2+5]=p;
	// 		}
	// 		else{
	// 			if(b2>b1){
	// 				while(q1!=b2){
	// 					board[p1+5][q1+5] = p;
	// 					q1++;
	// 					p1++;
	// 				}
	// 			}
	// 			else{
	// 				while(q1!=b2){
	// 					board[p1+5][q1+5] = p;
	// 					q1--;
	// 					p1--;
	// 				}					
	// 			}
	// 			board[a2+5][b2+5]=p;
	// 		}

	// 		board[a3+5][b3+5] = p+2;
	// 		int prev2=0;
	// 		if(p!=1){
	// 			//board[x1+5][y1+5]=2;
	// 			// opp_rings_x[opp_ringsonboard] = a3;
	// 			// opp_rings_y[opp_ringsonboard] = b3;

	// 			opp_ringsonboard++;
	// 		}
	// 		else{
	// 			//board[x1+5][y1+5]=1;
	// 			// my_rings_x[my_ringsonboard] = a3;
	// 			// my_rings_y[my_ringsonboard] = b3;

	// 			my_ringsonboard++;
	// 		}
	// 		token = strtok(NULL, " ");
	// 	}				
	// }
	// else if(token[0] == 'R' && token[1]=='S')
	// {
	// 	r = (atoi(token));
	// 	token = strtok(NULL, " ");
	// 	s = (atoi(token));
	// 	convtodavid(r,s,arr);
	// 	int a1 = arr[0];
	// 	int b1 = arr[1];

	// 	token = strtok(NULL, " "); //this is M

	// 	token = strtok(NULL, " ");
	// 	r = (atoi(token));
	// 	token = strtok(NULL, " ");
	// 	s = (atoi(token));
	// 	convtodavid(r,s,arr);
	// 	int a2 = arr[0];
	// 	int b2 = arr[1];

	// 	token = strtok(NULL, " "); //this is M

	// 	token = strtok(NULL, " ");
	// 	r = (atoi(token));
	// 	token = strtok(NULL, " ");
	// 	s = (atoi(token));
	// 	convtodavid(r,s,arr);
	// 	int a3 = arr[0];
	// 	int b3 = arr[1];

	// 	int p1 = a1;
	// 	int q1 = b1;
	// 	if(a1==a2){
	// 		if(b2>b1){
	// 			while(q1!=b2){
	// 				board[p1+5][q1+5] = p;
	// 				q1++;
	// 			}
	// 		}
	// 		else{
	// 			while(q1!=b2){
	// 				board[p1+5][q1+5] = p;
	// 				q1--;
	// 			}					
	// 		}
	// 		board[a2+5][b2+5]=p;
	// 	}
	// 	else if(b1==b2){
	// 		if(a2>a1){
	// 			while(p1!=a2){
	// 				board[p1+5][q1+5] = p;
	// 				p1++;
	// 			}
	// 		}
	// 		else{
	// 			while(p1!=a2){
	// 				board[p1+5][q1+5] = p;
	// 				p1--;
	// 			}					
	// 		}
	// 		board[a2+5][b2+5]=p;
	// 	}
	// 	else{
	// 		if(b2>b1){
	// 			while(q1!=b2){
	// 				board[p1+5][q1+5] = p;
	// 				q1++;
	// 				p1++;
	// 			}
	// 		}
	// 		else{
	// 			while(q1!=b2){
	// 				board[p1+5][q1+5] = p;
	// 				q1--;
	// 				p1--;
	// 			}					
	// 		}
	// 		board[a2+5][b2+5]=p;
	// 	}
	// 	board[a3+5][b3+5] = p+2;
	// 	int prev2=0;
	// 	if(p!=1){
	// 		//board[x1+5][y1+5]=2;
	// 		// opp_rings_x[opp_ringsonboard] = a3;
	// 		// opp_rings_y[opp_ringsonboard] = b3;

	// 		opp_ringsonboard++;
	// 	}
	// 	else{
	// 		//board[x1+5][y1+5]=1;
	// 		// my_rings_x[my_ringsonboard] = a3;
	// 		// my_rings_y[my_ringsonboard] = b3;

	// 		my_ringsonboard++;
	// 	}

	// 	token = strtok(NULL, " ");

	// 	if(token[0]=='S'){
	// 		token = strtok(NULL, " ");
	// 		r = (atoi(token));
	// 		token = strtok(NULL, " ");
	// 		s = (atoi(token));
	// 		convtodavid(r,s,arr);
	// 		int x2 = arr[0];
	// 		int y2 = arr[1];

	// 		token = strtok(NULL, " "); //this is M

	// 		token = strtok(NULL, " ");
	// 		r = (atoi(token));
	// 		token = strtok(NULL, " ");
	// 		s = (atoi(token));
	// 		convtodavid(r,s,arr);
	// 		int x1 = arr[0];
	// 		int y1 = arr[1];

	// 		int prev;
	// 		if(p!=1){
	// 			board[x1+5][y1+5]=0;
	// 			// for(int i=0;i<opp_ringsonboard;i++){
	// 			// 	if(opp_rings_x[i]==x1 && opp_rings_y[i]==y1){
	// 			// 		prev = i;
	// 			// 		break;
	// 			// 	}
	// 			// }
	// 		}
	// 		else{
	// 			board[x1+5][y1+5]=0;
	// 			// for(int i=0;i<my_ringsonboard;i++){
	// 			// 	if(my_rings_x[i]==x1 && my_rings_y[i]==y1){
	// 			// 		prev = i;
	// 			// 		break;
	// 			// 	}
	// 			// }
	// 		}
	// 		int a = x1;
	// 		int b = y1;
	// 		if(x1==x2){
	// 			if(y2>y1){
	// 				b++;
	// 				while(board[a+5][b+5]==0 && b<y2){
	// 					b++;
	// 				}
	// 				if(b==y2){
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 				else{
	// 					while(b<y2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 						b++;
	// 					}
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 			}
	// 			else if(y2 < y1){
	// 				b--;
	// 				while(board[a+5][b+5]==0 && b>y2){
	// 					b--;
	// 				}
	// 				if(b==y2){
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 				else{
	// 					while(b>y2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 						b--;
	// 					}
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 			}
	// 		}
	// 		else if(y1==y2){
	// 			if(x2>x1){
	// 				a++;
	// 				while(board[a+5][b+5]==0 && a<x2){
	// 					a++;
	// 				}
	// 				if(a==x2){
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 				else{
	// 					while(a<x2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 						a++;
	// 					}
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 			}
	// 			else if(x2 < x1){
	// 				a--;
	// 				while(board[a+5][b+5]==0 && a>x2){
	// 					a--;
	// 				}
	// 				if(a==x2){
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 				else{
	// 					while(a>x2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 						a--;
	// 					}
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 			}
	// 		}
	// 		else{
	// 			if(y2>y1){
	// 				b++;
	// 				a++;
	// 				while(board[a+5][b+5]==0 && b<y2){
	// 					b++;
	// 					a++;
	// 				}
	// 				if(b==y2){
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 				else{
	// 					while(b<y2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 						b++;
	// 						a++;
	// 					}
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 			}
	// 			else if(y2 < y1){
	// 				b--;
	// 				a--;
	// 				while(board[a+5][b+5]==0 && b>y2){
	// 					b--;
	// 					a--;
	// 				}
	// 				if(b==y2){
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 				else{
	// 					while(b>y2){
	// 					if(board[a+5][b+5] == 0){
	// 						board[a+5][b+5] = 0;
	// 					}
	// 					else{
	// 						board[a+5][b+5] = (board[a+5][b+5] % 2) + 1;
	// 					}
	// 						b--;
	// 						a--;
	// 					}
	// 					if(p!=1){
	// 						board[x2+5][y2+5]=4;
	// 						// opp_rings_x[prev] = x2;
	// 						// opp_rings_y[prev] = y2;
	// 						//opp_ringsonboard++;

	// 					}
	// 					else{
	// 						board[x2+5][y2+5]=3;
	// 						// my_rings_x[prev] = x2;
	// 						// my_rings_y[prev] = y2;
	// 						//my_ringsonboard++;
	// 					}
	// 				}
	// 			}
	// 		}
	// 		token = strtok(NULL, " ");
	// 		while(token != NULL){
	// 			// cout<<token<<"\n";
	// 			token = strtok(NULL, " ");
	// 			r = (atoi(token));
	// 			token = strtok(NULL, " ");
	// 			s = (atoi(token));
	// 			convtodavid(r,s,arr);
	// 			int a1 = arr[0];
	// 			int b1 = arr[1];
	// 			// cout<<a1<<" "<<b1<<"\n";

	// 			token = strtok(NULL, " "); //this is RE

	// 			token = strtok(NULL, " ");
	// 			r = (atoi(token));
	// 			token = strtok(NULL, " ");
	// 			s = (atoi(token));
	// 			convtodavid(r,s,arr);
	// 			int a2 = arr[0];
	// 			int b2 = arr[1];

	// 			token = strtok(NULL, " "); //this is X

	// 			// cout<<a2<<" "<<b2<<"\n";
	// 			token = strtok(NULL, " ");
	// 			r = (atoi(token));
	// 			token = strtok(NULL, " ");
	// 			s = (atoi(token));
	// 			convtodavid(r,s,arr);
	// 			int a3 = arr[0];
	// 			int b3 = arr[1];
	// 			// cout<<a3<<" "<<b3<<"\n";
	// 			int p1 = a1;
	// 			int q1 = b1;
	// 			if(a1==a2){
	// 				if(b2>b1){
	// 					while(q1!=b2){
	// 						board[p1+5][q1+5] = p;
	// 						q1++;
	// 					}
	// 				}
	// 				else{
	// 					while(q1!=b2){
	// 						board[p1+5][q1+5] = p;
	// 						q1--;
	// 					}					
	// 				}
	// 				board[a2+5][b2+5]=p;
	// 			}
	// 			else if(b1==b2){
	// 				if(a2>a1){
	// 					while(p1!=a2){
	// 						board[p1+5][q1+5] = p;
	// 						p1++;
	// 					}
	// 				}
	// 				else{
	// 					while(p1!=a2){
	// 						board[p1+5][q1+5] = p;
	// 						p1--;
	// 					}					
	// 				}
	// 				board[a2+5][b2+5]=p;
	// 			}
	// 			else{
	// 				if(b2>b1){
	// 					while(q1!=b2){
	// 						board[p1+5][q1+5] = p;
	// 						q1++;
	// 						p1++;
	// 					}
	// 				}
	// 				else{
	// 					while(q1!=b2){
	// 						board[p1+5][q1+5] = p;
	// 						q1--;
	// 						p1--;
	// 					}					
	// 				}
	// 				board[a2+5][b2+5]=p;
	// 			}

	// 			board[a3+5][b3+5] = p+2;
	// 			int prev2=0;
	// 			if(p!=1){
	// 				//board[x1+5][y1+5]=2;
	// 				// opp_rings_x[opp_ringsonboard] = a3;
	// 				// opp_rings_y[opp_ringsonboard] = b3;

	// 				opp_ringsonboard++;
	// 			}
	// 			else{
	// 				//board[x1+5][y1+5]=1;
	// 				// my_rings_x[my_ringsonboard] = a3;
	// 				// my_rings_y[my_ringsonboard] = b3;

	// 				my_ringsonboard++;
	// 			}
	// 			token = strtok(NULL, " ");
	// 		}				
	// 	}
	// }
}


vector<int> Boardclass::find_row(int p){

	int x1,y1;
	int count = 0;
	vector<int> vec;
	for(int i=-5;i<=5;i++){
		for(int j=-5;j<=5;j++){
			if(board[i+5][j+5]==p){
				if(count==0){
					x1 = i;
					y1 = j;
					count++;
				}
				else{
					count++;
				}
			}
			else{
				if(count==5){
					//int a[4] = {x1,y1,x1,j-1};
					vec.push_back(x1);
					vec.push_back(y1);
					vec.push_back(x1);
					vec.push_back(j-1);
					count=0;
				}
				else if(count > 5){
					// int a[4] = {x1,y1,x1,y1+4};
					vec.push_back(x1);
					vec.push_back(y1);
					vec.push_back(x1);
					vec.push_back(y1 + 4);
					// int b[4] = {x1,j-5,x1,j-1};
					vec.push_back(x1);
					vec.push_back(j-5);
					vec.push_back(x1);
					vec.push_back(j-1);
					count = 0;
				}
				count = 0;
			}
		}
		count = 0;
	}
	count = 0;
	for(int j=-5;j<=5;j++){
		for(int i=-5;i<=5;i++){
			if(board[i+5][j+5]==p){
				if(count==0){
					x1 = i;
					y1 = j;
					count++;
				}
				else{
					count++;
				}
			}
			else{
				if(count==5){
					// int a[4] = {x1,y1,i-1,y1};
					vec.push_back(x1);
					vec.push_back(y1);
					vec.push_back(i-1);
					vec.push_back(y1);
					count=0;
				}
				else if(count > 5){
					// int a[4] = {x1,y1,x1+4,y1};
					vec.push_back(x1);
					vec.push_back(y1);
					vec.push_back(x1+4);
					vec.push_back(y1);
					// int b[4] = {i-5,y1,i-1,y1};
					vec.push_back(i-5);
					vec.push_back(y1);
					vec.push_back(i-1);
					vec.push_back(y1);
					count = 0;
				}
				count = 0;
			}
		}
		count = 0;
	}
	count=0;
	int i = -5;
	int z,j;
	for(int z=-5;z<=5;z++){
		j = z;
		while(i<=5 && j<=5){
			if(board[i+5][j+5]==p){
				if(count==0){
					x1 = i;
					y1 = j;
					count++;
				}
				else{
					count++;
				}
			}
			else{
				if(count==5){
					// int a[4] ={x1,y1,i-1,j-1};
					vec.push_back(x1);
					vec.push_back(y1);
					vec.push_back(i-1);
					vec.push_back(j-1);
					count=0;
				}
				else if(count > 5){
					// int a[4] = {x1,y1,x1+4,y1+4};
					vec.push_back(x1);
					vec.push_back(y1);
					vec.push_back(x1+4);
					vec.push_back(y1+4);
					// int b[4] = {i-5,j-5,i-1,j-1};
					vec.push_back(i-5);
					vec.push_back(j-5);
					vec.push_back(i-1);
					vec.push_back(j-1);
					count = 0;
				}
				count = 0;
			}
			i++;
			j++;			
		}
		i = -5;
		count = 0;
	}
	count = 0;
	j = -5;
	for(int z=-4;z<=5;z++){
		i = z;
		while(i<=5 && j<=5){
			if(board[i+5][j+5]==p){
				if(count==0){
					x1 = i;
					y1 = j;
					count++;
				}
				else{
					count++;
				}
			}
			else{
				if(count==5){
					// int a[4] = {x1,y1,i-1,j-1};
					vec.push_back(x1);
					vec.push_back(y1);
					vec.push_back(i-1);
					vec.push_back(j-1);
					count=0;
				}
				else if(count > 5){
					// int a[4] = {x1,y1,x1+4,y1+4};
					vec.push_back(x1);
					vec.push_back(y1);
					vec.push_back(x1+4);
					vec.push_back(y1+4);
					// int b[4] = {i-5,j-5,i-1,j-1};
					vec.push_back(i-5);
					vec.push_back(j-5);
					vec.push_back(i-1);
					vec.push_back(j-1);
					count = 0;
				}
				count = 0;
			}
			i++;
			j++;			
		}
		j = -5;
		count = 0;
	}
	return vec;
}
