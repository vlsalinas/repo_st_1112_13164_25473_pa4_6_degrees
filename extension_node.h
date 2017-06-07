/*
 * Vincent Salinas
 * 6-5-2017
 * CSE 100
 * Project Assingment 4, Graphs
 *
 * Description:
 *      Contains memmber and function declarations of
 *      extension_node class. Used in the process of
 *      making an extension_graph graph for the extension.cpp
 *      program.
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

class extension_node {

  public:

    extension_node(int v); // Constructor
    int item; // key
    int heet; // heet
    bool soFar; // boolean value indicating status so far
    vector<int> list1; // friends vector

};

#endif
