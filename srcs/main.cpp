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
  ROB *apexROB = new ROB();
  IQ *apexIQ = new IQ();

  //Perform first initialization
  initialize(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ);

  //Set up simulator command interface
  string cmd; //interface switch statement selector
  string mod; //the "d" command takes a modifier
  int n, a1, a2; // number of cycles modifier

  //Run user interface
  while (true) {
    //On first execution of the interface, display the help message
    if (cycle == 0)
      help();

    //Get the next command. If command takes the n parameter, ingest it also
    cin >> cmd;

    //Process the command. If command takes additional parameters, ingest them.
    if (cmd == "i") {
      initialize(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ);
    }
    else if (cmd== "s"){
      cin >> n;
      simulate(n, *apexCPU, *apexCode, *apexRF, *apexData, *apexROB, *apexIQ);
    }
    else if (cmd == "d"){
      //Ingest modifiers
      cin >> mod;

      if (mod == "mem"){
        cin >> a1 >> a2;
        //Display memory
        display(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ, mod, a1, a2);
      }else {
        //Display memory
        display(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ, mod);
      }
    }
    else if (cmd == "urf"){
      //Ingest modifier
      cin >> n;
      //Set URF size
      if (VERBOSE >= 1)
        std::cout << "Setting URF Size to " << n << " registers ... " << std::endl;
      apexRF->setNumReg(n);
    }
    else if (cmd == "q"){
      quit(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ);
      break;
    }
    else if (cmd == "h"){
      help();
    }
    else{
      std::cerr << "Did not understand " << cmd << " !" << std::endl;
      help();
    }
  } // End User Interface while-loop

  return 0;
}
