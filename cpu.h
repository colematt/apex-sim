/* FILE INFORMATION
File:     cpu.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file for cpu.cpp
*/

#include "stage.h"
#include "data.h"
#include "register.h"
#include "code.h"

#ifndef CPU_H
#define CPU_H

class CPU {
private:

	Stage F;      //Fetch stage
  	Stage DRF;    //Decode/Reg File stage
 	Stage ALU1;   //ALU 1st stage
  	Stage ALU2;   //ALU 2nd stage
  	Stage B;      //Branch stage
  	Stage D;		//(Branch) Delay stage
  	Stage M;      //Memory stage
  	Stage WB;     //Write Back stage
  
public:
  CPU(Code &mycode, Registers &myregisters, Data &mydata);
  void initialize();
  void display();
  int simulate(Code &apexCode, Registers &apexRF, Data &apexData);
};

#endif
