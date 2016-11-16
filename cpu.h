/* FILE INFORMATION
File:     cpu.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file for cpu.cpp
*/

#include "data.h"
#include "register.h"
#include "code.h"
#include "stage.h"

#ifndef CPU_H
#define CPU_H

class CPU {
private:
	
  
public:
  CPU();
  void initialize();
  void display();
  int simulate(Code &mycode, Registers &myregisters, Data &mydata);
};

#endif
