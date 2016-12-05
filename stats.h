/* FILE INFORMATION
File:     stats.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Provides statistics tracking and computation for apex-sim
*/

#ifndef STATS_H
#define STATS_H

class Stats {
private:

public:

  //Data members
  unsigned int cycle;           // number of cycles simulated
  unsigned int dispatched;      // number of instructions dispatched to IQ
  unsigned int no_dispatched;   // number of cycles with no dispatch to IQ
  unsigned int issued;          // number of instructions issued to any FU
  unsigned int no_issued;       // number of cycles with no instructions issued
  unsigned int resolved;        // number of instructions resolved from B FU
  unsigned int committed;       // number of instructions committed from ROB
  unsigned int load_committed;  // number of LOAD instructions committed
  unsigned int store_committed; // number of STORE instructions committed

  Stats ();
  ~stats ();

  // Reset all stats counters
  void initialize();

  // Display all stats
  void display();

  // Statistics getters
  double ipc(); // Instructions per Cycle
  unsigned int stalled();       // Number of cycles dispatch stalled
  unsigned int no_issue();      // Number of cycles with no issue to an FU
  unsigned int load_commit();   // Number of LOAD instructions committed
  unsigned int store_commit();  // Number of STORE instructions committed

};

#endif
