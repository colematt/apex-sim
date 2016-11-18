/* FILE INFORMATION
File:     main.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Driver for apex-sim. Contains functions controlling simulator high-level behavior.
*/
#include <iostream>
#include <string>
#include "code.h"
#include "cpu.h"
#include "data.h"
#include "register.h"
#include "apex.h"

#define VERBOSE 1

using namespace std;

//Simulator variables with external linkage
int cycle = 0; //simulator cycle current value
int pc = 4000;    //program counter current value
static const char* instFile; //instruction input file

//Display an interface help message
void help()
{
  cout << "[i]   Initialize the simulator state" << endl;
  cout << "[s n] Simulate <n> number of cycles" << endl;
  cout << "[d n] Display the simulator internal state" << endl;
  cout << "[q]   Quit the simulator" << endl;
  cout << "[h]   Display a help message" << endl;
}

// Initialize the simulator to a known state.
void initialize(CPU &mycpu, Registers &myregisters, Data &mydata)
{
  if (VERBOSE)
    cout << "Initializing ... " << endl;

  //Reset simulator state variables
  cycle = 0;
  pc = 4000;

  //Initialize each of the instances by delegating to member functions
  mycpu.initialize();
  myregisters.initialize();
  mydata.initialize();
}

// Display the simulator internal state.
void display(CPU &mycpu, Registers &myregisters, Data &mydata)
{
  if (VERBOSE)
    cout << "Displaying simulator state ... " << endl;

  //Print simulator state variables

  //Display each of the instances by delegating to member functions
  cout << "-----------\n" << "CPU" << "-----------\n";
  mycpu.display();

  cout << "-----------\n" << "Registers" << "-----------\n";
  myregisters.display();

  cout << "-----------\n" << "Data Memory" << "-----------\n";
  mydata.display();
}

//Quit the simulator
void quit(CPU &mycpu, Registers &myregisters, Data &mydata){
  if (VERBOSE)
    cout << "Displaying final state and quitting simulator ..." << endl;
  display(mycpu, myregisters, mydata);
}

// Simulate the operation of the system for <num_cycles>, or until a HALT
//instruction is encountered, or until an error occurs in simulation.
//Return the current cycle number after simulation pauses or halts.
int simulate(int num_cycles, CPU &apexCPU, Code &apexCode, Registers &apexRF, Data &apexData)
{
  for (int c = cycle; c < num_cycles; c++)
  {
    //Perform one cycle of simulation
    if (VERBOSE)
      cout << "Simulating cycle " << cycle << " ..." << endl;

    //cpu::simulate() returns 0 if execution should not continue
    //(EOF, HALT or exception encountered)
    if(!(apexCPU.simulate(apexCode, apexRF, apexData))){
      cout << "Simulator HALT encounted on cycle " << cycle << endl;
      quit(apexCPU, apexRF, apexData);
      return 0;
    }

    apexCPU.display();
    apexRF.display();

    //Cycle complete, increment the global cycle counter
    cycle++;
  }

  return cycle;
}

int main(int argc, char** argv)
{
  //Command line program options handling
  //Check if user needs a usage message
  if (argc != 2) {
    cout << "USAGE: apex-sim <instructions file>" << endl;
    exit(0);
  }
  else {
    //User didn't need a usage message. Capture filenames
    instFile = (const char*) argv[1];
  }

  //Instantiate Simulator classes
  Code *apexCode = new Code(instFile);
  Registers *apexRF = new Registers();
  Data *apexData = new Data();
  CPU *apexCPU = new CPU(*apexCode, *apexRF, *apexData);

  //Perform first initialization
  initialize(*apexCPU, *apexRF, *apexData);

  //Set up simulator command interface
  string command = "h"; //interface switch statement selector
  int n = 1; // number of cycles or addresses modifier

/******************************************************************************/
/**************************USER INTERFACE *************************************/
/******************************************************************************/
  while (command != "q") {
    //On first execution of the interface, display the help message
    if (cycle == 0)
      help();

    //Get the next command. If command takes the n parameter, ingest it also
    cin >> command;
    if (command == "s")
      cin >> n;

    //Perform appropriate action based on the command / parameter
    switch (command[0]) {
      case 'i':
        initialize(*apexCPU, *apexRF, *apexData);
        break;
      case 's':
        simulate(n, *apexCPU, *apexCode, *apexRF, *apexData);
        break;
      case 'd':
        display(*apexCPU, *apexRF, *apexData);
        break;
      case 'q': //simulator can quit by user selection or encountering HALT
        quit(*apexCPU, *apexRF, *apexData);
        break;
      case 'h': //Falls through to default (which prints the help message)
      default: //Input wasn't recognized
        help();
        break;
    }
  } // End User Interface
  return 0;
}
