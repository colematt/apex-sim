/* FILE INFORMATION
File:     main.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Driver for apex-sim. Contains functions controlling simulator high-level behavior.
*/
#include <iostream>
#include <string.h>

using namespace std;

//Simulator variables with external linkage
extern int cycle = 0; //simulator's current cycle
extern const char* instFile; //instruction input file

// Initialize the simulator to a known state.
void initialize()
{
  cout << "initialize()" << endl;
  //TODO Call to data::initialize()
  //TODO Call to registers::initialize()
  //TODO Call to cpu::initialize()
}

// Display the simulator internal state.
void display(int start=0, int stop=0)
{
  cout << "display()" << endl;
  //TODO Call to cpu::display()
  //TODO Call to registers::display()
  //TODO Call to data::display(start,stop)
  //TODO Call to code::display()
}

// Simulate the operation of the system for <num_cycles> or until a HALT instruction is encountered. Optionally display the simulator internal state every <disp_cycles> cycles. If <disp_cycles> is zero, the internal state is not displayed.
void simulate(int num_cycles, unsigned int disp_cycles=0)
{
  int start = cycle;
  int stop = cycle + num_cycles;

  for (int c = start; c < stop; c++)
  {
    //Perform one cycle of simulation
    cout << "simulate()" << endl;
    //if(!cpu::simulate()) // simulate returns 0 if execution should not continue (EOF or HALT encountered)
    //  break;

    //Determine whether the machine state should be displayed
    if (display && ((c - start) % display == 0))
      display();

    //Cycle complete, increment the global cycle counter
    cycle++;
  }
}

// Provide the simulator's command interface
void interface(string command, int n=1, int d=0)
{
  switch (command) {
    case "i":
      initialize();
      break;
    case "s":
      simulate(n, d);
      break;
    case "d":
      display(n);
      break;
    case "q":
      break;
    case "h": //falls through to default (which prints the help message)
    default:
      cout << "[i]                        (I)nitialize the simulator state" << endl;
      cout << "[s num_cycles disp_cycles] (S)imulate the number of cycles specified by <n>," << endl;
      cout << "                               displaying contents every <disp_cycles> cycles" << endl;
      cout << "[d num_addr]               (D)isplay the contents of each stage in the pipeline," << endl;
      cout << "                               registers/flags, and the first <num_addr> memory " <<endl;
      cout << "                               locations containing data" << endl;
      cout << "[q]                        (Q)uit the simulator" << endl;
      cout << "[h]                        (H)elp message (repeat this information)" << endl;
      break;
  }
}

int main(int argc, char** argv)
{
  //Command line program options handling
  //Check if user needs a usage message
  if (argc == 1) {
    cout << "USAGE: apex-sim [-h|--help] <instructions file>" << endl;
    exit(0);
  }
  else if (!strcmp(argv[1], "-h") || !strcmp(argv[1],"--help")) {
        cout << "USAGE: apex-sim [-h|--help] <instructions file>" << endl;
        exit(0);
      }
    }
  }

  //User didn't need a usage message. Capture filenames
  instFile = (const char*) argv[1];

  //TODO: Instantiate Simulator classes

  //Set up simulator command interface
  string command = "h"; //interface switch statement selector
  int n = 1; // number of cycles or addresses modifier
  int d = 0; // cycle display interval modifier

  while (command != "q") {
    //Get the next command
    cin >> command;

    //Simulate
    if (command == "s") {
      cin >> n >> d;
      interface(command, n, d);
    }
    //Display
    else if (command == "d") {
      cin >> n;
      interface(command, n);
    }
    //Initialize, Quit, or Help
    else {
      interface(command)
    }
  }

  return 0;
}
