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
 * Param: const char * in_filename - file of the list of actors and films_list
 *				bool use_weighted_edges - if there are weighted edges
 * Return: bool if it was loaded successfully
 * Loads the file and creates the graph
 */
bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges){
  // Initialize the file stream
  ifstream fin(in_filename);

  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (fin) {
    string s;

    // get the next line
    if (!getline( fin, s )) break;

    if (!have_header) {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss) {
      string next;

      // get the next string before hitting a tab character
      if (!getline( ss, next, '\t' )) break;

      record.push_back( next );
    }

    if (record.size() != 3) {
      continue;
    }

    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);

    // check for name in hashmap of actors
    unordered_map<string, ActorNode*>::iterator search = 
      actor.find(actor_name);

    // if not, then create node and call addToGraph
    if( search == actor.end() ) {
      ActorNode *newNode = new ActorNode(actor_name);
      actor.insert(make_pair((string)actor_name, 
            (ActorNode*)newNode));
      search = actor.find(actor_name);
    } 

    // else, update node
    string film = movie_title + '\t' + record[2];

    // find weight
    int cost = 1;
    if( use_weighted_edges ) {
      cost = 1 + (2015 - movie_year);
    }

    ((*search).second->films_list).insert(make_pair((string)film, (int)cost));

    //add to info hashmap
    unordered_map<string, vector<ActorNode*>>::iterator
      insert_data = info.find(film);
    vector<ActorNode*> vector_of_actors;
    f1(film, vector_of_actors, insert_data);
    //movie not there
    //    if( insert_data == info.end() ) {
    //      vector<ActorNode*> vector_of_actors;
    //      info.insert(make_pair((string)movie, 
    //            (vector<ActorNode*>)vector_of_actors));
    //      insert_data = info.find(movie);
    //    }

    ActorNode* temp = (*search).second;
    //add actor to that movie's vector
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
  if( insert_data == info.end() ) {
    info.insert(make_pair((string)film, (vector<ActorNode*>)vector_of_actors));
    insert_data = info.find(film);
  }
}


/**
 * Param: in_filename - name of input file
 * Return: boolean - whether load was successful or not
 * Load in info to populate ActorNodes and actor hashmap
 */
