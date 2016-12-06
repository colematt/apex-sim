/* FILE INFORMATION
File:     cpu.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file for stage.cpp
*/

#include <string>
#include <vector>

#ifndef STAGE_H
#define STAGE_H

//Represents the instruction occupying an APEX pipeline stage, its operands, any values accumulated by the register file/forwarding/computation and any validity bools accumulated.
class Stage {
private:
    std::string name;
    int latency;
    int lcounter;

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
  int c; //simulator cycle "timestamp"
  std::string opcode; //(e.g. ADD) representing this instruction
  std::vector<std::string> operands;
  std::vector<int> values;
  std::vector<bool> valids;

  //Constructors/Destructors/Operators
  Stage(std::string n, int l=1);

  //Interface functions
  void initialize(); //Initialize the contents of this stage to empty with NOP
  void display(); //Display the contents of this stage: name, opcode, operands
  bool advance(Stage &dest); //Advance a stage into destination stage

  //Utility functions
  int littoi(std::string literal); //Convert a #literal to its int value
  bool isAllValid(); //For this instr are all sources valid or no sources

}; //class Stage
#endif
