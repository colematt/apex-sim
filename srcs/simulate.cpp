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
	// ALU3, MUL2, LSFU3. If there's a match:
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
		else{/*no commit this cycle*/}
	}


	/*ADVANCEMENT PHASE***********************************************************
	******************************************************************************
	*****************************************************************************/

	/****ALU3 STAGE****/
	// Advanced by ROB COMMITTING

	/****ALU2 STAGE****/
	if (ALU2.isReady() && ALU3.isEmpty()){
		//TODO: Add advance logic
	}
	/****ALU1 STAGE****/
	if (ALU1.isReady() && ALU2.isEmpty()){
		//TODO: Add advance logic
	}
	/****MUL2 STAGE****/
	// Advanced by ROB COMMITTING

	/****MUL1 STAGE****/
	if (MUL1.isReady() && MUL2.isEmpty()){
		//TODO: Add advance logic
	}
	/****LSFU3 STAGE****/
	// Advanced by ROB COMMITTING

	/****LSFU2 STAGE****/
	if (LSFU2.isReady() && LSFU3.isEmpty()){
		//TODO: Add advance logic
	}
	/****LSFU1 STAGE****/
	if (LSFU1.isReady() && LSFU2.isEmpty()){
		//TODO: Add advance logic
	}
	/****B STAGE****/
	// B stage does not "advance", it empties and updates stats counters.
	// This is because B stage does not have a destination register
	// and so it doesn't commit.
	if (B.isReady()){
		//TODO: Add specialized B advance logic
	}
	/****IQ****/
	// Up to 3 wakeup signals can occur per cycle.
	for (int wakeup = 0; wakeup < 3; wakeup++){
		//If we can issue, do so, and increment stats
		if (myiq.issue(*ALU1, *MUL1, *LSFU1, *B)) {
			issued++;
		}
		//If we can't issue, break out of the for-loop
		else{
			break;
		}

		// Now that we've finished wakeups,
		// Decide if any successful issues occurred this cycle
		if (wakeup == 0)
			no_issued++;
	}
	/****DRF2 STAGE****/
	// If HALT is in this stage, do not advance it. Its presence here is part of
	// the STOPPING logic! There are no instructions behind it because
	// F stage has stopped fetching. All other opcodes will advance into IQ.
	if (DRF2.opcode == "HALT"){
		//Dispatch fails
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

	/****F STAGE****/


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

	/****B STAGE****/

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

	/****B STAGE****/

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
