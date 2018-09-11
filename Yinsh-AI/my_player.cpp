#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include "Boardclass.h"
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