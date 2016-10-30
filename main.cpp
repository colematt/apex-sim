/* FILE INFORMATION
File:     main.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Driver for apex-sim. Contains functions controlling simulator high-level behavior.
*/
#include <iostream>

using namespace std;

//Simulator variables with external linkage
extern int cycle = 0;
extern string codeFile;
extern string memFile;

// Initialize the simulator to a known state.
// Optionally <format> the memory text file.
void initialize(bool format=false)
{
  cout << "initialize()" << endl;
  //Create instance of the MMU
  //Create instance of the Register File
  //Create instances of the CPU function units

  //Initialize memory text file
  if (format)
    cout << "Zeroing memory source file..." << endl;
}

// Display the simulator internal state.
void display()
{
  cout << "display()" << endl;
  //Call to cpu::display()
  //Call to register::display()
  //Call to memory::display()
}

// Simulate the operation of the system for n cycles or until a HALT instruction is encountered. Optionally display the simulator internal state every <display> cycles. If <display> is zero, the internal state is not displayed.
void simulate(int n, unsigned int display=0)
{
  int start = cycle;
  int stop = cycle + n;

  for (int c = start; c < stop; c++)
  {
    //Perform one cycle of simulation
    cout << "simulate()" << endl;
    //Call to cpu::simulate()

    //Determine whether the machine state should be displayed
    if (display && ((c - start) % display == 0))
      display();

    //Cycle complete, increment the global cycle counter
    cycle++;
  }
}

int main(int argc, char** argv)
{
  //Command line program options handling

  //Simulator Command Interface

  return 0;
}
