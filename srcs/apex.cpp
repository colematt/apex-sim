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
  std::cout << "Command         | Action\n"
            << "----------------|---------------------------------------------\n"
            << "i               |Initialize the simulator state\n"
            << "s <n>           |Simulate <n> number of cycles\n"
            << "d all           |Display the full simulator internal state\n"
            << "d cpu           |Display CPU stage contents\n"
            << "d rt            |Display Front-end and Back-end Register Tables\n"
            << "d iq            |Display Issue Queue entries and status\n"
            << "d rob           |Display ROB contents\n"
            << "d mem <a1> <a2> |Display memory from address <a1> to <a2>\n"
            << "d stats         |Display Stats\n"
            << "urf <n>         |Set URF Size to <n> physical registers\n"
            << "q               |Quit the simulator\n"
            << "h               |Display this help message" << std::endl;
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
} //end initialize()

// Display the simulator internal state.
// TODO: Add more pass-by-reference arguments, to IQ, ROB classes?
void display(CPU &mycpu, Registers &myregisters, Data &mydata, string mod, int a1=0, int a2=3996)
{
  //Sanitize inputs
  if  !(mod == "all" ||
        mod == "cpu" ||
        mod == "rt"  ||
        mod == "iq"  ||
        mod == "rob" ||
        mod == "mem" ||
        mod == "stats"){
            std::cerr << "Display modifier " << mod << " not understood."
            mod = "none";
        }
  }
  if ((mod == "all" || mod == "mem") && a1 < 0){
    std::cerr << "Memory range start is out of bounds. Setting to 0." << std::endl;
    a1 = 0;
  }
  if ((mod == "all" || mod == "mem") && a2 > 3996){
    std::cerr << "Memory range stop is out of bounds. Setting to 3996." << std::endl;
    a2 = 3996;
  }
  if ((mod == "all" || mod == "mem") && (a1 > a2)){
    //We assert a1 <= a2. Swap a1, a2 if assertion is false.
    a1 = a1 ^ a2;
    a2 = a1 ^ a2;
    a1 = a1 ^ a2;
  }

  if (VERBOSE >= 1)
    std::cout << "Displaying simulator state ... " << std::endl;

  //Print simulator state variables
  std::cout << "cycle: " << cycle << " pc: " << pc << std::endl;

  //Display each of the instances by delegating to member functions
  if (mod == "all" || mod == "cpu"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "CPU\n" << "-----------\n";
    mycpu.display();
  }
  if (mod == "all" || mod == "rt"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "Registers\n" << "-----------\n";
    myregisters.display();
  }
  if (mod == "all" || mod == "iq"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "Issue Queue\n" << "-----------\n";
    //TODO: Add call to IQ::display() function
  }
  if (mod == "all" || mod == "rob"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "Reorder Buffer\n" << "-----------\n";
    //TODO: Add call to ROB::display() function
  }
  if (mod == "all" || mod == "mem"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "Data Memory\n" << "-----------\n";
    mydata.display(a1, a2);
  }
  if (mod == "all" || mod == "stats"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "Statistics\n" << "-----------\n";
    stats();
  }
} // end simulate()

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
