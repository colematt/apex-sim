/* FILE INFORMATION
File:     cpu.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file for cpu.cpp
*/

#include <string>
#include <vector>
#include "instruction.h"

#ifndef CPU_H
#define CPU_H

//Represents the instruction occupying an APEX pipeline stage, its operands, any values accumulated by the register file/forwarding/computation and any validity bools accumulated.
class Stage {
private:

public:
  //the stage is occupied by an inflight instruction
  //(it will always have an instruction loaded, but that instruction may have
  // advanced to a follow-on stage; it should not be "simulated" again)
  bool isEmpty;
  //the stage has completed its work for the inflight instruction
  //(it is ready to be forwarded and/or advanced)
  bool isReady;


  //Instruction contents
  int pc; //program counter value that issued this
  std::string opcode; //(e.g. ADD) representing this instruction
  std::vector<std::string> operands;
  std::vector<int> values;
  std::vector<bool> valids;

  //Constructors/Destructors
  Stage();

  //Interface functions
  void initialize(); //Initialize the contents of this stage to empty with NOP
  void display(); //Display the contents of this stage
  int simulate(); //Perform this stage's actions

  //Utility functions
  //TODO: design void advance(); //advances a ready instruction to next stage
  int littoi(std::string literal);

}; //class Stage

class CPU {
private:
  Stage F;      //Fetch stage
  Stage DRF;    //Decode/Reg File stage
  Stage ALU1;   //ALU 1st stage
  Stage ALU2;   //ALU 2nd stage
  Stage B;      //Branch stage
  Stage D;      //(Branch) Delay stage
  Stage M;      //Memory stage
  Stage WB;     //Write Back stage
public:
  CPU(Code &mycode, Registers &myregisters, Data &mydata);
  void initialize();
  void display();
  int simulate();
}

#endif
