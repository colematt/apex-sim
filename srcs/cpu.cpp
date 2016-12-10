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
 ALU1("ALU 1st"),
 ALU2("ALU 2nd"),
 ALU3("ALU WB"),
 MUL1("MUL 1st"),
 MUL2("MUL WB"),
 B1("Branch 1st"),
 B2("Branch WB")
 LSFU1("LSFU 1st"),
 LSFU2("LSFU 2nd"),
 LSFU3("LSFU WB")
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
	B1.initialize();
	B2.initialize();
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
	B1.display();
	B2.display();
	LSFU1.display();
	LSFU2.display();
	LSFU3.display();
}
