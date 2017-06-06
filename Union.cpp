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
 * Param: src - the src actor node to union
 *				dest - the dest actor node to union
 * Return: none.
 * Union the src and dest nodes
 */

void Union::union_them( ActorNode* src, ActorNode* dest, unordered_map<string, ActorNode*> & actor  ) {

  src->soFar = true;
  dest->soFar = true;

  ActorNode* data1 = union_find( src, actor );
  ActorNode* data2 = union_find( dest, actor );
  if( data1 == data2 )
    return;

  //		//if more than one movie matches( a ante is already set)
  //		if( src->ante != nullptr ) {
  //merge all actors in those movies
  if( data1->cost >= data2->cost ) {
    //data2->ante = data1;
    //data1->cost += data2->cost;
    //return;
    u1(data1, data2);
  }

  else {
    //data1->ante = data2;
    //data2->cost += data1->cost;
    //return;
    u2(data1, data2);
  }

}

void Union::u1(ActorNode*& data1, ActorNode*& data2)
{
  data2->ante = data1;
  data1->cost += data2->cost;
  return;
}

void Union::u2(ActorNode*& data1, ActorNode*& data2)
{
  data1->ante = data2;
  data2->cost += data1->cost;
  return;

}


/**
 * Param: aNode - the node being searched for in the set
 * Return: ActorNode* - the aNode2 node of aNode
 * Find the node and connect all nodes in path to root
 */

ActorNode* Union::union_find( ActorNode* aNode, unordered_map<string, ActorNode*> & actor ) {
  stack<ActorNode*> stack1;

  //cerr << "HELLO" << endl;
  //go to beginActor's place in hashmap	
  ActorNode* begin = actor.at( aNode->celebrity);

  if( !begin->ante ) {
    begin->ante = begin;
    return begin;
  }

  int i = 0;
  //trace up ante pointers and add nodes to begin
  u3(begin, stack1);
  //while( begin->ante != begin ) {
  //  stack1.push(begin);
  //  begin = begin->ante;
  //}		

  //store root
  ActorNode* aNode2 = begin;
  //pop each node off stack
  u4(stack1, begin, i);
  //while( !stack1.empty() ) {
  //  if( i != 0 ) 
  //    //cerr << "Find i is : " << i << endl;
  //    i++;
  //  //reassign each ante to point to root
  //  ActorNode* aNode3 = stack1.top();
  //  aNode3->ante = begin;
  //  stack1.pop();
  //}
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
      //cerr << "Find i is : " << i << endl;
      i++;
    //reassign each ante to point to root
    ActorNode* aNode3 = stack1.top();
    aNode3->ante = begin;
    stack1.pop();
  }

}
