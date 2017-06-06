// Vincent Salinas
// 5-30-2017
// CSE 100
// Project Assignment 4, Graphs
#ifndef UNION_H
#define UNION_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class ActorNode;
class ActorGraph;

class Union {

  public:
    // Helper functions
    void u1(ActorNode*& data1, ActorNode*& data2);
    void u2(ActorNode*& data1, ActorNode*& data2);
    void u3(ActorNode*& begin, stack<ActorNode*>& stack1);
    void u4(stack<ActorNode*>& stack1, ActorNode*& begin, int& i);

    /* constructor */
    Union() {};
    /**
     * Param: 
     *          src - the src actor node to union
     *		dest - the dest actor node to union
     * Return: none.
     * Descriptin: union the src and dest nodes
     */
    void union_them( ActorNode* src, ActorNode* dest, unordered_map<string, ActorNode*> & actor  );

    /**
     * Param: aNode = node to be searched
     * Return: ActorNode* = the lookout node of aNode
     * Description: Find the node and connect all nodes in path to root
     */
    ActorNode* union_find( ActorNode* aNode, unordered_map<string, ActorNode*> & actor );

};


#endif // UNION_H
