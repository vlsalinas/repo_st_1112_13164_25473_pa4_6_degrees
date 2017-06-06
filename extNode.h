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
    extNode(int v);

    /* int of key */
    int item;

    /* height */
    int length;

    /* check boolean */
    bool soFar;

    /* vector of friends */
    vector<int> acquaintances;

};

#endif
