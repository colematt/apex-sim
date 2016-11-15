/* FILE INFORMATION
File:     cpu.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the CPU class, which simulates operation of a five stage CPU.
*/

#include <iostream>
#include "cpu.h"

Stage::Stage(std::string n){
	name = n;
	this->initialize()
}

void Stage::initialize(){
	pc = 0;
	opcode = "NOP";
	operands.clear()
	values.clear();
	valids.clear();
	isEmpty = true;
	isReady = false;
}

void Stage::display(){
	std::cout << name << ": " << opcode << " ";

	for(auto o : operands){
		std::cout << o << " ";
	}

	std::cout << std::endl;
} 

int Stage::littoi(std::string literal){
	literal = literal.erase(0,1);
	return std::stoi(literal);
}

bool Stage::isAllValid(){}

CPU::CPU(Code &mycode, Registers &myregisters, Data &mydata){
	this->initialize()
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

int CPU::simulate(){}