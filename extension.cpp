/*
 * Vincent Salinas
 * 6-1-2017
 * CSE 100
 * Project Assignmenr 4, Graphs
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string.h>
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include "extensionGraph.h"
#include "extNode.h"

using namespace std;

int main( int argc, char* argv[] ) {

  // Validation check for correct number of arguments.
  if( argc != 4 ) {
    cerr << "Invalid number of command line arguments. Aborting." << endl;
    return -1;
  }

  // Validation check
  extensionGraph * EG1 = new extensionGraph();
  bool temp1 = EG1->loadFromFile( argv[1] );

  if( !temp1 ) return -1;

  // open file stream for read and write.
  ifstream fin(argv[2]);
  ofstream fout(argv[3]);

  int counter = 0;

  // read file
  while(fin) {

    string s;

    if( !getline( fin, s )) {
      break;
    }

    istringstream ss( s );
    
    // records source and dest actors
    vector <string> vec1;

    // while there are lines to be read
    while( ss ) {

      string next;

      // record next data before tab
      if( !getline( ss, next, ' ' )) {
        break;
      }

      vec1.push_back( next );
    }

    // stop at 2 actors recorded
    if( vec1.size() != 2 ) {
      continue;
    }

    string data1(vec1[0]);
    string data2(vec1[1]);

    // write to output file
    counter = EG1->searching(data1, data2 ); 
    fout << "# of connections between " << data1 << " and " << data2 << " are " << counter << endl;
  }

  fin.close();
  delete EG1;
  return 0;

}
