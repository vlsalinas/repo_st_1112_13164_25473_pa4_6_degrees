/*
 * Vincent Salinas
 * 6-3-2017
 * CSE 100
 * Project Assignmenr 4, Graphs
 */

#include "Timer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string.h>
#include <stdio.h>
#include "ActorGraph.h"
#include "ActorNode.h"
#include "Link.h"
using namespace std;

int main( int argc, char* argv[] ) {

  bool method_to_use = false;
  ActorGraph * actor_graph = new ActorGraph();
  // Start timer.
  Timer duration;
  duration.time_start();
  // Commence validation checks.
  int number_of_arguments = argc;
  char* algorithm = argv[4];

  // Validation check for crrect number of arguments.
  if( number_of_arguments != 4 && number_of_arguments != 5 ) {
    cerr << "Invalid number of arguments. Aborting." << endl;
    return -1;
  }

  // Validation check for BFS or Link Find.
  if( number_of_arguments == 4
      || strcmp( algorithm, "ufind" ) == 0 
      || strcmp( algorithm, "bfs" ) == 0 ) {

    if( number_of_arguments == 4
        || strcmp( algorithm, "ufind" ) == 0) {
      method_to_use = false;
    }
    else {
      method_to_use = true;
    }
  }
  else {
    cerr << "Invalid argument for method to use. Aborting." << endl;
    return -1;
  }


  bool load_file = actor_graph->loadFromFile( argv[1] );
  // Validation check for successful file read.
  if( !load_file ) return -1;

  ifstream fin(argv[2]);
  ofstream fout(argv[3]);
  bool have_header = false;

  vector<string> vec2;
  vector<string> source;
  vector<string> dest;
  vector<int> yyy;

  // read file
  while(fin) {

    string s;

    if( !getline( fin, s )) {
      break;
    }

    // ignore header
    if( !have_header ) {	
      have_header = true;
      fout << "Actor1\tActor2\tYear" << endl;
      continue;
    }

    istringstream ss( s );
    // vec1 source and dest actors
    vector <string> vec1;

    // keep reading if there are lines to be read in
    while( ss ) {

      string next;

      // vec1 data before next tab
      if( !getline( ss, next, '\t' )) {
        break;
      }

      vec1.push_back( next );
    }

    // stop after 2 actors vec1ed
    if( vec1.size() != 2 ) {
      continue;
    }

    source.push_back(vec1[0]);
    dest.push_back(vec1[1]);

  }

  // write to output file.
  if( method_to_use ) {
    yyy = actor_graph->BFS( source, dest );
  }
  else {
    yyy = actor_graph->union_find( source, dest ); 
  }

  for( int i = 0; i < yyy.size(); i++ ) {
    fout << source[i] << "\t" << dest[i] << "\t" << yyy[i]
      << endl;
  }


  // stop timer
  long long timing = duration.time_end();
  cout << "Duration (nanoseconds): " << timing << endl;
  // close file
  fin.close();
  // delete graph
  delete actor_graph;

  return 0;
}

	
