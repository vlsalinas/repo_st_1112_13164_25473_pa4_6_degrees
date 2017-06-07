/*
 * Vincent Salinas
 * 6-6-2017
 * CSE 100
 * Project Assignment 4, Graphs
 *
 * Description:
 *      extension.cpp explores the problem of social media networks and 
 *      how it suggest mutual friends to two different people that aren't
 *      directly "friended". 
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string.h>
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include "extension_graph.h"
#include "extension_node.h"

using namespace std;

int main( int argc, char* argv[] ) {

  // Validation
  int number_of_arguments = argc;
  if( number_of_arguments != 4 ) {
    cerr << "Invalid number of arguments. Aborting." << endl;
    return -1;
  }

  //check validity of fourth param
  extension_graph * actor_graph = new extension_graph();
  bool load_file = actor_graph->loadFromFile( argv[1] );

  //check success of loading
  if( !load_file ) return -1;

  ifstream fin(argv[2]);
  ofstream fout(argv[3]);
  int temp1 = 0;

  //reading file
  while(fin) {

    string s;

    //get the next line
    if( !getline( fin, s )) {
      break;
    }

    istringstream ss( s );
    //will hold the start and end actors
    vector <string> vec1;

    //while there are strings to read in
    while( ss ) {

      string next;

      //get the next string before hitting tab
      if( !getline( ss, next, ' ' )) {
        break;
      }

      vec1.push_back( next );
    }

    //only read in two names
    if( vec1.size() != 2 ) {
      continue;
    }

    string source(vec1[0]);
    string dest(vec1[1]);

    //send information to output file
    temp1 = actor_graph->search( source, dest ); 

    fout << "The number of connections from " << source << " to " << dest << ": " << temp1 << endl;
  }

  fin.close();
  delete actor_graph;

  return 0;

}
