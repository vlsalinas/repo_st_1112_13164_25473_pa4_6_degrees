/*
 * Vincent Ssalinas
 * 5-30-2017
 * CSE 100
 * Project Assignment 4, Graphs
 *
 * Description:
 *
 * Contains member and function declarations for ActorGraph class.
 * Includes functions:
 *      loadFromFile() = loads file to be read
 *      pathFinding() = finds path from start to end actors
 *      BFS() = breadth first search algorithm
 *      union_find() = union find algorithm 
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <queue>
#include "Link.h"

using namespace std;

class ActorNode;

/**
 * Comparator for priority queue
 */
class ActorNodeComp {

  public:

    bool operator()(ActorNode*& lhs, ActorNode*& rhs) const {
      return lhs < rhs;
    }
};

class ActorGraph {

  protected:  
    //vector of our actor nodes
    unordered_map<string, vector<ActorNode*>> details;
    unordered_map<string, ActorNode*> actor;
    unordered_map<string, vector<string>> actor_links;

  public:
    ActorGraph(void) {} // Constructor
    ~ActorGraph(void); // Destructor

    int max;
    // Helper functions
    void f1(string film, vector<ActorNode*>& vector_of_actors, unordered_map<string, vector<ActorNode*>>::iterator& insert_data);

    void f2(unordered_map<string, ActorNode*>::iterator& search, string& actor_name);

    void f3(int& temp, ActorNode*& next, unordered_map<string, int>::iterator& movieSearch, priority_queue<ActorNode*, vector<ActorNode*>, ActorNodeComp>& pq, ActorNode*& curr);

    void f4(unordered_map<string, ActorNode*>::iterator& reset);

    void f5(ActorNode*& aNode, string& temp, stack<string>& rrr, std::size_t& split);

    void f6(ActorNode*& aNode, string& temp, stack<string>& rrr, std::size_t& split);

    void f7(unordered_map<string, ActorNode*>::iterator& a_iter, int& yyy);

    void f8(queue<ActorNode*>& tss, int& yyy, vector<ActorNode*>& vec1, vector<string>& dest, int& i, vector<int>& year_acted_together);

    void f9(unordered_map<string, ActorNode*>::iterator& clear);

    void f10(unordered_map<string, ActorNode*>::iterator& a_iter, int& yyy, Link& u1);

    void f11(vector<int>& year_acted_together, vector<string>& source, vector<string>& dest, int& yyy, Link& u1);

    void f12(unordered_map<string, ActorNode*>::iterator& iter1);

    /*
     * Load the graph from a tab-delimited file of actor->movie relationships.
     * Param: 
     *          in_filename = file to be read
     *          use_weighted_edges = if w was extracted from command line arg
     * Return:
     *          boolean indicating successful (or unsuccessful) load
     * Description:
     *           return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    /**
     * Param: 
     *          in_filename = file to be read
     * Return: 
     *          boolean indicating successful load or not
     * Description: 
     *          populate graph
     */
    bool loadFromFile(const char* in_filename);

    /**
     * Param: 
     *          source = start actor
     *		dest = destination actor 
     * Return: 
     *          stack<string> = stack of actor names from source actor to dest actor
     * Description:
     *          BFS search to find shortest path from source to dest
     */
    stack<string> pathFinding( string source, string dest );

    /**
     * Param: 
     *         source = vector of actors starting at 
     *	        dest = vector of actors to be connected
     * Return: 
     *          vector<int> = vector containing years for actor pairs
     * Description:
     *          BFS search for actorconnections
     */
    vector<int> BFS( vector<string> source, vector<string> dest );

    /**
     * ufind implementation for actorconnections
     * Param: 
     *          source - vector of actors starting at
     *		dest - vector of actors to be connected to
     * Return: 
     *          vector<int> = contains year of actor pairs
     * Description:
     *          union find implementation for actorconnections
     */
    vector<int> union_find( vector<string> source, vector<string> dest );

};


#endif // ACTORGRAPH_H
