
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

    /* Constructor */
    ActorNode(std::string name);

    /* Actor name */
    std::string celebrity;

    /* weight for ufind */
    int cost;

    /* counter of distance */
    int edge_weight;

    /* year tracker for ufind */
    int track_year;

    /* checked boolean */
    bool soFar;

    /* hashmap of movies for actor with weights */
    unordered_map<std::string, int> films_list;

    /* pointer to ante node in current search */
    ActorNode * ante;

    /* current movie and year*/
    std::string ante_film;

    /* overloaded comparison operator for node */
    bool operator<(const ActorNode& other); 

}; 

#endif // ACTORNODE_H
