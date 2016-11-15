/* FILE INFORMATION
File:     cpu.cpp
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Contains the Stage class, which defines a cpu stage.
*/

#include <iostream>
#include "stage.h"

Stage::Stage(std::string n){
	name = n;
	this->initialize();
}

void Stage::initialize(){
	pc = 0;
	opcode = "NOP";
	operands.clear();
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

bool Stage::isAllValid(){
	return false; //Temporary declare for compile test
}
