/* FILE INFORMATION
File:     main.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Driver for apex-sim.
*/
#include <iostream>
#include <string>
#include "code.h"
#include "cpu.h"
#include "data.h"
#include "register.h"
#include "apex.h"

using namespace std;

//Simulator variables without external linkage
static const char* instFile; //instruction input file

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
  int n = 1; // number of cycles modifier
  int a1, a2 = 0; //address bounds modifier

  //Run user interface
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
