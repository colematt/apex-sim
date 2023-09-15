/* FILE INFORMATION
File:     main.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Driver for apex-sim.
*/
#include <algorithm>
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

  // Instantiate Simulator classes
  Code *apexCode = new Code(instFile);
  Registers *apexRF = new Registers();
  Data *apexData = new Data();
  CPU *apexCPU = new CPU(*apexCode, *apexRF, *apexData);
  ROB *apexROB = new ROB();
  IQ *apexIQ = new IQ();

  // Perform first initialization
  initialize(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ);

/**** User Interface ***********************************************************
********************************************************************************
*******************************************************************************/
  // User interface variables
  string cmd;
  int n, a1, a2;
  n = a1 = a2 = 0;

  //On first pass through the interface, display help
  help();

  //Iterate until the user calls quit option
  while (true) {
    //Reset parameter variables
    n = a1 = a2 = 0;

    // Get the next command.
    cout << "apex-sim $ ";
    cin >> cmd;

    //lowercase input strings
    //std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

    // Validate the input
    if (cmd != "i" && cmd != "s" &&
        cmd != "dall" && cmd != "dcpu" && cmd != "diq" && cmd != "dmap" &&
        cmd != "dmem" && cmd != "drob" && cmd != "dstats" && cmd != "durf" &&
        cmd != "urf" && cmd != "q" && cmd != "h"){
          //user has failed to provide a valid input, try again
          cerr << "Did not understand command " << cmd << endl;
          help();
          continue;
    }

    //Process the command. If command takes additional parameters, ingest them.
    if (cmd == "i") {
      initialize(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ);
    }
    else if (cmd== "s"){
      cin >> n;
      simulate(n, *apexCPU, *apexCode, *apexRF, *apexData, *apexROB, *apexIQ);
    }
    else if (cmd == "dall"){
      a1 = 0; a2 = 100;
      display(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ, "all", a1, a2);
    }
    else if (cmd == "dcpu"){
      display(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ, "cpu");
    }
    else if (cmd == "diq"){
      display(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ, "iq");
    }
    else if (cmd == "dmap"){
      display(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ, "map");
    }
    else if (cmd == "dmem"){
      cin >> a1 >> a2;
      display(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ, "mem", a1, a2);
    }
    else if (cmd == "drob"){
      display(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ, "rob");
    }
    else if (cmd == "dstats"){
      display(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ, "stats");
    }
    else if (cmd == "durf"){
      display(*apexCPU, *apexRF, *apexData, *apexROB, *apexIQ, "urf");
    }
    else if (cmd == "urf"){
      cin >> n;
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
    else{}
  } // End User Interface while-loop

  return 0;
}
