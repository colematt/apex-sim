#include <vector>
#include <string>
#include "cpu.h"
#include "apex.h"

#define FORWARDING 1

int CPU::simulate(Code &mycode, Registers &myregisters, Data &mydata,
	ROB &myrob, IQ &myiq){

	/*COMMITTING PHASE************************************************************
	******************************************************************************
	*****************************************************************************/

	// Check to see if the ROB head matches the contents of either
	// ALU3, MUL2, LSFU3, B2. If there's a match:
	// 1. Commit ROB's head entry
	// 2. Increment stats counters
	// 3. Mark that FU stage empty (prepare to "advance" into that stage)
	if (!myrob.isEmpty()){
		if (ALU3.isReady() && myrob.match(ALU3)){
			myrob.commit(myregisters);
			committed++;
			ALU3.empty = true;
		}
		else if (MUL2.isReady() && myrob.match(MUL2)){
			myrob.commit(myregisters);
			committed++;
			MUL2.empty = true;
		}
		else if (LSFU3.isReady() && myrob.match(LSFU3)){
			myrob.commit(myregisters);
			if (LSFU3.opcode == "LOAD"){
				committed_load++;
				committed++;
			}
			else {
				committed_store++;
				committed++;
			}
			LSFU3.empty = true;
		}
		else if (B2.isReady() && myrob.match(B2)){
			myrob.commit(myregisters);
			committed++;
			B2.empty = true;
		}
		else{no_commit++;} // there were ROB contents, but they didn't match
	}
	else{no_commit++;} // there were no ROB contents

	/*ADVANCEMENT PHASE***********************************************************
	******************************************************************************
	*****************************************************************************/

	/****B2 STAGE****/
	// Advanced by ROB COMMITTING

	/****B1 STAGE****/
	if (B1.isReady() && B2.isEmpty()){
		B1.advance(B2);
	}

	/****ALU3 STAGE****/
	// Advanced by ROB COMMITTING

	/****ALU2 STAGE****/
	if (ALU2.isReady() && ALU3.isEmpty()){
		ALU2.advance(ALU3);
	}

	/****ALU1 STAGE****/
	if (ALU1.isReady() && ALU2.isEmpty()){
		ALU1.advance(ALU2);
	}

	/****MUL2 STAGE****/
	// Advanced by ROB COMMITTING

	/****MUL1 STAGE****/
	if (MUL1.isReady() && MUL2.isEmpty()){
		MUL1.advance(MUL2);
	}
	/****LSFU3 STAGE****/
	// Advanced by ROB COMMITTING

	/****LSFU2 STAGE****/
	if (LSFU2.isReady() && LSFU3.isEmpty()){
		LSFU2.advance(LSFU3);
	}

	/****LSFU1 STAGE****/
	if (LSFU1.isReady() && LSFU2.isEmpty()){
		LSFU1.advance(LSFU2);
	}

	/****IQ****/
	int wakeup = -1;
	// Up to 3 wakeup signals can occur per cycle.
	for (wakeup = 0; wakeup < 3; wakeup++){
		//If we can issue, do so, and increment stats
		if (myiq.issue(ALU1, MUL1, LSFU1, B1)) {
			issued++;
		}
		//If we can't issue, break out of the for-loop
		else{
			break;
		}
	}
	// Now that we've finished wakeups,
	// Determine if no successful issues occurred this cycle
	if (wakeup == 0)
		no_issued++;

	/****DRF2 STAGE****/
	// If HALT is in this stage, do not advance it. Its presence here is part of
	// the STOPPING logic! There are no instructions behind it because
	// F stage has stopped fetching. All other opcodes will advance into IQ.
	if (DRF2.opcode == "HALT"){
		//Dispatch fails
		no_dispatch++;
	}
	else if (DRF2.opcode == "NOP"){
		// NOP instructions do not advance into the IQ.
		// NOP instructions do not get a ROB entry.
		// Mark the stage empty so advancement can continue, dispatch failed
		DRF2.empty = true;
		no_dispatch++;
	}
	else if (DRF2.opcode == "BZ" ||
					DRF2.opcode == "BNZ" ||
				 	DRF2.opcode == "BAL" ||
					DRF2.opcode == "JUMP"){
		// Specification 2, Detail 2 states that no control flow instructions
		// can be dispatched until any control flow instruction in the IQ has
		// been issued.
		bool inIQ = false;
		bool inROB = false;
		if (myiq.hasEntryWithOpcode("BZ") ||
				myiq.hasEntryWithOpcode("BNZ") ||
				myiq.hasEntryWithOpcode("BAL") ||
				myiq.hasEntryWithOpcode("JUMP")){
			//Dispatch stalls
			no_dispatch++;
		}
		else {
			if (DRF2.isReady() && !DRF2.isEmpty()){
				//Advance the contents of DRF2 into the IQ
				if( inIQ == false){
					inIQ = myiq.dispatchInst(DRF2);
				}

				//Advance the contents of DRF2 into the ROB
				if( inROB == false){
					inROB = myrob.addStage(DRF2);
				}

				if( inIQ && inROB){
					//Empty DRF2
					DRF2.empty = true;

					//Increment stats counters
					dispatched++;

					inIQ = false;
					inROB = false;
				}
			}
			else {no_dispatch++;}
		}
	} // DRF2 control flow instruction handling
	else {
		bool inIQ = false;
		bool inROB = false;
		if (DRF2.isReady() && !DRF2.isEmpty()){
			//Advance the contents of DRF2 into the IQ
			if( inIQ == false){
				inIQ = myiq.dispatchInst(DRF2);
			}

			//Advance the contents of DRF2 into the ROB
			if( inROB == false){
				inROB = myrob.addStage(DRF2);
			}

			//Empty DRF2
			DRF2.empty = true;

			//Increment stats counters
			dispatched++;
		}
		else {no_dispatch++;}
	}

	/****DRF1 STAGE****/
	if (DRF1.isReady() && DRF2.isEmpty()){
		DRF1.advance(DRF2);
	}

	/****F STAGE****/
	if (F.isReady() && DRF1.isEmpty()){
		F.advance(DRF1);
	}

	/*WORKING PHASE***************************************************************
	******************************************************************************
	*****************************************************************************/

	/****B2 STAGE****/
	if (--(B2.lcounter) <= 0 && !B2.isEmpty()) {
		//Writeback X register
		if (B2.opcode == "BAL") {
			myregisters.write("X", (B2.pc)+4, true);
		}
		B2.ready = true;
	}

	/****B1 STAGE****/
	if (--(B1.lcounter) <= 0 && !B1.isEmpty()) {
		//Opcode is good,
		//Branch conditional is true or unconditionally taken
		if ((B1.opcode == "BZ" && Z == 0) ||
				(B1.opcode == "BNZ" && Z != 0) ||
				(B1.opcode == "BAL") ||
				(B1.opcode == "JUMP")){
			// Flush the ROB, IQ
			myrob.flush(B1.c);
			myiq.flush(B1.c, myregisters);

			// For each non-branch stage,
			// flush instructions if its timestamp
			// is after B1 stage's timestamp
			ALU3.flush(B1.c, myregisters);
			ALU2.flush(B1.c, myregisters);
			ALU1.flush(B1.c, myregisters);
			MUL2.flush(B1.c, myregisters);
			MUL1.flush(B1.c, myregisters);
			LSFU3.flush(B1.c, myregisters);
			LSFU2.flush(B1.c, myregisters);
			LSFU1.flush(B1.c, myregisters);
			DRF2.flush(B1.c, myregisters);
			DRF1.flush(B1.c, myregisters);
			F.flush(B1.c, myregisters);

			//Set global pc based on B1.opcode (and local B1.pc)
			if(B1.opcode == "BZ" || B1.opcode == "BNZ"){
				pc = B1.pc + B1.values.at(0);
			}
			else if (B1.opcode == "BAL" || B1.opcode == "JUMP"){
				pc = B1.values.at(0) + B1.values.at(1);
			}
			else {}

			// Reset the halting flag
			is_halting = false;

			// Set B1 as ready
			B1.ready = true;
		}
		// Opcode is good, but branch conditional is false
		// Set the stage as ready
		else if ((B1.opcode == "BZ" && Z != 0) || (B1.opcode == "BNZ" && Z == 0)){
			B1.ready = true;
		}
		//Opcode isn't good: it isn't one of BZ, BNZ, BAL, JUMP
		else{
			std::cerr << "Unrecognized opcode " << B1.opcode << " at B1 WORKING phase" << std::endl;
			B1.ready = false;
		}
	}

	/****ALU3 STAGE****/
	if (--(ALU3.lcounter) <= 0 && !ALU3.isEmpty()) {
		//Writeback
		myregisters.write(ALU3.operands.at(0), ALU3.values.at(0), ALU3.valids.at(0));

		ALU3.ready = true;
	}

	/****ALU2 STAGE****/
	if (--(ALU2.lcounter) <= 0 && !ALU2.isEmpty()) {
		//Perform arithmetic, set valid bit, set Z flag
		if (ALU2.opcode == "ADD"){
			if (!ALU2.valids.at(0)){
				ALU2.values.at(0) = ALU2.values.at(1) + ALU2.values.at(2);
				ALU2.valids.at(0) = true;
				if (ALU2.c >= Zcycle){
					Z = ALU2.values.at(0);
					Zcycle = ALU2.c;
				}
			}
		}
		else if (ALU2.opcode == "SUB"){
			if (!ALU2.valids.at(0)){
				ALU2.values.at(0) = ALU2.values.at(1) - ALU2.values.at(2);
				ALU2.valids.at(0) = true;
				if (ALU2.c >= Zcycle){
					Z = ALU2.values.at(0);
					Zcycle = ALU2.c;
				}
			}
		}
		else if (ALU2.opcode == "MOVC"){
			ALU2.values.at(0) = ALU2.values.at(1) + 0;
			ALU2.valids.at(0) = true;
		}
		else if (ALU2.opcode == "AND"){
			if (!ALU2.valids.at(0)){
				ALU2.values.at(0) = ALU2.values.at(1) & ALU2.values.at(2);
				ALU2.valids.at(0) = true;
				if (ALU2.c >= Zcycle){
					Z = ALU2.values.at(0);
					Zcycle = ALU2.c;
				}
			}
		}
		else if (ALU2.opcode == "OR"){
			if (!ALU2.valids.at(0)){
				ALU2.values.at(0) = ALU2.values.at(1) | ALU2.values.at(2);
				ALU2.valids.at(0) = true;
				if (ALU2.c >= Zcycle){
					Z = ALU2.values.at(0);
					Zcycle = ALU2.c;
				}
			}
		}
		else if (ALU2.opcode == "EX-OR"){
			if (!ALU2.valids.at(0)){
				ALU2.values.at(0) = ALU2.values.at(1) ^ ALU2.values.at(2);
				ALU2.valids.at(0) = true;
				if (ALU2.c >= Zcycle){
					Z = ALU2.values.at(0);
					Zcycle = ALU2.c;
				}
			}
		}
		else {
			std::cerr << "Unrecognized opcode " << ALU2.opcode << " at ALU2 WORKING phase" << std::endl;
		}

		ALU2.ready = true;
	}

	/****ALU1 STAGE****/
	if (--(ALU1.lcounter) <= 0) {
		ALU1.ready = true;
	}

	/****MUL2 STAGE****/
	if (--(MUL2.lcounter) <= 0 && !MUL2.isEmpty()) {
		//Writeback
		myregisters.write(MUL2.operands.at(0), MUL2.values.at(0), MUL2.valids.at(0));

		MUL2.ready = true;
	}

	/****MUL1 STAGE****/
	if (--(MUL1.lcounter) <= 0 && !MUL1.isEmpty()) {
		//Perform arithmetic, set valid bit, set Z flag
		if (MUL1.opcode == "MUL") {
			if (!ALU2.valids.at(0)){
				ALU2.values.at(0) = ALU2.values.at(1) * ALU2.values.at(2);
				ALU2.valids.at(0) = true;
				if (ALU2.c >= Zcycle){
					Z = ALU2.values.at(0);
					Zcycle = ALU2.c;
				}
			}
		}
		else {
			std::cerr << "Unrecognized opcode " << MUL1.opcode << " at MUL1 WORKING phase" << std::endl;
		}

		MUL1.ready = true;
	}

	/****LSFU3 STAGE****/
	if (--(LSFU3.lcounter) <= 0 && !LSFU3.isEmpty()) {
		if (LSFU3.opcode == "LOAD") {
			//Perform memory access
			LSFU3.values.at(0) = mydata.readMem(LSFU3.values.at(1));
			LSFU3.valids.at(0) = true;

			//Writeback
			myregisters.write(LSFU3.operands.at(0), LSFU3.values.at(0), LSFU3.valids.at(0));
		}
		else if (LSFU3.opcode == "STORE") {
			//Perform memory access
			mydata.writeMem(LSFU3.values.at(1), LSFU3.values.at(0));

			//No writeback (no destination registers)
		}
		else {
			std::cerr << "Unrecognized opcode " << LSFU3.opcode << " at LSFU3 WORKING phase" << std::endl;
		}

		LSFU3.ready = true;
	}

	/****LSFU2 STAGE****/
	if (--(LSFU2.lcounter) <= 0 && !LSFU2.isEmpty()) {
		/*This phase reserved for TLB lookup (not implemented)*/

		if (LSFU2.opcode == "LOAD"){
			///Operand[0] need not be valid; it gets written to in LSFU3
			LSFU2.ready = true;
		}
		else if (LSFU2.opcode == "STORE"){
			if (LSFU2.valids.at(0))
				LSFU2.ready = true;
			else
				LSFU2.ready = false;
		}
		else{
			std::cerr << "Unrecognized opcode " << LSFU2.opcode << " at LSFU2 WORKING phase" << std::endl;
			LSFU2.ready = false;
		}

	}

	/****LSFU1 STAGE****/
	if (--(LSFU1.lcounter) <= 0 && !LSFU1.isEmpty()) {
		//Compute address, store in src1 (LOAD) or src2 (STORE)
		if (LSFU1.opcode == "LOAD") {
			LSFU1.values.at(1) = LSFU1.values.at(1) + LSFU1.values.at(2);
			LSFU1.valids.at(1) = true;
		} else if (LSFU1.opcode == "STORE") {
			LSFU1.values.at(1) = LSFU1.values.at(1) + LSFU1.values.at(2);
			LSFU1.valids.at(1) = true;
		} else {
			std::cerr << "Unrecognized opcode " << LSFU1.opcode << " at LSFU1 WORKING phase" << std::endl;
		}

		LSFU1.ready = true;
	}


	/****B2 STAGE****/
	if (--(B2.lcounter) <= 0 && !B2.isEmpty()) {
		//Writeback X register
		if (B2.opcode == "BAL") {
			myregisters.write("X", (B2.pc)+4, true);
		}
		B2.ready = true;
	}

	/****B1 STAGE****/
	if (--(B1.lcounter) <= 0 && !B1.isEmpty()) {
		//Perform branching logic
		//Branch conditional is true or unconditionally taken
		if ((B1.opcode == "BZ" && Z == 0) ||
				(B1.opcode == "BNZ" && Z != 0) ||
				(B1.opcode == "BAL") ||
				(B1.opcode == "JUMP")){
			// Flush the ROB, IQ
			myrob.flush(B1.c);
			myiq.flush(B1.c, myregisters);

			// For each non-branch stage,
			// flush instructions if its timestamp
			// is after B1 stage's timestamp
			ALU3.flush(B1.c, myregisters);
			ALU2.flush(B1.c, myregisters);
			ALU1.flush(B1.c, myregisters);
			MUL2.flush(B1.c, myregisters);
			MUL1.flush(B1.c, myregisters);
			LSFU3.flush(B1.c, myregisters);
			LSFU2.flush(B1.c, myregisters);
			LSFU1.flush(B1.c, myregisters);
			DRF2.flush(B1.c, myregisters);
			DRF1.flush(B1.c, myregisters);
			F.flush(B1.c, myregisters);

			//Set global pc based on B1.opcode (and local B1.pc)
			if(B1.opcode == "BZ" || B1.opcode == "BNZ"){
				pc = B1.pc + B1.values.at(0);
			}
			else if (B1.opcode == "BAL" || B1.opcode == "JUMP"){
				pc = B1.values.at(0) + B1.values.at(1);
			}
			else {}

			//Set B1 as ready
			B1.ready = true;
		}
		//Branch conditional is false
		else if ((B1.opcode == "BZ" && Z != 0) || (B1.opcode == "BNZ" && Z == 0)){
			B1.ready = true;
		}
		//Opcode is not one of BZ, BNZ, BAL, JUMP
		else{
			std::cerr << "Unrecognized opcode " << B1.opcode << " at B1 WORKING phase" << std::endl;
			B1.ready = false;
		}
	}

	/****DRF2 STAGE****/
	if (--(DRF2.lcounter) <= 0 && !DRF2.isEmpty()) {
		// Readout available operands
		if (DRF2.opcode == "ADD" ||
			DRF2.opcode == "SUB" ||
			DRF2.opcode == "MUL" ||
			DRF2.opcode == "AND" ||
			DRF2.opcode == "OR" ||
			DRF2.opcode == "EX-OR"){

			DRF2.values.at(0) = myregisters.physRead(DRF2.operands.at(0));
			DRF2.valids.at(0) = myregisters.physIsValid(DRF2.operands.at(0));

			DRF2.values.at(1) = myregisters.read(DRF2.operands.at(1));
			DRF2.valids.at(1) = myregisters.isValid(DRF2.operands.at(1));

			DRF2.values.at(2) = myregisters.read(DRF2.operands.at(2));
			DRF2.valids.at(2) = myregisters.isValid(DRF2.operands.at(2));

			DRF2.ready = true;
		}
		else if (DRF2.opcode == "MOVC"){

			DRF2.values.at(0) = myregisters.physRead(DRF2.operands.at(0));
			DRF2.valids.at(0) = myregisters.physIsValid(DRF2.operands.at(0));

			DRF2.values.at(1) = DRF2.littoi(DRF2.operands.at(1));
			DRF2.valids.at(1) = true;

			myregisters.write(DRF2.operands.at(0), DRF2.values.at(0), false);

			DRF2.ready = true;
		}
		else if (DRF2.opcode == "STORE"){

			DRF2.values.at(0) = myregisters.read(DRF2.operands.at(0));
			DRF2.valids.at(0) = myregisters.isValid(DRF2.operands.at(0));

			DRF2.values.at(1) = myregisters.read(DRF2.operands.at(1));
			DRF2.valids.at(1) = myregisters.isValid(DRF2.operands.at(1));

			DRF2.values.at(2) = DRF2.littoi(DRF2.operands.at(2));
			DRF2.valids.at(2) = true;

			if (DRF2.valids.at(1))
				DRF2.ready = true;
		}

		else if (DRF2.opcode == "LOAD"){

			DRF2.values.at(0) = myregisters.physRead(DRF2.operands.at(0));
			DRF2.valids.at(0) = myregisters.physIsValid(DRF2.operands.at(0));

			DRF2.values.at(1) = myregisters.read(DRF2.operands.at(1));
			DRF2.valids.at(1) = myregisters.isValid(DRF2.operands.at(1));


			DRF2.values.at(2) = DRF2.littoi(DRF2.operands.at(2));
			DRF2.valids.at(2) = true;

			DRF2.ready = true;
		}

		else if (DRF2.opcode == "BZ" ||
			DRF2.opcode == "BNZ"){

			DRF2.values.at(0) = DRF2.littoi(DRF2.operands.at(0));
			DRF2.valids.at(0) = true;
			DRF2.ready = true;
		}
		else if (DRF2.opcode == "BAL" ||
			DRF2.opcode == "JUMP"){

			DRF2.values.at(0) = myregisters.read(DRF2.operands.at(0));
			DRF2.valids.at(0) = myregisters.isValid(DRF2.operands.at(0));

			DRF2.values.at(1) = DRF2.littoi(DRF2.operands.at(1));
			DRF2.valids.at(1) = true;

			DRF2.ready = true;
		}else{
			std::cerr << "Unresolvable opcode in DRF: " << DRF2.opcode << std::endl;
			exit(1);
		}//End DRF Stage

		DRF2.ready = true;
	}

	/****DRF1 STAGE****/
	if (--(DRF1.lcounter) <= 0 && !DRF1.isEmpty()) {
		if (DRF1.opcode == "ADD" ||
			DRF1.opcode == "SUB" ||
			DRF1.opcode == "MUL" ||
			DRF1.opcode == "AND" ||
			DRF1.opcode == "OR" ||
			DRF1.opcode == "EX-OR" ||
			DRF1.opcode == "MOVC"){
		// Perform renaming
		DRF1.operands.at(0) = myregisters.getRenamed(DRF1.operands.at(0));
		DRF1.ready = true;
		}

		if (DRF1.opcode == "STORE" ||
			DRF1.opcode == "BZ" ||
			DRF1.opcode == "BNZ" ||
			DRF1.opcode == "BAL" ||
			DRF1.opcode == "JUMP" ||
			DRF1.opcode == "HALT"){
			DRF1.ready = true;
		}

	}

	/****F STAGE****/
	// If is_halting == true, do not fetch further instructions. Remain empty.
	// If a HALT is fetched, set is_halting = true.
	// These conditions are needed in the STOPPING PHASE.
	if (!is_halting){
		if (--(F.lcounter) <= 0) {
			// Fetch the instruction at PC
			if (F.isEmpty() == true){
				F.initialize();
				F.lcounter = 0;
				std::vector<std::string> instr = mycode.getInstr(pc);

				F.pc = pc;
				F.opcode = instr.at(0);
				for (int i=1;i<instr.size();i++){
					if (instr.at(i) != " ")
						F.operands.push_back(instr.at(i));
				}
				F.empty = false;
				F.ready = true;

				// Increment the PC
				pc += 4;
			}
			// Check whether the is_halting flag should be set
			if (F.opcode == "HALT")
				is_halting = true;
		}
	}

	/*FORWARDING PHASE************************************************************
	******************************************************************************
	*****************************************************************************/
	#if FORWARDING
	/****B2 --> ****/
	//--> B1 handled by immediately committing X register

	/****ALU3 --> ****/
	// --> IQ (ALU3.dst = IQ.entry.src)
	for (auto &entry: myiq.issue_queue){
		if (entry.opcode == "ADD" ||
				entry.opcode == "SUB" ||
				entry.opcode == "MUL" ||
				entry.opcode == "AND" ||
				entry.opcode == "OR" ||
				entry.opcode == "EX-OR"){
			if (entry.operands.at(1) == ALU3.operands.at(0)){
				entry.values.at(1) = ALU3.values.at(0);
				entry.valids.at(1) = ALU3.valids.at(0);
			}
			if (entry.operands.at(2) == ALU3.operands.at(0)){
				entry.values.at(2) = ALU3.values.at(0);
				entry.valids.at(2) = ALU3.valids.at(0);
			}
		}
		if (entry.opcode == "LOAD"){
			if (entry.operands.at(1) == ALU3.operands.at(0)){
				entry.values.at(1) = ALU3.values.at(0);
				entry.valids.at(1) = ALU3.valids.at(0);
			}
		}
		if (entry.opcode == "STORE"){
			if (entry.operands.at(1) == ALU3.operands.at(0)){
				entry.values.at(1) = ALU3.values.at(0);
				entry.valids.at(1) = ALU3.valids.at(0);
			}
			if (entry.operands.at(2) == ALU3.operands.at(0)){
				entry.values.at(2) = ALU3.values.at(0);
				entry.valids.at(2) = ALU3.valids.at(0);
			}
		}
		if (entry.opcode == "BAL" || entry.opcode == "JUMP"){
			if (entry.operands.at(0) == ALU3.operands.at(0)){
				entry.values.at(0) = ALU3.values.at(0);
				entry.valids.at(0) = ALU3.valids.at(0);
			}
		}
	}

	/****ALU2 --> ****/
	// --> ALU1 (ALU2.dst == ALU1.srcs)
	if (ALU1.opcode != "MOVC"){
		if (ALU1.operands.at(1) == ALU2.operands.at(0)){
			ALU1.values.at(1) = ALU2.values.at(0);
			ALU1.valids.at(1) = ALU2.valids.at(0);
		}
		if (ALU1.operands.at(2) == ALU2.operands.at(0)){
			ALU1.values.at(2) = ALU2.values.at(0);
			ALU1.valids.at(2) = ALU2.valids.at(0);
		}
	}
	// --> MUL1 (ALU2.dst == MUL1.srcs)
	if (MUL1.opcode == "MUL"){
		if (MUL1.operands.at(1) == ALU2.operands.at(0)){
			MUL1.values.at(1) = ALU2.values.at(0);
			MUL1.valids.at(1) = ALU2.valids.at(0);
		}
		if (MUL1.operands.at(2) == ALU2.operands.at(0)){
			MUL1.values.at(2) = ALU2.values.at(0);
			MUL1.valids.at(2) = ALU2.valids.at(0);
		}
	}
	// --> B1   (B1.opcode == {BAL,JUMP}, ALU2.dst == B1.srcs)
	if (B1.opcode == "BAL" || B1.opcode == "JUMP"){
		if (B1.operands.at(0) == ALU2.operands.at(0)){
			B1.values.at(0) = ALU2.values.at(0);
			B1.valids.at(0) = ALU2.valids.at(0);
		}
	}
	// --> LSFU2 (LSFU2.opcode == {LOAD}, ALU2.dst == LSFU2.srcs)
	if (LSFU2.opcode == "LOAD"){
		if (LSFU2.operands.at(1) == ALU2.operands.at(0)){
			LSFU2.values.at(1) = ALU2.values.at(0);
			LSFU2.valids.at(1) = ALU2.valids.at(0);
		}
	}
	// --> LSFU2 (LSFU2.opcode == {STORE}, ALU2.dst == LSFU2.srcs)
	if (LSFU2.opcode == "STORE"){
		if (LSFU2.operands.at(0) == ALU2.operands.at(0)){
			LSFU2.values.at(0) = ALU2.values.at(0);
			LSFU2.valids.at(0) = ALU2.valids.at(0);
		}
		if (LSFU2.operands.at(1) == ALU2.operands.at(0)){
			LSFU2.values.at(1) = ALU2.values.at(0);
			LSFU2.valids.at(1) = ALU2.valids.at(0);
		}
	}
	// --> LSFU1 (LSFU1.opcode == {LOAD}, ALU2.dst == LSFU1.srcs)
	if (LSFU1.opcode == "LOAD"){
		if (LSFU1.operands.at(1) == ALU2.operands.at(0)){
			LSFU1.values.at(1) = ALU2.values.at(0);
			LSFU1.valids.at(1) = ALU2.valids.at(0);
		}
	}
	// --> LSFU1 (LSFU1.opcode == {STORE}, ALU2.dst == LSFU1.srcs)
	if (LSFU1.opcode == "STORE"){
		if (LSFU1.operands.at(0) == ALU2.operands.at(0)){
			LSFU1.values.at(0) = ALU2.values.at(0);
			LSFU1.valids.at(0) = ALU2.valids.at(0);
		}
		if (LSFU1.operands.at(1) == ALU2.operands.at(0)){
			LSFU1.values.at(1) = ALU2.values.at(0);
			LSFU1.valids.at(1) = ALU2.valids.at(0);
		}
	}
	// --> IQ (ALU2.op[0] == IQ.entry.{srcs})
	for (auto &entry: myiq.issue_queue){
		if (entry.opcode == "ADD" ||
				entry.opcode == "SUB" ||
				entry.opcode == "MUL" ||
				entry.opcode == "AND" ||
				entry.opcode == "OR" ||
				entry.opcode == "EX-OR"){
			if (entry.operands.at(1) == ALU2.operands.at(0)){
				entry.values.at(1) = ALU2.values.at(0);
				entry.valids.at(1) = ALU2.valids.at(0);
			}
			if (entry.operands.at(2) == ALU2.operands.at(0)){
				entry.values.at(2) = ALU2.values.at(0);
				entry.valids.at(2) = ALU2.valids.at(0);
			}
		}
		if (entry.opcode == "LOAD"){
			if (entry.operands.at(1) == ALU2.operands.at(0)){
				entry.values.at(1) = ALU2.values.at(0);
				entry.valids.at(1) = ALU2.valids.at(0);
			}
		}
		if (entry.opcode == "STORE"){
			if (entry.operands.at(1) == ALU2.operands.at(0)){
				entry.values.at(1) = ALU2.values.at(0);
				entry.valids.at(1) = ALU2.valids.at(0);
			}
			if (entry.operands.at(2) == ALU2.operands.at(0)){
				entry.values.at(2) = ALU2.values.at(0);
				entry.valids.at(2) = ALU2.valids.at(0);
			}
		}
		if (entry.opcode == "BAL" || entry.opcode == "JUMP"){
			if (entry.operands.at(0) == ALU2.operands.at(0)){
				entry.values.at(0) = ALU2.values.at(0);
				entry.valids.at(0) = ALU2.valids.at(0);
			}
		}
	}

	/****MUL2 --> ****/
	// --> IQ (MUL2.op[0] == IQ.entry.{srcs})

	/****MUL1 (lcounter == 0) --> ****/
	// --> ALU1 (MUL1.dst == ALU1.srcs)
	// --> B1 (MUL1.dst = B1.srcs)
	// --> LSFU2 (MUL1.dst = LSFU2.srcs)
	// --> LSFU1 (MUL1.dst = LSFU1.srcs)

	/****LSFU3 --> ****/
	// --> LSFU2 (LSFU3.opcode == LOAD, LSFU2.opcode == STORE, LSFU3.dst = LSFU2.srcs)
	// --> ALU1 (LSFU3.opcode == LOAD, LSFU3.dst == ALU1.srcs)
	// --> MUL1 (LSFU3.opcode == LOAD, LSFU3.dst == MUL1.srcs)
	// --> LSFU1 (LSFU1.opcode == LOAD, )
	// --> LSFU1 (LSFU1.opcode == STORE, )
	// --> IQ

	#endif

	/*STOPPING PHASE**************************************************************
	******************************************************************************
	*****************************************************************************/

	//Stop execution (return code 0) if:
	// 1. A HALT has been encountered (set with HALT in F, preventing fetch)
	// 2. HALT reaches DRF2 (ensures no instructions need to be dispatched)
	// 3. The IQ is empty (ensures no instructions need to be issued)
	// 4. The ROB is empty (ensures no instructions need to be committed)
	//Continue execution (return code 1) otherwise.
	if (is_halting &&
			DRF2.opcode == "HALT" &&
			myiq.isEmpty() &&
			myrob.isEmpty()){
		cycle++;
		return 0;
	}
	else{
		cycle++;
		return 1;
	}
}
