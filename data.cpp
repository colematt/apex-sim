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

  //Display first 100 non-zero contents of memory
  void Data::display(){
    int i = 0 ;
    int col = 0 ;
    int nz = 0;

    while (nz < 100){
      //Print one row of four memory-addressable locations
      std::cout << i << ": ";
      for (col = 0; col < 4; col++){
        //print out Memory[i+col] followed by a tab
        std::cout << this->readMem(i) << "\t";
        //if Memory[i+col] != 0, increment nz
        if (this->readMem(i) != 0)
          nz++;

        //Move to next column  
        col++;
      } //end for (print one row)

      //Print out line break
      std::cout << std::endl;

      //Increment line address
      i += 4;
    } //end while
  } //end display()
