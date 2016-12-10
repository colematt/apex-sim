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
  bool empty;
  bool isEmpty();
  //the stage has completed its work for the inflight instruction
  //(it is ready to be forwarded and/or advanced)
  bool ready;
  bool isReady();

  //Instruction contents
  int pc; //program counter value that issued this
  int c; //simulator cycle "timestamp"
  std::string opcode; //(e.g. ADD) representing this instruction
  std::vector<std::string> operands; //contains the tags of source/destination
  std::vector<int> values; // contains the actual values
  std::vector<bool> valids; // contains whether those values are valid

  //Constructors/Destructors/Operators
  Stage(std::string n, int l=1);

  //Interface functions
  void initialize();
  void display();

  //Utility functions
  int littoi(std::string literal);
  bool isAllValid();
  bool advance(Stage &dest);
  bool flush(int cycle, Registers &rf);

}; //class Stage
#endif
