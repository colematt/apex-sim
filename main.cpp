/* FILE INFORMATION
File:     main.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Driver for apex-sim. Contains functions controlling simulator high-level behavior.
*/
#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std;

// Initialize the simulator to a known state. Optionally zero the memory text file, representing a format of the memory)
void initialize(bool zero=false)
{
  cout << "initialize()" << endl;
}

// Display the simulator internal state.
void display()
{
  cout << "display()" << endl;

  //Call to cpu::display()
  //Call to register::display()
  //Call to memory::display()

}

// Simulate the operation of the system for n cycles or until a HALT instruction is encountered. Optionally display the simulator internal state every <display> cycles. If <display> is not positive, the internal state is not displayed.
void simulate(int n, int display=0)
{

}

int main(int argc, char** argv)
{

  return 0;
}
