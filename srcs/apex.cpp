/* FILE INFORMATION
File:     apex.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains helper functions controlling simulator high-level behavior.
*/
#include <iostream>
#include <string>
#include "code.h"
#include "cpu.h"
#include "data.h"
#include "register.h"
#include "apex.h"

// Initialize simulator state and stats variables with external linkage
int cycle = 0;
int pc = 4000;
int dispatched = 0;
int no_dispatch = 0;
int issued = 0;
int no_issued = 0;
int resolved = 0;
int committed = 0;
int committed_load = 0;
int committed_store = 0;

//Display an interface help message
void help()
{
  std::cout << "Command        | Action\n"
            << "---------------|---------------------------------------------\n"
            << "i              |Initialize the simulator state\n"
            << "s <n>          |Simulate <n> number of cycles\n"
            << "d              |Display the simulator internal state\n"
            << "dmt            |Display Front Rename and Back Register Alias tables\n"
            << "diq            |Display Issue Queue entries and status\n"
            << "drob           |Display ROB contents\n"
            << "dmem <a1> <a2> |Display memory from address <a1> to <a2>\n"
            << "dstats         |Display Stats\n"
            << "urf <n>        |Set URF Size to <n> physical registers\n"
            << "q              |Quit the simulator\n"
            << "h              |Display this help message" << std::endl;
}

// Initialize the simulator to a known state.
void initialize(CPU &mycpu, Registers &myregisters, Data &mydata)
{
  if (VERBOSE >= 1)
    std::cout << "Initializing ... " << std::endl;

  //Reset simulator state and stats variables
  cycle = 0;
  pc = 4000;
  dispatched = 0;
  no_dispatch = 0;
  issued = 0;
  no_issue = 0;
  resolved = 0;
  committed = 0;
  committed_load = 0;
  committed_store = 0;

  //Initialize each of the instances by delegating to member functions
  mycpu.initialize();
  myregisters.initialize();
  mydata.initialize();
}

// Display the simulator internal state.
void display(CPU &mycpu, Registers &myregisters, Data &mydata)
{
  if (VERBOSE >= 1)
    std::cout << "Displaying simulator state ... " << std::endl;

  //Print simulator state variables
  std::cout << "cycle: " << cycle << " pc: " << pc << std::endl;

  //Display each of the instances by delegating to member functions
  std::cout << "-----------\n" << "CPU\n" << "-----------\n";
  mycpu.display();

  std::cout << "-----------\n" << "Registers\n" << "-----------\n";
  myregisters.display();

  std::cout << "-----------\n" << "Data Memory\n" << "-----------\n";
  mydata.display();
}

//Display simulator stats
void stats()
{
  std::cout << "-----------\n" << "Statistics\n" << "-----------\n";
  std::cout << "Cycle: " << cycle << std::endl;
  std::cout << "Instructions through:\n"
            << " Dispatch=" << dispatched
            << " Issue=" << issued
            << " Resolution=" << resolved
            << " Commit=" << committed << std::endl;

  std::cout << "IPC: " << ((double) committed + (double) resolved) / (double) cycles << std::endl;
  std::cout << "# cycles dispatch stalled: " << no_dispatch << std::endl;
  std::cout << "# cycles with no issue: " << no_issue << std::endl;
  std::cout << "# LOAD instructions committed: " << committed_load << std::endl;
  std::cout << "# STORE instructions committed: " << committed_store << std::endl;
}
// Simulate the operation of the system for <num_cycles>, or until a HALT
//instruction is encountered, or until an error occurs in simulation.
//Return the current cycle number after simulation pauses or halts.
int simulate(int num_cycles, CPU &apexCPU, Code &apexCode, Registers &apexRF, Data &apexData)
{
  for (int c = cycle; c < num_cycles; c++)
  {
    //Perform one cycle of simulation
    if (VERBOSE >= 1)
      std::cout << "Simulating cycle " << cycle << " ..." << std::endl;

    //cpu::simulate() returns 0 if execution should not continue
    //(EOF, HALT or exception encountered)
    if(!(apexCPU.simulate(apexCode, apexRF, apexData))){
      std::cout << "Simulator HALT encounted on cycle " << cycle << std::endl;
      quit(apexCPU, apexRF, apexData);
      return 0;
    }

    if(VERBOSE >= 2){
	    apexCPU.display();
	    apexRF.display();
	}

    //Cycle complete, increment the global cycle counter
    cycle++;
  }

  return cycle;
}

//Quit the simulator
void quit(CPU &mycpu, Registers &myregisters, Data &mydata)
{
  if (VERBOSE >= 1)
    std::cout << "Quitting simulator ..." << std::endl;
  display(mycpu, myregisters, mydata);
}
