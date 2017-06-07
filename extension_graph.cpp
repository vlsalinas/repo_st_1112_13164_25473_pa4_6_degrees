/*
 * Vincent Salinas
 * 6-5-2017
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
#include "extension_graph.h"
#include "extension_node.h"

using namespace std;

// Destructor
extension_graph::~extension_graph() {
  unordered_map<int, extension_node*>::iterator st = list1.begin();

  //delete nodes in actor
  for( ; st != list1.end(); st++ ) {
    delete st->second;
  }
}

/**
 * Parameters: 
 *              in_filename = file to read in
 * Return: 
 *              boolean value indicating successful load or not 
 * Description:
 *              populate graph and return true if successful load, else false.
 */
bool extension_graph::loadFromFile( const char* in_filename ) {

  // open file stream for file to be read.
  ifstream fin(in_filename);

  // Read entire file.
  while (fin) {
    string s;

    if (!getline( fin, s )) break;

    istringstream ss( s );
    vector <string> vec1;

    while (ss) {
      string get_next;

      // record data before next tab
      if (!getline( ss, get_next, ' ' )) break;

      vec1.push_back( get_next );
    }

    if (vec1.size() != 2) {
      continue;
    }

    int beginning = stoi(vec1[0]);
    int end_dest = stoi(vec1[1]);

    // so far for name in unodered_map of friends
    auto locate = list1.find(beginning);

    // if not found, creat node and insert into graph
    if( locate == list1.end() ) {
      extension_node *newNode = new extension_node(beginning);
      list1.insert(make_pair((int)beginning, 
            (extension_node*)newNode));
      locate = list1.find(beginning);
    } 

    (*locate).second->list1.push_back(end_dest);
  }

  if (!fin.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  fin.close();
  return true;
}

/**
 * Param: 
 *              source = start search from this 
 *		dest = find connection to this
 * Return: 
 *              vector<int> = total number of shared friends
 * Description:
 *              Using depth first search, determines number of
 *              friends it takes to get from source to dest. 
 */
int extension_graph::search( string source, string dest ) {
  
  // save source and dest to compute
  int from_source = stoi(source);
  int end_dest = stoi(dest);

  stack<extension_node*> link;
  unordered_map<int, extension_node*>::iterator iter1 = list1.find(from_source);

  // Check if friend exists
  if( iter1 == list1.end() ) 
    return 0;

  // push beginning to stack
  link.push((*iter1).second);

  while( !link.empty() ) {
    extension_node* get_next = link.top();
    link.pop();
    get_next->soFar = true;

    if( get_next->item == end_dest ) {
      int len = get_next->heet + 1;
      unordered_map<int, extension_node*>::iterator iter2 = list1.begin();
      f1(iter2);
     // for( ; iter2 != list1.end(); iter2++ ) {
     //   (*iter2).second->heet = 0;
     //   (*iter2).second->soFar = false;
     // }
      return len;
    }

    // Touch on local nodes (friends)
    vector<int>::iterator iter5 = get_next->list1.begin();
    for( ; iter5 != get_next->list1.end(); iter5++ ) {
      extension_node* aNode1 = list1.at(*iter5);

      // end reached
      if( aNode1->item == end_dest ) {
        int len = get_next->heet + 1;
        unordered_map<int, extension_node*>::iterator iter4 = list1.begin();
        f2(iter4);
        //for( ; iter4 != list1.end(); iter4++ ) {
        //  (*iter4).second->heet = 0;
        //  (*iter4).second->soFar = false;
        //}
        return len;
      }

      if( !aNode1->soFar ) {
        aNode1->heet = get_next->heet + 1;
        link.push(aNode1);
      }
    }				
  }

  unordered_map<int, extension_node*>::iterator iter3 = list1.begin();
  for( ; iter3 != list1.end(); iter3++ ) {
    (*iter3).second->heet = 0;
    (*iter3).second->soFar = false;
  }

  return 0;
}

void extension_graph::f1(unordered_map<int, extension_node*>::iterator& iter2)
{
      for( ; iter2 != list1.end(); iter2++ ) {
        (*iter2).second->heet = 0;
        (*iter2).second->soFar = false;
      }

}

void extension_graph::f2(unordered_map<int, extension_node*>::iterator& iter4)
{
        for( ; iter4 != list1.end(); iter4++ ) {
          (*iter4).second->heet = 0;
          (*iter4).second->soFar = false;
        }

}
