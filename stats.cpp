/* FILE INFORMATION
File:     stats.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Provides statistics tracking and computation for apex-sim
*/

#include "stats.h"

Stats::Stats (){
  this->initialize();
}
Stats::~stats ();

// Reset all stats counters
void Stats::initialize(){
  this.cycle = 0;
  this.dispatched = 0;
  this.no_dispatched = 0;
  this.issued = 0;
  this.no_issued = 0;
  this.resolved = 0;
  this.committed = 0;
  this.load_committed = 0;
  this.store_committed = 0;
}

// Display all stats
void Stats::display(){
  std::cout << "Cycle: " << this.cycle << std::endl;
  std::cout << "IPC: " << this->ipc() << std::endl;
  std::cout << "Instructions through:\n"
            << " Dispatch=" << this.dispatched
            << " Issue=" << this.issue
            << " Resolution=" << this.resolved
            << " Commit=" << this.committed << std::endl;

  std::cout <<"# cycles dispatch stalled: " << this->stalled() << std::endl;
  std::cout <<"# cycles with no issue: " << this->no_issue() << std::endl;
  std::cout <<"# LOAD instructions committed: " << this->load_commit() << std::endl;
  std::cout <<"# STORE instructions committed: " << this->store_commit() << std::endl;
}

// Statistics getters
double Stats::ipc(){
  return ((double) committed + (double) resolved) / ((double) cycles);
}

unsigned int Stats::stalled(){
  return this.no_dispatched;
}
unsigned int Stats::no_issue(){
  return this.no_issued;
}
unsigned int Stats::load_commit(){
  return this.load_committed;
}
unsigned int Stats::store_commit(){
  return this.store_committed;
}
