/* FILE INFORMATION
File:     cpu.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the CPU class, which simulates operation of a five stage CPU.
*/

#include <iostream>
#include "cpu.h"

CPU::CPU(Code &mycode, Registers &myregisters, Data &mydata) :
 F("Fetch"),
 DRF("Decode/RF"),
 ALU1("ALU First"),
 ALU2("ALU Second"),
 B("Branch"),
 D("Branch Delay"),
 M("Memory"),
 WB("Write Back")
{

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
