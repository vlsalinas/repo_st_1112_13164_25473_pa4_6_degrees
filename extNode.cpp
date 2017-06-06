#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include "extNode.h"

/**
 * Param: value of the node
 * Return: none
 * Construtor for a node
 */
extNode::extNode(int v){

  item = v;
  soFar = false;
  length = 0;

}

