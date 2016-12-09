/* FILE INFORMATION
File:     cpu.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the CPU class, which simulates operation of a five stage CPU.
*/

#include <iostream>
#include "cpu.h"

//Constructors for stages explicitly called before constructor body begins
CPU::CPU(Code &mycode, Registers &myregisters, Data &mydata) :
 F("Fetch"),
 DRF1("DRF Rename"),
 DRF2("DRF Dispatch"),
 ALU1("ALU First"),
 ALU2("ALU Second"),
 ALU3("ALU Third"),
 MUL1("MUL First"),
 MUL2("MUL Second"),
 B("Branch"),
 LSFU1("LSFU First"),
 LSFU2("LSFU Second"),
 LSFU3("LSFU Third")
{
	this->initialize();
}

CPU::~CPU(){

}

void CPU::initialize(){
  is_halting = false;

	F.initialize();
	DRF1.initialize();
	DRF2.initialize();
	ALU1.initialize();
	ALU2.initialize();
	ALU3.initialize();
	MUL1.initialize();
	MUL2.initialize();
	B.initialize();
	LSFU1.initialize();
	LSFU2.initialize();
	LSFU3.initialize();
}

void CPU::display(){
	F.display();
	DRF1.display();
	DRF2.display();
	ALU1.display();
	ALU2.display();
	ALU3.display();
	MUL1.display();
	MUL2.display();
	B.display();
	LSFU1.display();
	LSFU2.display();
	LSFU3.display();
}
