/*
 * Vincent Salinas
 * 6-1-2017
 * CSE 100
 * Project Assignment 4, Graphs
 *
 * Description:
 *      Contains member and function implementations of the ActorGraph
 *      class. Used to create and populate late graph used in the 
 *      pathfinder.cpp program. Also contains implementation for
 *      BFS and union-find algorithms.
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
#include "Link.h"

using namespace std;

// Destructor
ActorGraph::~ActorGraph() {
  unordered_map<string, ActorNode*>::iterator st1 = actor.begin();
  unordered_map<string, vector<ActorNode*>>::iterator st2 = details.begin();

  //delete nodes
  for( ; st1 != actor.end(); st1++ ) {
    delete st1->second;
  }

}

/**
 * Parameters:
 *              in_filename = file to be read
 *              use_weighted_edges = true if weighted edges 
 * Return: 
 *              boolean value: true if successful load, else false
 * Description: Load file to be read and populate graph
 */
bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges){
  ifstream fin(in_filename);
  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (fin) {
    string s;
    if (!getline( fin, s )) break;
    if (!have_header) {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> vec1;

    while (ss) {
      string next;
      if (!getline( ss, next, '\t' )) break;
      vec1.push_back( next );
    }

    if (vec1.size() != 3) {
      continue;
    }

    string actor_name(vec1[0]);
    string movie_title(vec1[1]);
    int movie_year = stoi(vec1[2]); 
    // find actor in unordered_map
    unordered_map<string, ActorNode*>::iterator search = 

      actor.find(actor_name);

    // create actor node if not found
    if( search == actor.end() ) {
      ActorNode *newNode = new ActorNode(actor_name);
      actor.insert(make_pair((string)actor_name, 
            (ActorNode*)newNode));
      search = actor.find(actor_name);
    } 
    string film = movie_title + '\t' + vec1[2];

    // get weight
    int cost = 1;
    if( use_weighted_edges ) {
      cost = 1 + (2015 - movie_year);
    }
    ((*search).second->films_list).insert(make_pair((string)film, (int)cost));

    // insert data into hashmap
    unordered_map<string, vector<ActorNode*>>::iterator
      insert_data = details.find(film);
    vector<ActorNode*> vector_of_actors;
    f1(film, vector_of_actors, insert_data);
    ActorNode* temp = (*search).second;
    //add actor
    ((*insert_data).second).push_back(temp);	

  }

  if (!fin.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  fin.close();

  return true;
}

void ActorGraph::f1(string film, vector<ActorNode*>& vector_of_actors, unordered_map<string, vector<ActorNode*>>::iterator& insert_data)
{
  if( insert_data == details.end() ) {
    details.insert(make_pair((string)film, (vector<ActorNode*>)vector_of_actors));
    insert_data = details.find(film);
  }
}


/**
 * Parameter: 
 *              in_filename = file to be read
 * Return: 
 *              boolean value indicating successful load or not
 * Description: loads file to be read and populates graph
 */
bool ActorGraph::loadFromFile(const char* in_filename) {

  ifstream fin(in_filename);
  bool have_header = false;
  max = INT_MAX;
  // read contents of file
  while (fin) {
    string s;
    // get next line
    if (!getline( fin, s )) break;
    if (!have_header) {
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> vec2;

    while (ss) {
      string next;
      if (!getline( ss, next, '\t' )) break;
      vec2.push_back( next );
    }

    if (vec2.size() != 3) {
      continue;
    }

    string actor_name(vec2[0]);
    string movie_title(vec2[1]);
    int movie_year = stoi(vec2[2]);

    //check for oldest year
    if( movie_year < max ) {
      max = movie_year;
    }

    // check for name in hashmap of actors
    unordered_map<string, ActorNode*>::iterator search = 
      actor.find(actor_name);
    f2(search, actor_name);
    // else, update node
    string film = movie_title + '\t' + vec2[2];

    // find weight
    int year = movie_year;

    ((*search).second->films_list).insert(make_pair((string)film, (int)year));
  }

  if (!fin.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  fin.close();

  return true;
}

void ActorGraph::f2(unordered_map<string, ActorNode*>::iterator& search, string& actor_name)
{
  if( search == actor.end() ) {
    ActorNode *newNode = new ActorNode(actor_name);
    actor.insert(make_pair((string)actor_name, 
          (ActorNode*)newNode));
    search = actor.find(actor_name);
  }
}

/*
 * Parameters: 
 *              source = start actor
 *		dest = end actor
 * Return: 
 *              stack<String> = list of names of actors from source to dest actor
 * Description:
 *              BFS search of shortest path from source to dest actor
 */
stack<string> ActorGraph::pathFinding( string source, string dest ) {
  unordered_map<string, ActorNode*>::iterator iter1 = 
    actor.find(source);
  unordered_map<string, ActorNode*>::iterator iter2 = 
    actor.find(dest);
  stack<string> rrr;
  //check to see if actors are in graph
  if( iter1 == actor.end() || iter2 == actor.end() || 
      source == dest ) {

    if( iter1 == actor.end() ) {
      cerr << "Failed to locate node '" << source << "'" << endl;
    }
    else if ( iter2 == actor.end() ) {
      cerr << "Failed to locate node '" << dest << "'" << endl;
    }
    return rrr;
  }

  // dijkstra's algo 
  ActorNode* aNode = nullptr;
  priority_queue<ActorNode*, vector<ActorNode*>, ActorNodeComp> pq;
  ActorNode* aNode2 = (*iter1).second;
  aNode2->edge_weight = 0;
  pq.push(aNode2);

  // search local nodes
  while( !pq.empty() ) {
    ActorNode* aNode3 = pq.top();			
    pq.pop();
    if( !aNode3->soFar ) {
      aNode3->soFar = true;
    }

    unordered_map<string, int>::iterator movieSearch = aNode3->films_list.begin();
    for( ;movieSearch != aNode3->films_list.end(); movieSearch++ ) {
      unordered_map<string, vector<ActorNode*>>::iterator iter3 = details.find((*movieSearch).first);
      vector<ActorNode*> vec1 = (*iter3).second;
      for( int i = 0; i < vec1.size(); i++ ) {
        ActorNode* next = vec1[i];
        int temp = aNode3->edge_weight + next->films_list.at((*movieSearch).first);
        f3(temp, next, movieSearch, pq, aNode3);
        if( next -> celebrity == dest ) {
          aNode = next;
          break;
        }
      }
    }
  }
  // actor not found
  if( aNode == nullptr || aNode->celebrity != dest ) {
    unordered_map<string, ActorNode*>::iterator iter6 = actor.begin();
    f4(iter6);
    return rrr;
  }

  // insert data into stack
  while( aNode->ante ) {
    string temp;
    std::size_t temp3 = aNode->ante_film.find("\t");
    if( aNode->ante->celebrity == source ) {
      f5(aNode, temp, rrr, temp3);
      break;
    }
    else {
      f6(aNode, temp, rrr, temp3);
    }	
    aNode = aNode->ante;
  }
  // clear graph
  unordered_map<string, ActorNode*>::iterator iter6 = actor.begin();
  f4(iter6);
  return rrr;
}

void ActorGraph::f6(ActorNode*& aNode, string& temp, stack<string>& rrr, std::size_t& temp3)
{
  temp = '(' + aNode->ante->celebrity + ")--[" + 
    aNode->ante_film.substr(0, temp3) + "#@" + 
    aNode->ante_film.substr(temp3+1, aNode->ante_film.size())
    + "]-->";
  rrr.push(temp);

} 

void ActorGraph::f5(ActorNode*& aNode, string& temp, stack<string>& rrr, std::size_t& temp3)
{
  temp = "--[" + aNode->ante_film.substr(0, temp3) + "#@" + 
    aNode->ante_film.substr(temp3+1, aNode->ante_film.size())
    + "]-->";
  rrr.push(temp);
} 

void ActorGraph::f3(int& temp, ActorNode*& next, unordered_map<string, int>::iterator& movieSearch, priority_queue<ActorNode*, vector<ActorNode*>, ActorNodeComp>& pq, ActorNode*& aNode3)
{
  if( temp < next->edge_weight && !next->soFar ) {
    next->ante_film = (*movieSearch).first;
    next->ante = aNode3;
    next->edge_weight = temp;
    pq.push(next);
  }

}

void ActorGraph::f4(unordered_map<string, ActorNode*>::iterator& iter6)
{
  for( ; iter6 != actor.end(); iter6++ ) {
    (*iter6).second->edge_weight = INT_MAX;	
    (*iter6).second->ante = nullptr;	
    (*iter6).second->ante_film = "";
    (*iter6).second->soFar = false;	
  }
}

/**
 * Breath First Search
 * Parameters:
 *              source = vector of actors to start seardch
 *		dest = vector of actors connecting to
 * Return: 
 *              vector<int> = contains year for each pair of actors connected
 * Description: 
 *              BFS to find shortest path between source actor and dest actor
 */
vector<int> ActorGraph::BFS( vector<string> source, vector<string> dest ) {
  vector<int> year_acted_together ( source.size(), 9999 );
  int yyy = max;
  while( yyy != 2016 ) {
    // initialize for each actor
    unordered_map<string, ActorNode*>::iterator a_iter = actor.begin();
    for( ; a_iter != actor.end(); a_iter++ ) {
      f7(a_iter, yyy);
    }
    // search for end actor, or until not found
    for( int i = 0; i < source.size(); i++ ) {
      if( year_acted_together[i] != 9999 ) 
        continue;

      queue<ActorNode*> tss;
      unordered_map<string, ActorNode*>::iterator iter1 = actor.find(source[i]);
      ActorNode* aNode4 = (*iter1).second;
      tss.push(aNode4);
      vector<ActorNode*> vec1;
      while( !tss.empty() ) {
        f8(tss, yyy, vec1, dest, i, year_acted_together);
      }
      vector<ActorNode*>::iterator iter5 = vec1.begin();
      for( ; iter5 != vec1.end(); iter5++ ) {
        (*iter5)->soFar = false;
      }
    }
    yyy++;
  }
  details.clear();
  unordered_map<string, ActorNode*>::iterator iter7 = actor.begin();
  for( ; iter7 != actor.end(); iter7++ ) {
    (*iter7).second->soFar = false;
  }
  return year_acted_together;
}

void ActorGraph::f8(queue<ActorNode*>& tss, int& yyy, vector<ActorNode*>& vec1, vector<string>& dest, int& i, vector<int>& year_acted_together)
{
  ActorNode* temp1 = tss.front();
  temp1->soFar = true;
  vec1.push_back(temp1);
  tss.pop();
  auto iter2 = temp1->films_list.begin();
  for( ; iter2 != temp1->films_list.end(); iter2++ ) {
    auto iter3 = details.find((*iter2).first);
    if( iter3 == details.end() ) {
      continue;
    }

    auto iter4 = (*iter3).second.begin();
    for( ; iter4 != (*iter3).second.end(); iter4++ ) {

      //	if( year_acted_together[i] != 9999 ) 
      //	break;
      if( (*iter4)->celebrity == dest[i] ) {
        year_acted_together[i] = yyy;
        break;
      }
      if( !(*iter4)->soFar ) {
        (*iter4)->soFar = true;
        tss.push((*iter4));
      }
    }
  }

}

void ActorGraph::f7(unordered_map<string, ActorNode*>::iterator& a_iter, int& yyy)
{
  //for each movie in hashmap
  unordered_map<string, int>::iterator n_iter = (*a_iter).second->films_list.begin();
  for( ; n_iter != (*a_iter).second->films_list.end(); n_iter++ ) {
    //if movie == yyy
    if( (*n_iter).second != yyy ) 
      continue;
    //find in details hashmap
    unordered_map<string, vector<ActorNode*>>::iterator i_iter = details.find((*n_iter).first);
    //if no
    if( i_iter == details.end() ) {
      //add movie to details
      vector<ActorNode*> Data;
      details.insert(make_pair((string)(*n_iter).first, (vector<ActorNode*>)Data)); 
      i_iter = details.find((*n_iter).first);
    }
    //add actor to details vector
    (*i_iter).second.push_back((*a_iter).second);

  }

}


/**
 * Link Find
 * Parameters: 
 *              source = vectors of actors to be searched
 *		dest = vector of actors to be connected
 * Return: 
 *              vector<int> = contains years of paired actors
 * Description:
 *              find union between source actor and dest actor
 */
vector<int> ActorGraph::union_find( vector<string> source, vector<string> dest ) {
  vector<int> year_acted_together (source.size(), 9999);
  int yyy = max;
  Link u1;
  while( yyy != 2016 ) {
    unordered_map<string, ActorNode*>::iterator a_iter = actor.begin();
    // creat unordered_map for each node in disjoint set
    for( ; a_iter != actor.end(); a_iter++ ) {
      // initialize weights to 1, and all previous nodes to null
      unordered_map<string, int>::iterator n_iter = (*a_iter).second->films_list.begin();
      f10(a_iter,yyy,u1);
    }

    // input each pair
    f11(year_acted_together, source, dest, yyy, u1);
    // proceed to next year
    yyy++;
  }

  // nothing found
  details.clear();
  unordered_map<string, ActorNode*>::iterator iter1 = actor.begin();
  f12(iter1);
  return year_acted_together;
}

void ActorGraph::f12(unordered_map<string, ActorNode*>::iterator& iter1)
{
  for( ; iter1 != actor.end(); iter1++ ) {
    (*iter1).second->soFar = false;
    (*iter1).second->ante = nullptr;
    (*iter1).second->cost = 1;
  }

}

void ActorGraph::f11(vector<int>& year_acted_together, vector<string>& source, vector<string>& dest, int& yyy, Link& u1 )
{

  for( int i = 0; i < source.size(); i++ ) {
    if( year_acted_together[i] != 9999 )
      continue;
    ActorNode* st = u1.union_find( actor.at(source[i]), actor );
    ActorNode* en = u1.union_find( actor.at(dest[i]), actor );


    if( st->celebrity == en->celebrity ) {
      year_acted_together[i] = yyy;
    }
  }
}

void ActorGraph::f10(unordered_map<string, ActorNode*>::iterator& a_iter, int& yyy, Link& u1)
{
  unordered_map<string, int>::iterator n_iter = (*a_iter).second->films_list.begin();
  for( ; n_iter != (*a_iter).second->films_list.end(); n_iter++ ) {
    if( (*n_iter).second != yyy )
      continue;
    unordered_map<string, vector<ActorNode*>>::iterator i_iter = details.find((*n_iter).first);
    if( i_iter == details.end() ) {
      //add movie to details
      vector<ActorNode*> Data;
      details.insert(make_pair((string)(*n_iter).first, (vector<ActorNode*>)Data));
      i_iter = details.find((*n_iter).first);
    }

    //add actor to details vector
    (*i_iter).second.push_back((*a_iter).second);
    
    //union all details.second nodes into one set
    int temp1 = (*i_iter).second.size();
    if( temp1 == 1 ) {
      ActorNode* root = (*a_iter).second;
      root->soFar = true;
      root->ante = root;
      continue;
    }
    ActorNode* temp2 = (*i_iter).second.at(temp1-2);
    u1.union_them( temp2, (*a_iter).second, actor );
  }
}