bool ActorGraph::loadFromFile(const char* in_filename) {

  // Initialize the file stream
  ifstream fin(in_filename);

  bool have_header = false;
  max = INT_MAX;

  // keep reading lines until the end of file is reached
  while (fin) {
    string s;

    // get the next line
    if (!getline( fin, s )) break;

    if (!have_header) {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss) {
      string next;

      // get the next string before hitting a tab character
      if (!getline( ss, next, '\t' )) break;

      record.push_back( next );
    }

    if (record.size() != 3) {
      continue;
    }

    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);

    //check for oldest year
    if( movie_year < max ) {
      max = movie_year;
    }

    // check for name in hashmap of actors
    unordered_map<string, ActorNode*>::iterator search = 
      actor.find(actor_name);
    f2(search, actor_name);
    // if not, then create node and call addToGraph
    // if( search == actor.end() ) {
    //   ActorNode *newNode = new ActorNode(actor_name);
    //   actor.insert(make_pair((string)actor_name, 
    //         (ActorNode*)newNode));
    //   search = actor.find(actor_name);
    // } 

    // else, update node
    string film = movie_title + '\t' + record[2];

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

void ActorGraph::f2(unordered_map<string, ActorNode*>::iterator search, string actor_name)
{
  if( search == actor.end() ) {
    ActorNode *newNode = new ActorNode(actor_name);
    actor.insert(make_pair((string)actor_name, 
          (ActorNode*)newNode));
    search = actor.find(actor_name);
  }
}

/*
 * Param: actor - the hashmap of all actors in the graph
 *				string source - the actor whose node we are starting at
 *				string dest - the actor whose node we are ending at
 * Return: stack - the path names of the actors/films_list from start to end
 * Use BFS to search our graph for the shortest path from the first to last
 *		actor.
 */
stack<string> ActorGraph::pathFinding( string source, string dest ) {
  stack<string> rrr;

  unordered_map<string, ActorNode*>::iterator findActor = 
    actor.find(source);
  unordered_map<string, ActorNode*>::iterator endCheck = 
    actor.find(dest);

  //check to see if actors are in graph
  if( findActor == actor.end() || endCheck == actor.end() || 
      source == dest ) {

    if( findActor == actor.end() ) {
      cerr << "Failed to locate node '" << source << "'" << endl;
    }
    else if ( endCheck == actor.end() ) {
      cerr << "Failed to locate node '" << dest << "'" << endl;
    }
    return rrr;
  }


  //use Dijkstra's Algorithm 

  ActorNode* aNode = nullptr;

  priority_queue<ActorNode*, vector<ActorNode*>, ActorNodeComp> pq;
  ActorNode* start = (*findActor).second;
  start->edge_weight = 0;
  pq.push(start);

  //search for neighbors
  while( !pq.empty() ) {
    ActorNode* curr = pq.top();			
    pq.pop();

    if( !curr->soFar ) {
      curr->soFar = true;
    }

    unordered_map<string, int>::iterator movieSearch = curr->films_list.begin();
    for( ;movieSearch != curr->films_list.end(); movieSearch++ ) {
      unordered_map<string, vector<ActorNode*>>::iterator neighborSearch = info.find((*movieSearch).first);
      vector<ActorNode*> addActor = (*neighborSearch).second;

      for( int i = 0; i < addActor.size(); i++ ) {
        ActorNode* next = addActor[i];
        int temp = curr->edge_weight + next->films_list.at((*movieSearch).first);

        f3(temp, next, movieSearch, pq, curr);
        //new connection made in graph
        //if( temp < next->edge_weight && !next->soFar ) {
        //  next->ante_film = (*movieSearch).first;
        //  next->ante = curr;
        //  next->edge_weight = temp;
        //  pq.push(next);
        //}

        if( next -> celebrity == dest ) {
          aNode = next;
          break;
        }
      }
    }
  }

  //didn't find end actor
  if( aNode == nullptr || aNode->celebrity != dest ) {
    unordered_map<string, ActorNode*>::iterator reset = actor.begin();
    f4(reset);
    //for( ; reset != actor.end(); reset++ ) {
    //  (*reset).second->edge_weight = INT_MAX;	
    //  (*reset).second->ante = nullptr;	
    //  (*reset).second->ante_film = "";
    //  (*reset).second->soFar = false;	
    //}

    return rrr;
  }

  //add pathway to stack
  while( aNode->ante ) {
    //check if single connection
    string temp;

    //find movie and year parts of string
    std::size_t split = aNode->ante_film.find("\t");

    if( aNode->ante->celebrity == source ) {
      f5(aNode, temp, rrr, split);
      //temp = "--[" + aNode->ante_film.substr(0, split) + "#@" + 
      //  aNode->ante_film.substr(split+1, aNode->ante_film.size())
      //  + "]-->";
      //rrr.push(temp);
      break;
    }

    else {
      f6(aNode, temp, rrr, split);
      //temp = '(' + aNode->ante->name + ")--[" + 
      //  aNode->ante_film.substr(0, split) + "#@" + 
      //  aNode->ante_film.substr(split+1, aNode->ante_film.size())
      //  + "]-->";
      //rrr.push(temp);
    }	
    //go back one node and reset node 
    aNode = aNode->ante;
  }

  //Reset graph
  unordered_map<string, ActorNode*>::iterator reset = actor.begin();
  f4(reset);
  //for( ; reset != actor.end(); reset++ ) {
  //  (*reset).second->edge_weight = INT_MAX;	
  //  (*reset).second->ante = nullptr;	
  //  (*reset).second->ante_film = "";
  //  (*reset).second->soFar = false;	
  //}
  return rrr;
}

void ActorGraph::f6(ActorNode*& aNode, string& temp, stack<string>& rrr, std::size_t& split)
{
  temp = '(' + aNode->ante->celebrity + ")--[" + 
    aNode->ante_film.substr(0, split) + "#@" + 
    aNode->ante_film.substr(split+1, aNode->ante_film.size())
    + "]-->";
  rrr.push(temp);

} 

void ActorGraph::f5(ActorNode*& aNode, string& temp, stack<string>& rrr, std::size_t& split)
{
  temp = "--[" + aNode->ante_film.substr(0, split) + "#@" + 
    aNode->ante_film.substr(split+1, aNode->ante_film.size())
    + "]-->";
  rrr.push(temp);
} 

void ActorGraph::f3(int& temp, ActorNode*& next, unordered_map<string, int>::iterator& movieSearch, priority_queue<ActorNode*, vector<ActorNode*>, ActorNodeComp>& pq, ActorNode*& curr)
{
  if( temp < next->edge_weight && !next->soFar ) {
    next->ante_film = (*movieSearch).first;
    next->ante = curr;
    next->edge_weight = temp;
    pq.push(next);
  }

}

void ActorGraph::f4(unordered_map<string, ActorNode*>::iterator& reset)
{
  for( ; reset != actor.end(); reset++ ) {
    (*reset).second->edge_weight = INT_MAX;	
    (*reset).second->ante = nullptr;	
    (*reset).second->ante_film = "";
    (*reset).second->soFar = false;	
  }
}

/**
 * BFSCONNECT
 * Param: vector<string> source - vector of actors we start search with
 *				vector<string> dest - vector of actors we are connecting to
 * Return: vector<int> - year they were first connected for each pair
 * Finds first connection between the two actors using BFS
 */
vector<int> ActorGraph::BFS( vector<string> source, vector<string> dest ) {

  vector<int> year_acted_together ( source.size(), 9999 );


  //BFS to find earliest connection
  int yyy = max;
  //push current to queue


  while( yyy != 2016 ) {
    //for each actor in actor hashmap
    unordered_map<string, ActorNode*>::iterator a_iter = actor.begin();
    for( ; a_iter != actor.end(); a_iter++ ) {
      f7(a_iter, yyy);
      ////for each movie in hashmap
      //unordered_map<string, int>::iterator n_iter = (*a_iter).second->films_list.begin();
      //for( ; n_iter != (*a_iter).second->films_list.end(); n_iter++ ) {
      //  //if movie == yyy
      //  if( (*n_iter).second != yyy ) 
      //    continue;
      //  //find in info hashmap
      //  unordered_map<string, vector<ActorNode*>>::iterator i_iter = info.find((*n_iter).first);
      //  //if no
      //  if( i_iter == info.end() ) {
      //    //add movie to info
      //    vector<ActorNode*> Data;
      //    info.insert(make_pair((string)(*n_iter).first, (vector<ActorNode*>)Data)); 
      //    i_iter = info.find((*n_iter).first);
      //  }
      //  //add actor to info vector
      //  (*i_iter).second.push_back((*a_iter).second);

      //}
    }

    //search whole tree of current year or until end actor is found
    for( int i = 0; i < source.size(); i++ ) {
      if( year_acted_together[i] != 9999 ) 
        continue;

      queue<ActorNode*> tss;
      unordered_map<string, ActorNode*>::iterator iter1 = actor.find(source[i]);
      ActorNode* start = (*iter1).second;
      tss.push(start);
      vector<ActorNode*> vec1;

      while( !tss.empty() ) {
        f8(tss, yyy, vec1, dest, i, year_acted_together);
        ////look at neighbors of current
        //ActorNode* temp1 = tss.front();
        //temp1->soFar = true;
        //vec1.push_back(temp1);
        //tss.pop();
        //auto iter2 = temp1->films_list.begin();
        //for( ; iter2 != temp1->films_list.end(); iter2++ ) {
        //  //	if( year_acted_together[i] != 9999 ) 
        //  //	break;
        //  auto iter3 = info.find((*iter2).first);
        //  if( iter3 == info.end() ) {
        //    continue;
        //  }

        //  auto iter4 = (*iter3).second.begin();
        //  for( ; iter4 != (*iter3).second.end(); iter4++ ) {

        //    //	if( year_acted_together[i] != 9999 ) 
        //    //	break;
        //    if( (*iter4)->name == dest[i] ) {
        //      year_acted_together[i] = yyy;
        //      break;
        //    }
        //    if( !(*iter4)->soFar ) {
        //      (*iter4)->soFar = true;
        //      tss.push((*iter4));
        //    }
        //  }
        //}
      }
      vector<ActorNode*>::iterator iter5 = vec1.begin();
      for( ; iter5 != vec1.end(); iter5++ ) {
        (*iter5)->soFar = false;
      }
    }
    yyy++;
  }

  //reset graph
  info.clear();
  unordered_map<string, ActorNode*>::iterator clear = actor.begin();
  for( ; clear != actor.end(); clear++ ) {
    (*clear).second->soFar = false;
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
    //	if( year_acted_together[i] != 9999 ) 
    //	break;
    auto iter3 = info.find((*iter2).first);
    if( iter3 == info.end() ) {
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
    //find in info hashmap
    unordered_map<string, vector<ActorNode*>>::iterator i_iter = info.find((*n_iter).first);
    //if no
    if( i_iter == info.end() ) {
      //add movie to info
      vector<ActorNode*> Data;
      info.insert(make_pair((string)(*n_iter).first, (vector<ActorNode*>)Data)); 
      i_iter = info.find((*n_iter).first);
    }
    //add actor to info vector
    (*i_iter).second.push_back((*a_iter).second);

  }

}


/**
 * UFINDCONNECT
 * Param: vector<string> source - vector of actors we start search with
 *				vector<string> dest - vector of actors we are connecting to
 * Return: vector<int> - vector of years they were first connected
 * Finds first connection between the two actors using BFS
 */
vector<int> ActorGraph::UFindConnect( vector<string> source, vector<string> dest ) {
  vector<int> year_acted_together (source.size(), 9999);


  int yyy = max;
  Union u1;
  //for each year
  while( yyy != 2016 ) {
    //populate info like in BFS
    unordered_map<string, ActorNode*>::iterator a_iter = actor.begin();
    //create hashmap of all nodes for disjoint set
    for( ; a_iter != actor.end(); a_iter++ ) {
      //for each movie in hashmap
      //set all nodes' ante pointers to end()
      //all weights should be 1
      unordered_map<string, int>::iterator n_iter = (*a_iter).second->films_list.begin();
      f10(a_iter,yyy,u1);
     // for( ; n_iter != (*a_iter).second->films_list.end(); n_iter++ ) {
     //   if( (*n_iter).second != yyy ) 
     //     continue;
     //   //find in info hashmap
     //   unordered_map<string, vector<ActorNode*>>::iterator i_iter = info.find((*n_iter).first);
     //   //if no
     //   if( i_iter == info.end() ) {
     //     //add movie to info
     //     vector<ActorNode*> Data;
     //     info.insert(make_pair((string)(*n_iter).first, (vector<ActorNode*>)Data)); 
     //     i_iter = info.find((*n_iter).first);
     //   }

     //   //add actor to info vector
     //   (*i_iter).second.push_back((*a_iter).second);
     //   //union all info.second nodes into one set

     //   int size = (*i_iter).second.size();
     //   if( size == 1 ) {
     //     ActorNode* root = (*a_iter).second; 
     //     root->soFar = true;
     //     root->ante = root;
     //     continue;
     //   }
     //   ActorNode* temp = (*i_iter).second.at(size-2);
     //   u1.unionOp( temp, (*a_iter).second, actor );
     // }
    }

    /*find -- call on each pair in input vector*/
    f11(year_acted_together, source, dest, yyy, u1);
   // for( int i = 0; i < source.size(); i++ ) {
   //   if( year_acted_together[i] != 9999 ) 
   //     continue;
   //   ActorNode* start = u1.unionFind( actor.at(source[i]), actor );
   //   ActorNode* end = u1.unionFind( actor.at(dest[i]), actor );


   //   //if equal, cler prev & return yyy
   //   if( start->name == end->name ) {
   //     year_acted_together[i] = yyy;
   //   }
   // }
    //increment year
    yyy++;
  }

  //if nothing
  info.clear();
  unordered_map<string, ActorNode*>::iterator iter1 = actor.begin();
  f12(iter1);
 // for( ; iter1 != actor.end(); iter1++ ) {
 //   (*iter1).second->soFar = false;
 //   (*iter1).second->ante = nullptr;
 //   (*iter1).second->weight = 1;
 // }
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

void ActorGraph::f11(vector<int>& year_acted_together, vector<string>& source, vector<string>& dest, int& yyy, Union& u1 )
{

  for( int i = 0; i < source.size(); i++ ) {
    if( year_acted_together[i] != 9999 )
      continue;
    ActorNode* st = u1.unionFind( actor.at(source[i]), actor );
    ActorNode* en = u1.unionFind( actor.at(dest[i]), actor );


      if( st->celebrity == en->celebrity ) {
        year_acted_together[i] = yyy;
      }
  }
}

void ActorGraph::f10(unordered_map<string, ActorNode*>::iterator& a_iter, int& yyy, Union& u1)
{
  //for each movie in hashmap
  //set all nodes' ante pointers to end()
  //all weights should be 1
  unordered_map<string, int>::iterator n_iter = (*a_iter).second->films_list.begin();
  for( ; n_iter != (*a_iter).second->films_list.end(); n_iter++ ) {
    if( (*n_iter).second != yyy )
      continue;
    //find in info hashmap
    unordered_map<string, vector<ActorNode*>>::iterator i_iter = info.find((*n_iter).first);
    //if no
    if( i_iter == info.end() ) {
      //add movie to info
      vector<ActorNode*> Data;
      info.insert(make_pair((string)(*n_iter).first, (vector<ActorNode*>)Data));
      i_iter = info.find((*n_iter).first);
    }

    //add actor to info vector
    (*i_iter).second.push_back((*a_iter).second);
    //union all info.second nodes into one set

    int temp1 = (*i_iter).second.size();
    if( temp1 == 1 ) {
      ActorNode* root = (*a_iter).second;
      root->soFar = true;
      root->ante = root;
      continue;
    }
    ActorNode* temp2 = (*i_iter).second.at(temp1-2);
    u1.unionOp( temp2, (*a_iter).second, actor );
  }
}

  /** 
   * Param: None.
   * Return: None.
   *	Deallocated memory associated with the graph.
   */

  ActorGraph::~ActorGraph() {
    unordered_map<string, ActorNode*>::iterator st1 = actor.begin();
    unordered_map<string, vector<ActorNode*>>::iterator st2 = info.begin();

    //delete nodes in actor
    for( ; st1 != actor.end(); st1++ ) {
      delete st1->second;
    }

  }

