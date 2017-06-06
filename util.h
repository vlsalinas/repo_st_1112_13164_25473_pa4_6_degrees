/*
 * Vincent Salinas
 * 6-2-2017
 * CSE 100
 * Project Assignment 4, Graphs
 */

#ifndef UTIL_H
#define UTIL_H

#include <chrono>
#include <iostream>

using std::istream;

class Timer{

  public:

    // start timer (nanoseconds).
    // Takes no parameters. 
    // Returns void.
    void time_start();

    // end timer (nanoseconds). 
    // Takes no parameters.
    // Return time duration.
    long long time_end();
  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> st;


};



#endif //UTIL_H
