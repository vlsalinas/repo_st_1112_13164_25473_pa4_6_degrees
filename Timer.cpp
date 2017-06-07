/*
 * Vincent Salinas
 * 6-5-2017
 * CSE 100
 * Project Assignment 4, Graphs
 */

#include <iostream>
#include <sstream>
#include <ostream>
#include <vector>
#include <string>
#include "Timer.h"

using std::istream;
using std::istringstream;
using std::string;
using std::vector;

// time_end ends timer. Returns duration from start time (nanoseconds).
long long Timer::time_end() {
  std::chrono::time_point<std::chrono::high_resolution_clock> en;
  en = std::chrono::high_resolution_clock::now();
  return (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(en-st).count();

}

// time_start starts timer to record duration (nanoseconds).
void Timer::time_start() {
  st = std::chrono::high_resolution_clock::now();
}



