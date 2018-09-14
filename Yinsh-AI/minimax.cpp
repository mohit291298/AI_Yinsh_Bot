#include "minimax.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <list>
#include "Boardclass.h"
#include "Node.h"

using namespace std;

#define matrix_size 11;

// int depth  = 0;
Boardclass givenState;
// vector<int> heuristicEvaluation;
vector<state> nodeList;

//returns the heuristic function evaluation of all the nodes at depth d
vector<int> heuristicEval ( Node n, int depth, int max_depth ) {
    givenState = n.state;
    vector<int> answer;
    if (depth > max_depth) {return;}
    if (depth == max_depth) {
        answer.push_back(calculateHeuristic(n));
        // heuristicEvaluation.push_back(calculateHeuristic(n));
        return ans;
    }

    if ( depth < max_depth && nodeList.size()!= 0 ){
        for ( int i = 0; i < state.children.size(); i++ ){
            nodeList.push_back(children.at(i));
        }
        for ( int i = 0; i < state.children.size(); i++ ){
            vector<int> nodeEval = heuristicEval (nodeList.at(i) , depth + 1, max_depth);
            for (int j = 0; j < nodeEval.size(); j++ ){
                answer.push_back(nodeEval.at(j));
            }
        }
    }
    return ans;

}

// //minimax implementation on the tree
// int minimax ( Node n, int p , int depth ) {
//     vector<int> heuristicEvaluation = new vector<int>;
//     heuristicEvaluation = heuristicEval (n, 0, depth);
//     if ( p.myPlayer() ){

//     }
// }
