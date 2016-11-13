/* FILE INFORMATION
File:     cpu.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file for cpu.cpp
*/

#ifndef CPU_H
#define CPU_H

//Represents the instruction occupying an APEX pipeline stage, its operands, any values accumulated by the register file/forwarding/computation and any validity bools accumulated.
Class Stage {
private:

public:
  //whether the stage is occupied by an inflight instruction or a remnant of an advanced instruction
  bool isEmpty;


};

#endif
