
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
  extensionGraph(void) {}

	~extensionGraph(void);

	unordered_map<int, extNode*> friendsList;

	/**
	 * Param: in_filename - input filename
	 * Return: boolean saying whether load was successful or not 
	 * Load to the graph
	 */
	bool loadFromFile( const char* in_filename );

	/**
   * Param: start - start friend
   *				end - end friend
   * Return: vector<int> - consists of total, before, and after mutual friends
   * counts
   * Takes in start and end and finds the mutual friends
   */
	int finding( string start, string end );

	

};


#endif // EXTENSIONGRAPH_H

