/* FILE INFORMATION
File:     data.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header for data.cpp
*/

#ifndef DATA_H
#define DATA_H

class Data
{
private:
	std::vector<short>  memory (4000);

public:
	Data(); //initialize the memory with all positions set to zero

  	//Read one byte-address from memory at <addr>
  	int readMem(int addr);

  	//Write one byte to memory at <addr>
  	void writeMem(int addr, int value);

  	//Display first 100 non-zero contents of memory
  	void display();

};
