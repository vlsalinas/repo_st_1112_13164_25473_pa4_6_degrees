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
#include "extension_node.h"

using namespace std;

class extension_node;

class extension_graph {

  public:
    extension_graph(void) {} // Constructor
    ~extension_graph(void); // Destructor

    // Helper functions.
    void f1(unordered_map<int, extension_node*>::iterator& iter2);
    void f2(unordered_map<int, extension_node*>::iterator& iter4);

    unordered_map<int, extension_node*> list1;

    /**
     * Param: 
     *          in_filename = file to read in
     * Return: 
     *          boolean indicating successful load or not 
     * Description:
     *          populate graph, and return success or fail of file read.
     */
    bool loadFromFile( const char* in_filename );

    /**
     * Param: 
     *          source = source actor to start from
     *		dest = destination actor to connect to
     * Return: 
     *          vector<int> = contains number of mutual friends
     * 
     * Description:
     *          Finds mutual friends between source and dest 
     */
    int search( string source, string dest );



};


#endif // EXTENSIONGRAPH_H

