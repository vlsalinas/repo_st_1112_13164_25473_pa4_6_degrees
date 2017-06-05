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

/* 
 * Param: argc - number of arguments taken in
 *				argv - array of pointers to the arguments passed in
 * Return: int - whether program was successful or not
 */

int main( int argc, char* argv[] ) {

  if( argc != 4 ) {
    cerr << "Incorrect number of arguments. Try again." << endl;
    return -1;
  }

  //check validity of fourth param
  extensionGraph * EG1 = new extensionGraph();
  bool temp1 = EG1->loadFromFile( argv[1] );

  //check success of loading
  if( !temp1 ) return -1;

  ifstream fin(argv[2]);
  ofstream fout(argv[3]);

  int counter = 0;

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

    string data1(vec1[0]);
    string data2(vec1[1]);

    //send information to output file
    counter = EG1->search(data1, data2 ); 

    fout << "# of connections between " << data1 << " and "
      << data2 << " are " << counter << endl;
  }

  fin.close();
  delete EG1;

  return 0;

}
