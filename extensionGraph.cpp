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

    int data1 = stoi(record[0]);
    int data2 = stoi(record[1]);

    // check for name in hashmap of actors
    auto search = friendsList.find(data1);

    // if not, then create node and call addToGraph
    if( search == friendsList.end() ) {
      extNode *newNode = new extNode(data1);
      friendsList.insert(make_pair((int)data1, (extNode*)newNode));
      search = friendsList.find(data1);
    } 

    (*search).second->listOfFriends.push_back(data2);
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
int extensionGraph::search( string start, string end ) {

  int st = stoi(start);
  int en = stoi(end);

  //stack used in DFS
  stack<extNode*> stack1;

  unordered_map<int, extNode*>::iterator iter2 = friendsList.find(st);

  //if the friend is not in the list
  if( iter2 == friendsList.end() ) 
    return 0;

  //push the start to the stack
  stack1.push((*iter2).second);

  while( !stack1.empty() ) {
    extNode* next = stack1.top();
    stack1.pop();
    next->check = true;

    //check if it is equal to end friend
    f1(next, en);
    //if( next->key == en ) {
    //  int temp1 = next->height + 1;
    //  unordered_map<int, extNode*>::iterator iter1 = friendsList.begin();
    //  for( ; iter1 != friendsList.end(); iter1++ ) {
    //    (*iter1).second->height = 0;
    //    (*iter1).second->check = false;
    //  }
    //  return temp1;
    //}

    //visit next's mutual friends
    vector<int>::iterator vec1 = next->listOfFriends.begin();
    for( ; vec1 != next->listOfFriends.end(); vec1++ ) {
      extNode* adjacent = friendsList.at(*vec1);

      //check if it has reached the end
      f2(adjacent, next, en);
      //if( adjacent->key == en ) {
      //  int temp1 = next->height + 1;
      //  //reset fields
      //  unordered_map<int, extNode*>::iterator iter1 = friendsList.begin();
      //  for( ; iter1 != friendsList.end(); iter1++ ) {
      //    (*iter1).second->height = 0;
      //    (*iter1).second->check = false;
      //  }
      //  return temp1;
      //}
      f3(adjacent, next, stack1);
      //if( !adjacent->check ) {
      //  adjacent->height = next->height + 1;
      //  stack1.push(adjacent);
      //}
    }				
  }

  //iter1
  unordered_map<int, extNode*>::iterator iter1 = friendsList.begin();
  for( ; iter1 != friendsList.end(); iter1++ ) {
    (*iter1).second->height = 0;
    (*iter1).second->check = false;
  }

  //return 0 if no found stack1ions
  return 0;
}

int extensionGraph::f1(extNode*& next, int& en)
{
  if( next->key == en ) {
    int temp1 = next->height + 1;
    unordered_map<int, extNode*>::iterator iter1 = friendsList.begin();
    for( ; iter1 != friendsList.end(); iter1++ ) {
      (*iter1).second->height = 0;
      (*iter1).second->check = false;
    }
    return temp1;
  }

}

int extensionGraph::f2(extNode*& adjacent, extNode*& next, int& en )
{

  if( adjacent->key == en ) {
    int temp1 = next->height + 1;
    //reset fields
    unordered_map<int, extNode*>::iterator iter1 = friendsList.begin();
    for( ; iter1 != friendsList.end(); iter1++ ) {
      (*iter1).second->height = 0;
      (*iter1).second->check = false;
    }
    return temp1;
  }

}

void extensionGraph::f3(extNode*& adjacent, extNode*& next, stack<extNode*>& stack1 )
{
  if( !adjacent->check ) {
    adjacent->height = next->height + 1;
    stack1.push(adjacent);
  }

}

/** 
 * Param: None.
 * Return: None.
 *	Deallocated memory associated with the graph.
 */

extensionGraph::~extensionGraph() {
  unordered_map<int, extNode*>::iterator st = friendsList.begin();

  //delete nodes in actor
  for( ; st != friendsList.end(); st++ ) {
    delete st->second;
  }

}
