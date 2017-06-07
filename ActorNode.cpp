/*
 * Vincent Salinas
 * 6-2-2017
 * CSE 100
 * Program Assignment 4, Graphs
 *
 * Description:
 *      Contains member and function implementations for
 *      ActorNode class. Used in the process of creating an
 *      ActorGraph in the pathfinder.cpp and actorconnections.cpp
 *      program.
 */

#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <sstream>
#include "ActorNode.h"
#include "ActorGraph.h"
#include "Link.h"

using namespace std;

/*
 * Paramieters:
 *              n = name of actor
 * Return: 
 *              None.
 * Description:
 *              Constructor
 */
ActorNode::ActorNode(std::string n) {
  celebrity = n;
  cost = 1;
  ante = nullptr;
  edge_weight = INT_MAX;
  soFar = false;
}

/*
 * Parameters: 
 *              other = second node to be compared
 * Return: 
 *              boolean whether the passed in node is less than this or not
 *		if true, then this is less than other
 *		else false, then this is greater than other
 * Description:
 *              Compares weight.
 */
bool ActorNode::operator<(const ActorNode& other) {
  if( edge_weight != other.edge_weight ) {
    return edge_weight > other.edge_weight;
  }

  return celebrity > other.celebrity;
}

