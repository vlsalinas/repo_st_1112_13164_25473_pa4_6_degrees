/*
 * Vincent Salinas
 * 5-30-2017
 * CSE 100
 * Project Assignment 4, Graphs
 *
 * Description:
 *      Contains member and function decarations for ActorNode class.
 *
 */

#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class ActorGraph;
class Union;

class ActorNode {

  public:
    ActorNode(std::string name); // Constructor
    std::string celebrity; // actor
    int cost; // cost for an edge
    int edge_weight; // total distance (cost)
    int track_year; // current year for union find looked for
    bool soFar; // boolean indicating status so far
    unordered_map<std::string, int> films_list; // hashmap of films of acotrs w/ costs
    ActorNode * ante; // previous node pointer
    std::string ante_film; // current movie/year
    bool operator<(const ActorNode& other); 

}; 

#endif // ACTORNODE_H
