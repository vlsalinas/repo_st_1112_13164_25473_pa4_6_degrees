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

void Union::unionOp( ActorNode* src, ActorNode* dest, unordered_map<string, ActorNode*> & actor  ) {

  src->checked = true;
  dest->checked = true;

  ActorNode* data1 = unionFind( src, actor );
  ActorNode* data2 = unionFind( dest, actor );
  if( data1 == data2 )
    return;

  //		//if more than one movie matches( a previous is already set)
  //		if( src->previous != nullptr ) {
  //merge all actors in those movies
  if( data1->weight >= data2->weight ) {
    //data2->previous = data1;
    //data1->weight += data2->weight;
    //return;
    u1(data1, data2);
  }

  else {
    //data1->previous = data2;
    //data2->weight += data1->weight;
    //return;
    u2(data1, data2);
  }

}

void Union::u1(ActorNode*& data1, ActorNode*& data2)
{
  data2->previous = data1;
  data1->weight += data2->weight;
  return;
}

void Union::u2(ActorNode*& data1, ActorNode*& data2)
{
  data1->previous = data2;
  data2->weight += data1->weight;
  return;

}


/**
 * Param: aNode - the node being searched for in the set
 * Return: ActorNode* - the aNode2 node of aNode
 * Find the node and connect all nodes in path to root
 */

ActorNode* Union::unionFind( ActorNode* aNode, unordered_map<string, ActorNode*> & actor ) {
  stack<ActorNode*> stack1;

  //cerr << "HELLO" << endl;
  //go to beginActor's place in hashmap	
  ActorNode* begin = actor.at( aNode->name );

  if( !begin->previous ) {
    begin->previous = begin;
    return begin;
  }

  int i = 0;
  //trace up previous pointers and add nodes to begin
  u3(begin, stack1);
  //while( begin->previous != begin ) {
  //  stack1.push(begin);
  //  begin = begin->previous;
  //}		

  //store root
  ActorNode* aNode2 = begin;
  //pop each node off stack
  u4(stack1, begin, i);
  //while( !stack1.empty() ) {
  //  if( i != 0 ) 
  //    //cerr << "Find i is : " << i << endl;
  //    i++;
  //  //reassign each previous to point to root
  //  ActorNode* aNode3 = stack1.top();
  //  aNode3->previous = begin;
  //  stack1.pop();
  //}
  return aNode2;

}

void Union::u3(ActorNode*& begin, stack<ActorNode*>& stack1)
{
  while( begin->previous != begin ) {
    stack1.push(begin);
    begin = begin->previous;
  }	
}

void Union::u4(stack<ActorNode*>& stack1, ActorNode*& begin, int& i)
{
  while( !stack1.empty() ) {
    if( i != 0 ) 
      //cerr << "Find i is : " << i << endl;
      i++;
    //reassign each previous to point to root
    ActorNode* aNode3 = stack1.top();
    aNode3->previous = begin;
    stack1.pop();
  }

}
