#ifndef _Score_h
#define _Score_h

#include <string>
#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <cstring>

using namespace std;

// public :
    int markerHeuristic ( Node n ) ;
    int ringHeuristic ( Node n ) ;
    int changeInScore ( Node n ) ;
    int futureScore ( Node n ) ;
    int changeInFutureScore ( Node n ) ;
    int calculateHeuristic ( Node n ) ;

#endif