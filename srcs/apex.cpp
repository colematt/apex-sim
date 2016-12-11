/* FILE INFORMATION
File:     apex.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains helper functions controlling simulator high-level behavior.
*/
#include <iostream>
#include "code.h"
#include "cpu.h"
#include "data.h"
#include "register.h"
#include "rob.h"
#include "iq.h"
#include "apex.h"

// Initialize simulator state and stats variables with external linkage
int cycle = 0;
int pc = 4000;
int dispatched = 0;
int no_dispatch = 0;
int issued = 0;
int no_issued = 0;
int committed = 0;
int committed_load = 0;
int committed_store = 0;
int no_commit= 0;

// Initialize simulator flags
int Z = 0;
int Zcycle = 0;

//Display an interface help message
void help()
{
  std::cout << "Command         | Action\n"
            << "----------------|---------------------------------------------\n"
            << "i               |Initialize the simulator state\n"
            << "s <n>           |Simulate <n> number of cycles\n"
            << "d all           |Display the full simulator internal state\n"
            << "d cpu           |Display CPU stage contents\n"
            << "d iq            |Display Issue Queue entries and status\n"
            << "d map           |Display Front-end and Back-end Register Tables\n"
            << "d mem <a1> <a2> |Display memory from address <a1> to <a2>\n"
            << "d rob           |Display ROB contents\n"
            << "d stats         |Display Stats\n"
            << "d urf           |Display Unified Register File\n"
            << "urf <n>         |Set URF Size to <n> physical registers\n"
            << "q               |Quit the simulator\n"
            << "h               |Display this help message" << std::endl;
}

// Initialize the simulator to a known state.
void initialize(CPU &mycpu, Registers &myregisters, Data &mydata, ROB &myrob, IQ &myiq)
{
  if (VERBOSE >= 1)
    std::cout << "Initializing ... " << std::endl;

  //Reset simulator state and stats variables
  cycle = 0;
  pc = 4000;
  dispatched = 0;
  no_dispatch = 0;
  issued = 0;
  no_issued = 0;
  committed = 0;
  committed_load = 0;
  committed_store = 0;

  //Initialize each of the instances by delegating to member functions
  mycpu.initialize();
  myregisters.initialize();
  mydata.initialize();
} //end initialize()

// Display the simulator internal state.
void display(CPU &mycpu, Registers &myregisters, Data &mydata, ROB &myrob, IQ &myiq,
  std::string mod, int a1, int a2)
{
  //Sanitize inputs
  if  (mod != "all" &&
        mod != "cpu" &&
        mod != "iq"  &&
        mod != "map" &&
        mod != "mem" &&
        mod != "rob" &&
        mod != "stats" &&
        mod != "urf"){
            std::cerr << "Display modifier " << mod << " not understood.";
            mod = "";
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
  if (mod == "all" || mod == "iq"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "Issue Queue\n" << "-----------\n";
    myiq.display();
  }
  if (mod == "all" || mod == "map"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "Rename Tables\n" << "-----------\n";
    myregisters.dMap();
  }
  if (mod == "all" || mod == "mem"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "Data Memory\n" << "-----------\n";
    mydata.display(a1, a2);
  }
  if (mod == "all" || mod == "rob"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "Reorder Buffer\n" << "-----------\n";
    myrob.display();
  }
  if (mod == "all" || mod == "stats"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "Statistics\n" << "-----------\n";
    stats();
  }
  if (mod == "all" || mod == "urf"){
    if (VERBOSE >= 1)
      std::cout << "-----------\n" << "Registers\n" << "-----------\n";
    myregisters.dUrf();
  }
} // end display()

//Display simulator stats
void stats()
{
  std::cout << "-----------\n" << "Statistics\n" << "-----------\n";
  std::cout << "Cycle: " << cycle << std::endl;
  std::cout << "Instructions through:\n"
            << " Dispatch=" << dispatched
            << " Issue=" << issued
            << " Commit=" << committed << std::endl;

  std::cout << "IPC: " << ((double) committed) / (double) cycle << std::endl;
  std::cout << "# cycles dispatch stalled: " << no_dispatch << std::endl;
  std::cout << "# cycles with no issue: " << no_issued << std::endl;
  std::cout << "# LOAD instructions committed: " << committed_load << std::endl;
  std::cout << "# STORE instructions committed: " << committed_store << std::endl;
  std::cout << "# cycles with no commit: " << no_commit << std::endl;
}

// Simulate the operation of the system for <num_cycles>, or until a HALT
//instruction is encountered, or until an error occurs in simulation.
//Return the current cycle number after simulation pauses or halts.
int simulate(int num_cycles, CPU &mycpu, Code &mycode, Registers &myregisters,
  Data &mydata, ROB &myrob, IQ &myiq)
{
  int start = ::cycle;
  int stop = ::cycle + num_cycles;
  
  for (int c = start; c < stop; c++)
  {
    //Perform one cycle of simulation
    if (VERBOSE >= 1)
      std::cout << "Simulating cycle " << cycle << " ..." << std::endl;

    //cpu::simulate() returns 0 if execution should not continue
    //(EOF, HALT or exception encountered)
    if(!(mycpu.simulate(mycode, myregisters, mydata, myrob, myiq))){
      std::cout << "Simulator HALT encounted on cycle " << cycle << std::endl;
      quit(mycpu, myregisters, mydata, myrob, myiq);
      return 0;
    }

    if(VERBOSE >= 2){
	    mycpu.display();
	    myregisters.display();
	  }
  }

  return cycle;
}

//Quit the simulator
void quit(CPU &mycpu, Registers &myregisters, Data &mydata, ROB &myrob, IQ &myiq)
{
  if (VERBOSE >= 1)
    std::cout << "Quitting simulator ..." << std::endl;
  display(mycpu, myregisters, mydata, myrob, myiq, "all", 0, 100);
}
