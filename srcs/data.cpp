/* FILE INFORMATION
File:     data.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the DATA class, which simulates reading and writing main memory
*/

#include "data.h"
#include <iostream>

  Data::Data(){ //initialize the memory with all positions set to zero
    this->initialize();
  }

  Data::~Data(){
  	
  }

  //Initialize vector size and vector positions
  void Data::initialize(){
    memory.resize(4000);

    for (int i = 0; i < memory.size(); i++){
      memory.at(i) = 0;
    }
  }

  //Read four bytes from memory starting at address <addr>
  int Data::readMem(int addr){
    return memory.at(addr);
  }

  //Write four bytes to memory starting at <addr>
  void Data::writeMem(int addr, int value){
    memory.at(addr) = value;
  }

  //Display first 100 non-zero contents of memory
  void Data::display(){
    int i = 0 ;
    int col = 0 ;
    int nz = 0;

    while (nz < 100 && i <= 3996){
      //Print one row of four memory-addressable locations
      std::cout << i << ": ";
      for (col = 0; col < 4; col++){
        //print out Memory[i+col] followed by a tab
        std::cout << this->readMem(i+col) << "\t";

        //if Memory[i+col] != 0, increment nz
        if (this->readMem(i+col) != 0)
          nz++;
      } //end for (print one row)

      //Print out line break
      std::cout << std::endl;

      //Increment line address
      i += 4;
    } //end while
  } //end display()