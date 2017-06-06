/*
 * Vincent Salinas
 * 6-2-2017
 * CSE 100
 * Project Assignment 4, Graphs
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <queue>
#include <unordered_map>
#include "ActorGraph.h"
#include "ActorNode.h"
#include "Union.h"

using namespace std;

/**
 * Parameters: 
 *      src = source actor to union
 *	dest = dest actor node to union
 * Return: 
 *      None.
 * Description:
 *      union source and dest actors
 */
void Union::union_them( ActorNode* src, ActorNode* dest, unordered_map<string, ActorNode*> & actor  ) {

  src->soFar = true;
  dest->soFar = true;

  ActorNode* data1 = union_find( src, actor );
  ActorNode* data2 = union_find( dest, actor );
  if( data1 == data2 )
    return;

  // if more than one movie matched, then merge all acotrs in that movie
  if( data1->cost >= data2->cost ) {
    u1(data1, data2);
    return;
  }

  else {
    u2(data1, data2);
    return;
  }

}

void Union::u1(ActorNode*& data1, ActorNode*& data2)
{
  data2->ante = data1;
  data1->cost += data2->cost;
}

void Union::u2(ActorNode*& data1, ActorNode*& data2)
{
  data1->ante = data2;
  data2->cost += data1->cost;

}


/**
 * Parameters: 
 *              aNode = node to search
 * Return: 
 *              ActorNode* = node to union
 * Description:
 *              Connect all found nodes along the path to root
 */
ActorNode* Union::union_find( ActorNode* aNode, unordered_map<string, ActorNode*> & actor ) {

  stack<ActorNode*> stack1;
  ActorNode* begin = actor.at( aNode->celebrity);

  if( !begin->ante ) {
    begin->ante = begin;
    return begin;
  }

  int i = 0;
  // look up previous pointers and add to begin
  u3(begin, stack1);

  //store root
  ActorNode* aNode2 = begin;
  u4(stack1, begin, i);
  return aNode2;

}

void Union::u3(ActorNode*& begin, stack<ActorNode*>& stack1)
{
  while( begin->ante != begin ) {
    stack1.push(begin);
    begin = begin->ante;
  }	
}

void Union::u4(stack<ActorNode*>& stack1, ActorNode*& begin, int& i)
{
  while( !stack1.empty() ) {
    if( i != 0 ) 
      i++;
    // make all previous point to root
    ActorNode* aNode3 = stack1.top();
    aNode3->ante = begin;
    stack1.pop();
  }

}
