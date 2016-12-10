/* FILE INFORMATION
File:     cpu.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file to hold globally aware variables
*/

#include <string>
#include "code.h"
#include "cpu.h"
#include "data.h"
#include "register.h"
#include "rob.h"
#include "iq.h"

#ifndef APEX_H
#define APEX_H

//VERBOSE 0 : No diagnostic output. Only output required by specification.
//VERBOSE 1 : Some diagnostic output. Notify on each major action.
//VERBOSE 2 : More diagnostic output. VERBOSE 1 + mini report after a cycle.
//VERBOSE 3 : All diagnostic output. Currently equal to VERBOSE 2.
#define VERBOSE 1

extern int pc;    //STATE: program counter current value
extern int cycle; //STAT: simulator cycle current value
extern int dispatched; //STAT: number of instructions dispatched to IQ
extern int no_dispatch; //STAT: number of cycles with no instruction dispatched to IQ
extern int issued; //STAT: number of instructions issued to ANY FU plus HALT instructions issued directly to ROB
extern int no_issued; //STAT: number of cycles no instructions were issued
extern int committed; //STAT: number of instructions committed from ROB
extern int committed_load; //STAT: number of LOAD instructions committed
extern int committed_store; //STAT: number of STORE instructions committed
extern int no_commit; //STAT: number of cycles no instructions were committed


// Helper functions
void help();
void initialize(CPU &mycpu, Registers &myregisters, Data &mydata, ROB &myrob, IQ &myiq);
void display(CPU &mycpu, Registers &myregisters, Data &mydata, ROB &myrob, IQ &myiq,
  std::string mod="all", int a1=0, int a2=3996);
void stats();
int simulate(int num_cycles, CPU &mycpu, Code &mycode, Registers &myregisters, Data &mydata, ROB &myrob, IQ &myiq);
void quit(CPU &mycpu, Registers &myregisters, Data &mydata, ROB &myrob, IQ &myiq);

#endif
