/* FILE INFORMATION
File:     main.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Driver for apex-sim. Contains functions controlling simulator high-level behavior.
*/
#include <iostream>
#include <string.h>

#define VERBOSE 1

using namespace std;

//Simulator variables with external linkage
extern int cycle = 0; //simulator's current cycle
extern const char* instFile; //instruction input file

//Display an interface help message
void help()
{
  cout << "[i]   Initialize the simulator state" << endl;
  cout << "[s n] Simulate the number of cycles specified by <n>," << endl;
  cout << "      displaying contents every <disp_cycles> cycles" << endl;
  cout << "[d n] Display the contents of each stage in the pipeline," << endl;
  cout << "      registers/flags, and the first <num_addr> memory " <<endl;
  cout << "      locations containing data" << endl;
  cout << "[q]   Quit the simulator" << endl;
  cout << "[h]   Help message (repeat this information)" << endl;
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

  //TODO Perform entry actions?

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

    //Perform appropriate action based on the command / parameter
    switch (command) {
      case "i":
        initialize();
        break;
      case "s":
        simulate(n);
        break;
      case "d":
        display();
        break;
      case "q": //quitting causes no action except to conclude this function
        break;
      case "h": //Falls through to default (which prints the help message)
      default: //Input wasn't recognized
        help();
        break;
  } // End User Interface

  //TODO Perform exiting actions?
  return 0;
}
