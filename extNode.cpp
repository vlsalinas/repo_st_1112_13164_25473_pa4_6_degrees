/*
 * Vincent Salinas
 * 6-3-2017
 * CSE 100
 * Project Assignmenr 4, Graphs
 */

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include "extNode.h"

/**
 * Param: 
 *              v = value of node
 * Return: 
 *              None.
 * Description:
 *              Construtor for a node
 */
extNode::extNode(int v){

  soFar = false;
  length = 0;
  item = v;

}

