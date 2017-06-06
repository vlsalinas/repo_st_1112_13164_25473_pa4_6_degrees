
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

    /* constructor */
    Union() {};
    /**
     * Param: src - the src actor node to union
     *				dest - the dest actor node to union
     * Return: none.
     * Union the src and dest nodes
     */
    void unionOp( ActorNode* src, ActorNode* dest, unordered_map<string, ActorNode*> & actor  );


    /**
     * Param: aNode - the node being searched for in the set
     * Return: ActorNode* - the sentinel node of aNode
     * Find the node and connect all nodes in path to root
     */
    ActorNode* unionFind( ActorNode* aNode, unordered_map<string, ActorNode*> & actor );

    void u1(ActorNode*& data1, ActorNode*& data2);
    void u2(ActorNode*& data1, ActorNode*& data2);
    void u3(ActorNode*& begin, stack<ActorNode*>& stack1);
    void u4(stack<ActorNode*>& stack1, ActorNode*& begin, int& i);
};


#endif // UNION_H
