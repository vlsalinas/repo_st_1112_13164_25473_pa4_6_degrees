/*
 * Vincent Salinas
 * 5-31-2017
 * CSE 100
 * Project Assignment 4, Graphs
 */

#ifndef EXTENSIONGRAPH_H
#define EXTENSIONGRAPH_H

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include "extNode.h"

using namespace std;

class extNode;

class extensionGraph {

  public:
    // Helper functions
    int f1(extNode*& next, int& en);
    int f2(extNode*& adjacent, extNode*& next, int& en);
    void f3(extNode*& adjacent, extNode*& next, stack<extNode*>& stack1 );
    void f4(unordered_map<int, extNode*>::iterator& iter1);
    extensionGraph(void) {} // Constructor
    ~extensionGraph(void); // Destructor
    unordered_map<int, extNode*> list1;


    // Param: in_filename = file to be read 
    // Return: boolean indicating successful read or not 
    // Description: return true if successful load, else false. Also populates graph.
    bool loadFromFile( const char* in_filename );

    // Param: (1) start = start actor, (2) end = end actor
    // Return: int = # of mutual friends* 
    // Description: searches mutual friends between start and end actors
    int searching( string start, string end );
};


#endif // EXTENSIONGRAPH_H

