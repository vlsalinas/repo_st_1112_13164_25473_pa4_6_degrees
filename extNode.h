/*
 * Vincent Salinas
 * 5-31-2017
 * CSE 100
 * Project Assignment 4, Graphs
 */

#ifndef EXTNODE_H
#define EXTNODE_H

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

class extNode {

  public:
    extNode(int v); // Constructor
    vector<int> acquaintances;
    int item; // key
    int length; // height
    bool soFar; // boolean indicating status so far

};

#endif
