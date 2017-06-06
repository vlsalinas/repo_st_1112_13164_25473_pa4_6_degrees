/*
 * Vincent Salinas
 * 6-5-2017
 * CSE 100
 * Project Assignment 4, Graphs
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <stdlib.h>
#include "util.h"
#include "ActorGraph.h"
#include "ActorNode.h"
using namespace std;

int main( int argc, char* argv[] ) {

  bool ww = false;
  ActorGraph * actor_graph = new ActorGraph();
  Timer duration;

  //do checks on all input

  //check if number of args is correct
  if( argc != 5 ) {
    cerr << "Invalid number of arguments. Aborting." << endl;
    return -1;
  }

  //check ww boolean
  if( *argv[2] != 'u' && *argv[2] != 'w' ) {
    cerr << "Invalid argument: " << *argv[2] << endl;
    return -1;
  }

  //call on ww or unww?
  if( *argv[2] == 'w' ) {
    ww = true;
  }

  duration.time_start();

  bool load_file = actor_graph->loadFromFile( argv[1], ww );

  //check success of loading
  if( !load_file ) return -1;

  ifstream fin(argv[3]);
  ofstream fout(argv[4]);

  bool have_header = false;

  //reading file 
  while(fin) {

    string s;

    if( !getline( fin, s )) {
      break;
    }

    // ignore header
    if( !have_header ) {
      have_header = true;
      fout << "(actor)--[movie#@year]-->(actor)--..." << endl;
      continue;
    }

    istringstream ss( s );

    // Record actors
    vector <string> pairs;

    // Read entire file.
    while( ss ) {

      string next;

      // Read in next string before tab
      if( !getline( ss, next, '\t' )) {
        break;
      }

      pairs.push_back( next );
    }

    // stop at 2 actors
    if( pairs.size() != 2 ) {
      continue;
    }

    string start_actor(pairs[0]);
    string end_actor(pairs[1]);

    // write data to output file
    stack<string> stack1 = actor_graph->pathFinding( start_actor, end_actor );
    if( stack1.empty() ) {
      continue;	
    } 

    fout << "(" << start_actor << ")";

    // get stack1 from stack
    while( !stack1.empty() ) {
      fout << stack1.top();
      stack1.pop();
    }

    // Add last actor
    fout << "(" << end_actor << ")\n";
  }

  if( !fin.eof() ) {
    cerr << "Failed to read " << argv[3] << "!\n";
    return -1;
  }
  // stop timer
  long long timing = duration.time_end();
  cout << "Duration (nanoseconds): " << timing << endl;
  fin.close();	
  delete actor_graph;	

  return 0;

}
