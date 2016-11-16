/* FILE INFORMATION
File:     cpu.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the CPU class, which simulates operation of a five stage CPU.
*/

#include <iostream>
#include "cpu.h"

	Stage F("Fetch");      		//Fetch stage
  	Stage DRF("Decode/RF");    	//Decode/Reg File stage
 	Stage ALU1("ALU First");   	//ALU 1st stage
  	Stage ALU2("ALU Second");   //ALU 2nd stage
  	Stage B("Branch");      	//Branch stage
  	Stage D("Branch Delay");    //(Branch) Delay stage
  	Stage M("Memory");      	//Memory stage
  	Stage WB("Write Back");     //Write Back stage

CPU::CPU(){
	this->initialize();
}

void CPU::initialize(){
	F.initialize();
	DRF.initialize();
	ALU1.initialize();
	ALU2.initialize();
	B.initialize();
	D.initialize();
	M.initialize();
	WB.initialize();
}

void CPU::display(){
	F.display();
	DRF.display();
	ALU1.display();
	ALU2.display();
	B.display();
	D.display();
	M.display();
	WB.display();
}

//int CPU::simulate(Code &mycode, Registers &myregisters, Data &mydata){
//	return 0; //Temporary declare for compile test
//}