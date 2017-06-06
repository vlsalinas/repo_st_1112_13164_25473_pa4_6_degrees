#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <queue>
#include "Union.h"

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
    unordered_map<string, vector<ActorNode*>> info;
    unordered_map<string, ActorNode*> actor;
    unordered_map<string, vector<string>> connections;

  public:
    ActorGraph(void) {}

    ~ActorGraph(void);

    int max;

    void f1(string film, vector<ActorNode*>& vector_of_actors, unordered_map<string, vector<ActorNode*>>::iterator& insert_data);

    void f2(unordered_map<string, ActorNode*>::iterator search, string actor_name);

    void f3(int& temp, ActorNode*& next, unordered_map<string, int>::iterator& movieSearch, priority_queue<ActorNode*, vector<ActorNode*>, ActorNodeComp>& pq, ActorNode*& curr);

    void f4(unordered_map<string, ActorNode*>::iterator& reset);

    void f5(ActorNode*& aNode, string& temp, stack<string>& rrr, std::size_t& split);

    void f6(ActorNode*& aNode, string& temp, stack<string>& rrr, std::size_t& split);

    void f7(unordered_map<string, ActorNode*>::iterator& a_iter, int& yyy);

    void f8(queue<ActorNode*>& tss, int& yyy, vector<ActorNode*>& vec1, vector<string>& dest, int& i, vector<int>& year_acted_together);

    void f9(unordered_map<string, ActorNode*>::iterator& clear);

    void f10(unordered_map<string, ActorNode*>::iterator& a_iter, int& yyy, Union& u1);

    void f11(vector<int>& year_acted_together, vector<string>& source, vector<string>& dest, int& yyy, Union& u1);

    void f12(unordered_map<string, ActorNode*>::iterator& iter1);

    /**
     * rdered_map<string, ActorNode*>::iterator& clear);
     *
     *     void f10(unordered_map<string, ActorNode*>::iterator& a_iter, int& yyy, Union& u1);
     *
     *         void f11(vector<int>& year_acted_together, vector<string>& source, vector<string>& dest, int& yyy, Union& u1);
     *
     *             void f12(unordered_map<string, ActorNode*>::iterator& iter1);
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + 
     *		(2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    /**
     * Param: in_filename - input filename
     * Return: boolean saying whether load was successful or not
     * Load the actors into nodes and populates graph's actor hashmap
     */
    bool loadFromFile(const char* in_filename);

    /**
     * Param: string source - starting actor
     *				string dest - ending actor 
     * Return: stack<string> - the path names of the actors/movies from start to end
     * Use BFS to search our graph for the shortest path from the first actor
     * to the second
     */
    stack<string> findPath( string source, string dest );

    /**
     * BFS implementation for actorconnections
     * Param: vector<string> source - vector of actors we are starting at
     *				vector<string> dest - vector of actors we are connecting to
     * Return: vector<int> - the year the two actors were connected for each pair
     *
     */
    vector<int> BFSConnect( vector<string> source, vector<string> dest );


    /**
     * ufind implementation for actorconnections
     * Param: vector<string> source - vector of actors we are starting at
     *				vector<string> dest - vector of actors we are connecting to
     * Return: vector<int> - the year the two actors were connected for each pair
     *
     */
    vector<int> UFindConnect( vector<string> source, vector<string> dest );

};


#endif // ACTORGRAPH_H
