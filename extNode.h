#ifndef EXTNODE_H
#define EXTNODE_H

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

class extNode {

  public:
    /* Constructor */
    extNode(int value);

    /* int of key */
    int key;

    /* height */
    int height;

    /* check boolean */
    bool check;

    /* vector of friends */
    vector<int> listOfFriends;

};

#endif
