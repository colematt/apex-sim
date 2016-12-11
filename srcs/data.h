/* FILE INFORMATION
File:     data.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header for data.cpp
*/

#ifndef DATA_H
#define DATA_H

#include <vector>

class Data
{
private:
	std::vector<int>  memory;

public:
	Data(); //initialize the memory with all positions set to zero
	~Data(); //Deconstructor

	//Interface functions
	void initialize();
	void display(int a1, int a2);

	//Accessors and Mutators
	int readMem(int addr);
	void writeMem(int addr, int value);

};
#endif
