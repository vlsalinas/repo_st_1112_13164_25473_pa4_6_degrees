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


/* 
 * Param: argc - number of arguments taken in
 *				argv - array of pointers to the arguments passed in
 * Return: int - whether program was successful or not
 */

int main( int argc, char* argv[] ) {

  bool ww = false;
  ActorGraph * graph = new ActorGraph();
  Timer time;

  //do checks on all input

  //check if number of args is correct
  if( argc != 5 ) {
    cerr << "Not the right number of arguments. Goodbye." << endl;
    return -1;
  }

  //check ww boolean
  if( *argv[2] != 'u' && *argv[2] != 'w' ) {
    cerr << "Invalid argument. Try later." << *argv[2] << endl;
    return -1;
  }

  //call on ww or unww?
  if( *argv[2] == 'w' ) {
    ww = true;
  }

  time.time_start();

  bool loadSuccess = graph->loadFromFile( argv[1], ww );

  //check success of loading
  if( !loadSuccess ) return -1;

  ifstream fin(argv[3]);
  ofstream fout(argv[4]);

  bool have_header = false;

  //reading file 
  while(fin) {

    string s;

    //get the next line
    if( !getline( fin, s )) {
      break;
    }

    //skip header
    if( !have_header ) {
      have_header = true;
      fout << "(actor)--[movie#@year]-->(actor)--..." << endl;
      continue;
    }

    istringstream ss( s );
    //will hold the start and end actors
    vector <string> pairs;

    //while there are strings to read in
    while( ss ) {

      string next;

      //get the next string before hitting a tab character
      if( !getline( ss, next, '\t' )) {
        break;
      }

      pairs.push_back( next );
    }

    //only read in two names
    if( pairs.size() != 2 ) {
      continue;
    }

    string start_actor(pairs[0]);
    string end_actor(pairs[1]);

    //send information to output file
    stack<string> pathway = 
      graph->pathFinding( start_actor, end_actor );
    if( pathway.empty() ) {
      continue;	
    } 

    fout << "(" << start_actor << ")";

    //pop off pathway from stack
    while( !pathway.empty() ) {
      fout << pathway.top();
      pathway.pop();
    }

    //add last actor to line
    fout << "(" << end_actor << ")\n";
  }

  if( !fin.eof() ) {
    cerr << "Failed to read " << argv[3] << "!\n";
    return -1;
  }

  long long timing = time.time_end();
  cout << "Time taken: " << timing << endl;
  fin.close();	
  delete graph;	

  return 0;

}
