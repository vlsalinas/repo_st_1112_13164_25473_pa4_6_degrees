/*
 * Vincent Salinas
 * 6-6-2017
 * CSE 100
 * Project Assignment 4, Graphs
 */

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include "extension_node.h"

/**
 * Parameters:
 *              v = value
 * Return: 
 *              none
 * Description:
 *              Construtor for a node in extension graph
 */
extension_node::extension_node(int v){

  item = v;
  soFar = false;
  heet = 0;

}

