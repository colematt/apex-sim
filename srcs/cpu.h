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
#include "rob.h"
#include "iq.h"

#ifndef CPU_H
#define CPU_H



class CPU {
	private:
		bool is_halting; //See STOPPING phase in CPU::Simulate() for explanation

		Stage F;      	//Fetch stage
		Stage DRF1;  	//Rename stage
		Stage DRF2;  	//Dispatch stage
		Stage ALU1; 	//ALU 1st stage
		Stage ALU2;   	//ALU 2nd stage
		Stage ALU3;     //ALU WB stage
		Stage MUL1;		//MUL 4-cycle stage
		Stage MUL2;		//MUL WB stage
		Stage B;     	//Branch stage
		Stage LSFU1;	//LSFU 1st stage
		Stage LSFU2;	//LSFU 2st stage
		Stage LSFU3;	//LSFU WB stage

	public:
	  //Create CPU object which uses Code, Registers, and Data objects
	  CPU(Code &mycode, Registers &myregisters, Data &mydata);
	  ~CPU(); // Deconstructor
	  void initialize(); //Sets initial values for object
	  void display(); //Displays object members' values

	  //Simulates one cycle of cpu usage.
	  int simulate(Code &mycode, Registers &myregisters, Data &mydata,
			ROB &myrob, IQ &myiq);
};

#endif
