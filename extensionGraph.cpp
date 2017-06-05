#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include "extensionGraph.h"
#include "extNode.h"

using namespace std;

/**
 * Param: in_filename - input filename
 * Return: boolean saying whether load was successful or not 
 * Load to the graph
 */
	bool extensionGraph::loadFromFile( const char* in_filename ) {

		// Initialize the file stream
    ifstream infile(in_filename);

    // keep reading lines until the end of file is reached
    while (infile) {
      string s;
    
      // get the next line
      if (!getline( infile, s )) break;

      istringstream ss( s );
      vector <string> record;

      while (ss) {
        string next;
    
        // get the next string before hitting a tab character
        if (!getline( ss, next, ' ' )) break;

        record.push_back( next );
      }
    
      if (record.size() != 2) {
        continue;
      }

      int startFriend = stoi(record[0]);
      int endFriend = stoi(record[1]);

      // check for name in hashmap of actors
      auto finding = friendsList.find(startFriend);

      // if not, then create node and call addToGraph
      if( finding == friendsList.end() ) {
				extNode *newNode = new extNode(startFriend);
				friendsList.insert(make_pair((int)startFriend, 
										(extNode*)newNode));
				finding = friendsList.find(startFriend);
			} 

			(*finding).second->listOfFriends.push_back(endFriend);
    }

    if (!infile.eof()) {
      cerr << "Failed to read " << in_filename << "!\n";
      return false;
    }

    infile.close();
    return true;
	}

/**
 * Param: start - start friend
 *				end - end friend
 * Return: vector<int> - consists of total, before, and after mutual friends
 * counts
 * Takes in start and end and finds how many mutual friends it takes to reach 
 * each other.  Uses DFS. 
 */
	int extensionGraph::finding( string start, string end ) {

		int starting = stoi(start);
		int ending = stoi(end);

		//stack used in DFS
		stack<extNode*> connect;

		unordered_map<int, extNode*>::iterator find = friendsList.find(starting);

		//if the friend is not in the list
		if( find == friendsList.end() ) 
			return 0;

		//push the start to the stack
		connect.push((*find).second);

		while( !connect.empty() ) {
			extNode* next = connect.top();
			connect.pop();
			next->check = true;
	
			//check if it is equal to end friend
			if( next->key == ending ) {
				int height = next->height + 1;
				unordered_map<int, extNode*>::iterator clear = friendsList.begin();
				for( ; clear != friendsList.end(); clear++ ) {
					(*clear).second->height = 0;
					(*clear).second->check = false;
				}
				return height;
			}

			//visit next's mutual friends
			vector<int>::iterator mutualFriends = next->listOfFriends.begin();
			for( ; mutualFriends != next->listOfFriends.end(); mutualFriends++ ) {
				extNode* neighbor = friendsList.at(*mutualFriends);

				//check if it has reached the end
				if( neighbor->key == ending ) {
					int height = next->height + 1;
					//reset fields
					unordered_map<int, extNode*>::iterator clear = friendsList.begin();
					for( ; clear != friendsList.end(); clear++ ) {
					(*clear).second->height = 0;
					(*clear).second->check = false;
					}
					return height;
				}

				if( !neighbor->check ) {
					neighbor->height = next->height + 1;
					connect.push(neighbor);
				}
			}				
		}

		//clear
		unordered_map<int, extNode*>::iterator clear = friendsList.begin();
		for( ; clear != friendsList.end(); clear++ ) {
			(*clear).second->height = 0;
			(*clear).second->check = false;
		}

		//return 0 if no found connections
		return 0;
	}

/** 
	* Param: None.
	* Return: None.
	*	Deallocated memory associated with the graph.
	*/

	extensionGraph::~extensionGraph() {
		unordered_map<int, extNode*>::iterator startN = friendsList.begin();

		//delete nodes in actor
		for( ; startN != friendsList.end(); startN++ ) {
			delete startN->second;
		}

	}
