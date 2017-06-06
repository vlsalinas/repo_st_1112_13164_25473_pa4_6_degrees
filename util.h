#ifndef UTIL_H
#define UTIL_H

#include <chrono>
#include <iostream>

using std::istream;

class Timer{
  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> st;

  public:

    /*
     * Function called when sting the timer.
     */
    void time_start();

    /*
     * Function called when ending the timer. Returns duration in nanoseconds
     * PRECONDITION: time_start() must be called before this function
     */
    long long time_end();


};



#endif //UTIL_H
