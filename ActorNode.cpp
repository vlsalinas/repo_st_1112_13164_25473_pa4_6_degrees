#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <sstream>
#include "ActorNode.h"
#include "ActorGraph.h"
#include "Union.h"

using namespace std;

/*
 * Param: The celebrity of the actor whose node it is
 * Return: None.
 * Initialize the node.
 */
ActorNode::ActorNode(std::string n) {
  celebrity = n;
  edge_weight = INT_MAX;
  ante = nullptr;
  soFar = false;
  cost = 1;
}

/*
 * Param: other - the other node to be compared to this
 * Return: boolean - whether the passed in node is less than this or not
 *		true - this < other
 *		false - this > other
 * Compares the passed in node to the current node using first the weight
 *		and then the actor as a means of comparison.
 */
bool ActorNode::operator<(const ActorNode& other) {
  //if this's weight is different from other
  if( edge_weight != other.edge_weight ) {
    return edge_weight > other.edge_weight;
  }

  //otherwise compare the actor celebritys
  return celebrity > other.celebrity;
}

