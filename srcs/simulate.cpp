#include <vector>
#include <string>
#include "cpu.h"
#include "apex.h"

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
	/****B2 STAGE****/
	// Advanced by ROB COMMITTING
	/****B1 STAGE****/
	if (B1.isReady() && B2.isEmpty()){
		B1.advance(B2);
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
	// Decide if any successful issues occurred this cycle
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
	// NOP instructions do not advance into the IQ. They do not get a ROB entry.
	else if (DRF2.opcode == "NOP"){
		// Mark the stage empty so advancement can continue
		DRF2.empty = true;
		// Dispatch fails, however
		no_dispatch++;

	}
	else {
		if (DRF2.isReady() && !DRF2.isEmpty()){
			//Advance the contents of DRF2 into the IQ
			myiq.dispatchInst(DRF2);

			//Empty DRF2
			DRF2.empty = true;

			//Increment stats counters
			dispatched++;
		}
		else {
			//Dispatch fails
			no_dispatch++;
		}
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

	/****ROB****/

	/****ALU3 STAGE****/

	/****ALU2 STAGE****/

	/****ALU1 STAGE****/

	/****MUL2 STAGE****/

	/****MUL1 STAGE****/

	/****LSFU3 STAGE****/

	/****LSFU2 STAGE****/

	/****LSFU1 STAGE****/

	/****B2 STAGE****/

	/****B1 STAGE****/
	// If a branch is taken, the following actions must occur:
	//   1. Flush the ROB using flush()
	//   2. Flush the IQ using flush()
	//   3. Flush instructions waiting in any stage if issued after B stage

	/****IQ****/

	/****DRF2 STAGE****/

	/****DRF1 STAGE****/

	/****F STAGE****/
	// If is_halting == true, do not fetch further instructions.
	// If a HALT is fetched, set is_halting = true.
	// These conditions are needed in the STOPPING PHASE.
	if (!is_halting){
		//Fetch the next instruction
	}
	if (F.opcode == "HALT")
		is_halting = true;


	/*FORWARDING PHASE************************************************************
	******************************************************************************
	*****************************************************************************/

	/****ROB****/

	/****ALU3 STAGE****/

	/****ALU2 STAGE****/

	/****ALU1 STAGE****/

	/****MUL2 STAGE****/

	/****MUL1 STAGE****/

	/****LSFU3 STAGE****/

	/****LSFU2 STAGE****/

	/****LSFU1 STAGE****/

	/****B2 STAGE****/

	/****B1 STAGE****/

	/****IQ****/

	/****DRF2 STAGE****/

	/****DRF1 STAGE****/

	/****F STAGE****/


	/*STOPPING PHASE**************************************************************
	******************************************************************************
	*****************************************************************************/

	//Stop execution (return code 0) if:
	// 1. A HALT has been encountered (set with HALT in F, also preventing fetch)
	// 2. HALT reaches DRF2 (ensures no instructions need to enter IQ)
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
