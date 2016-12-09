#include <vector>
#include <string>
#include "cpu.h"
#include "apex.h"

int CPU::simulate(Code &mycode, Registers &myregisters, Data &mydata,
	ROB &myrob, IQ &myiq){

	/*COMMITTING PHASE*************************************************************
	*******************************************************************************
	******************************************************************************/

	/*ADVANCEMENT PHASE***********************************************************
	******************************************************************************
	*****************************************************************************/

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
	// If HALT is in this stage, do not advance it. Its presence here is part of
	// the STOPPING logic! There are no instructions behind it
	// because F stage has stopped fetching
	if (DRF2.opcode != "HALT"){
		//TODO: Advance the contents
	}

	/****DRF1 STAGE****/

	/****F STAGE****/


	/*WORKING PHASE****************************************************************
	*******************************************************************************
	******************************************************************************/

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
	if !(is_halting){
		//Fetch the next instruction
	}
	if (F.opcode == "HALT")
		is_halting = true;


	/*FORWARDING PHASE*************************************************************
	*******************************************************************************
	******************************************************************************/

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


	/*STOPPING PHASE***************************************************************
	*******************************************************************************
	******************************************************************************/

	//Stop execution (return code 0) if:
	// 1. A HALT has been encountered (set with HALT in F, also preventing fetch)
	// 2. HALT reaches DRF2 (ensures no instructions need to enter IQ)
	// 3. The IQ is empty (ensures no instructions need to be issued)
	// 4. The ROB is empty (ensures no instructions need to be committed)
	//Continue execution (return code 1) otherwise.
	if (is_halting &&
			DRF2.opcode == "HALT" &&
			myiq.issue_queue.empty() &&
			myrob.reorder_buffer.empty())
		return 0;
	else
		return 1;
}
