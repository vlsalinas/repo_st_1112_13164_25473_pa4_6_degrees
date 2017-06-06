#include <iostream>
#include <sstream>
#include <ostream>
#include <vector>
#include <string>
#include "util.h"

using std::istream;
using std::istringstream;
using std::string;
using std::vector;
/*
 * Starts the timer. Saves the current time.
 */
void Timer::time_start() {
  st = std::chrono::high_resolution_clock::now();
}

/*
 * Ends the timer. Compares end time with the start time and returns number of nanoseconds
 */
long long Timer::time_end() {
  std::chrono::time_point<std::chrono::high_resolution_clock> en;
  en = std::chrono::high_resolution_clock::now();
  return (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(en-st).count();

}

