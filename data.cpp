/* FILE INFORMATION
File:     data.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the DATA class, which simulates reading and writing main memory
*/

#include "data.h"

  //Read one byte-address from memory at <addr>
  int Data::readMem(int addr){
    return memory.at(addr);
  }

  //Write one byte to memory at <addr>
  void Data::writeMem(int addr, short value){
    memory.at(addr) = value;
  }

  //Display contents of memory beginning at <startAddr>
  //and ending at <endAddr>, inclusive
  //If <endAddr> < <startAddr>, return silently.
  void Data::display(int startAddr, int endAddr){
    int index;

    if (startAddr <= endAddr){
      index = startAddr;

      while (index <= endAddr){
        cout << "Memory address " << index << " value " << memory.at(index) << endl;
      }
    }
  }