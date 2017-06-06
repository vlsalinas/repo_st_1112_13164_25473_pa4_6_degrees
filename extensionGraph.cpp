/*
 * Vincent Salinas
 * 6-4-2017
 * CSE 100
 * Project Assignment 4, Graphs
 */

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

  // Open file stream and get file. 
  ifstream infile(in_filename);

  // Read entire file in.
  while (infile) {
    string s;

    // get the next line
    if (!getline( infile, s )) break;

    istringstream ss( s );
    vector <string> record;

    while (ss) {
      string next;

      // Get next piece of data before tab
      if (!getline( ss, next, ' ' )) break;

      record.push_back( next );
    }

    if (record.size() != 2) {
      continue;
    }

    int data1 = stoi(record[0]);
    int data2 = stoi(record[1]);

    // search for name in hashmap of actors
    auto search = list1.find(data1);

    // if not found, create node and add to graph
    if( search == list1.end() ) {
      extNode *newNode = new extNode(data1);
      list1.insert(make_pair((int)data1, (extNode*)newNode));
      search = list1.find(data1);
    } 

    (*search).second->acquaintances.push_back(data2);
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;
}

/**
 * Param: 
 *              start = source actor
 *              end = destination actor	
 * Return:
 *              vector<int> = vector of mutual friends
 * Description:
 *              Determine how many friends from start actor to end actor using
 *              Depth First Search 
 */
int extensionGraph::searching( string start, string end ) {

  int st = stoi(start);
  int en = stoi(end);

  // create stack for DFS
  stack<extNode*> stack1;

  unordered_map<int, extNode*>::iterator iter2 = list1.find(st);

  // Friend not found
  if( iter2 == list1.end() ) 
    return 0;

  // push to stack (start) 
  stack1.push((*iter2).second);

  while( !stack1.empty() ) {
    extNode* next = stack1.top();
    stack1.pop();
    next->soFar = true;

    // soFar if it is equal to end friend
    f1(next, en);
    
    //visit next's mutual friends
    vector<int>::iterator vec1 = next->acquaintances.begin();
    for( ; vec1 != next->acquaintances.end(); vec1++ ) {
      extNode* adjacent = list1.at(*vec1);

      // so far end reached
      f2(adjacent, next, en);
      f3(adjacent, next, stack1);
      }				
  }

  unordered_map<int, extNode*>::iterator iter1 = list1.begin();
  f4(iter1);
  
  //return 0 if not found
  return 0;
}

int extensionGraph::f1(extNode*& next, int& en)
{
  if( next->item == en ) {
    int temp1 = next->length + 1;
    unordered_map<int, extNode*>::iterator iter1 = list1.begin();
    for( ; iter1 != list1.end(); iter1++ ) {
      (*iter1).second->length = 0;
      (*iter1).second->soFar = false;
    }
    return temp1;
  }

}

int extensionGraph::f2(extNode*& adjacent, extNode*& next, int& en )
{

  if( adjacent->item == en ) {
    int temp1 = next->length + 1;
    //reset fields
    unordered_map<int, extNode*>::iterator iter1 = list1.begin();
    for( ; iter1 != list1.end(); iter1++ ) {
      (*iter1).second->length = 0;
      (*iter1).second->soFar = false;
    }
    return temp1;
  }

}

void extensionGraph::f3(extNode*& adjacent, extNode*& next, stack<extNode*>& stack1 )
{
  if( !adjacent->soFar ) {
    adjacent->length = next->length + 1;
    stack1.push(adjacent);
  }

}

void extensionGraph::f4(unordered_map<int, extNode*>::iterator& iter1)
{
  for( ; iter1 != list1.end(); iter1++ ) {
    (*iter1).second->length = 0;
    (*iter1).second->soFar = false;
  }
}

// Destructor
extensionGraph::~extensionGraph() {
  unordered_map<int, extNode*>::iterator st = list1.begin();

  //delete nodes in actor
  for( ; st != list1.end(); st++ ) {
    delete st->second;
  }

}
