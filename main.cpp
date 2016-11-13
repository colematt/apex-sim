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
#include "instruction.h"
#include "register.h"

#define VERBOSE 1

using namespace std;

//Simulator variables with external linkage
static int cycle; //simulator's current cycle
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
void initialize()
{
  if (VERBOSE)
    cout << "Initializing ... " << endl;
  //TODO Call to data::initialize()
  //TODO Call to registers::initialize()
  //TODO Call to cpu::initialize()
}

// Display the simulator internal state.
void display()
{
  if (VERBOSE)
    cout << "Displaying simulator state ... " << endl;
  //TODO Call to cpu::display()
  //TODO Call to registers::display()
  //TODO Call to data::display()
  //TODO Call to code::display()
}

// Simulate the operation of the system for <num_cycles>, or until a HALT
//instruction is encountered, or until an error occurs in simulation.
//Return the current cycle number after simulation pauses or halts.
int simulate(int num_cycles)
{
  for (int c = cycle; c < cycle + num_cycles; c++)
  {
    //Perform one cycle of simulation
    if (VERBOSE)
      cout << "Simulating cycle " << cycle << " ..." << endl;

    //cpu::simulate() returns 0 if execution should not continue
    //(EOF, HALT or exeception encountered)
    //if(!cpu::simulate())
    //  break;

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

  //Perform entry actions
  cycle = 0;

  //TODO Instantiate Simulator classes

  //Set up simulator command interface
  string command = "h"; //interface switch statement selector
  int n = 1; // number of cycles or addresses modifier

  /****** USER INTERFACE ******/
  while (command != "q") {
    //On first execution of the interface, display the help message
    if (cycle == 0)
      help();

    //Get the next command. If command takes the n parameter, ingest it also
    cin >> command;
    if (command == "s")
      cin >> n;

    char selectCom = command[0];
    //Perform appropriate action based on the command / parameter
    switch (command[0]) {
      case 'i':
        initialize();
        break;
      case 's':
        simulate(n);
        break;
      case 'd':
        display();
        break;
      case 'q': //quitting causes no action except to conclude this function
        break;
      case 'h': //Falls through to default (which prints the help message)
      default: //Input wasn't recognized
        help();
        break;
    }
  } // End User Interface

  //TODO Perform any exiting actions?

  return 0;
}
