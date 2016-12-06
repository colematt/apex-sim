/* FILE INFORMATION
File:     cpu.h
Authors:  Matthew Cole <mcole8@binghamton.edu>
          Brian Gracin <bgracin1@binghamton.edu>
Description: Header file to hold globally aware variables
*/

#ifndef APEX_H
#define APEX_H

#define VERBOSE 1

extern int pc;    //STATE: program counter current value
extern int cycle; //STAT: simulator cycle current value
extern int dispatched; //STAT: number of instructions dispatched to IQ
extern int no_dispatch; //STAT: number of cycles with no instruction dispatched to IQ
extern int issued; //STAT: number of instructions issued to ANY FU plus HALT instructions issued directly to ROB
extern int no_issued; //STAT: number of cycles no instructions were issued
extern int resolved; //STAT: number of instructions resolved from Branch FU
extern int committed; //STAT: number of instructions committed from ROB
extern int committed_load; //STAT: number of LOAD instructions committed
extern int committed_store; //STAT: number of STORE instructions committed



// Helper functions
void help();
void initialize(CPU &mycpu, Registers &myregisters, Data &mydata);
void display(CPU &mycpu, Registers &myregisters, Data &mydata);
void stats();
int simulate(int num_cycles, CPU &apexCPU, Code &apexCode, Registers &apexRF, Data &apexData);
void quit(CPU &mycpu, Registers &myregisters, Data &mydata);

#endif
