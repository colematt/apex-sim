#include <vector>
#include <string>
#include "cpu.h"
#include "apex.h"

#define FORWARDING 0

int CPU::simulate(CPU &mycpu, Code &mycode, Registers &myregisters, Data &mydata, ROB &myrob, IQ &myiq){

/******************************************************************************/
/************************STAGE ADVANCEMENT PHASE*******************************/
/******************************************************************************/

	//WB Stage
	if (WB.opcode == "ADD" ||
			WB.opcode == "SUB" ||
			WB.opcode == "MOVC" ||
			WB.opcode == "MUL" ||
			WB.opcode == "AND" ||
			WB.opcode == "OR" ||
			WB.opcode == "EX-OR" ||
			WB.opcode == "LOAD" ||
			WB.opcode == "STORE" ||
			WB.opcode == "BZ" ||
			WB.opcode == "BNZ" ||
			WB.opcode == "BAL" ||
			WB.opcode == "JUMP" ||
			WB.opcode == "HALT" ||
			WB.opcode == "NOP"){
			//If the WB stage is not empty and ready, "vacate" it.
			//The fields' contents will remain, but it will appear empty on checks
			//WARNING: Do NOT use the advance() function -- WB has nowhere to advance.
			if (!WB.isEmpty && WB.isReady){
				WB.isEmpty = true;
				WB.isReady = false;
			}
	}
	else{
		std::cerr << "Unresolvable opcode in WB: " << WB.opcode << std::endl;
		exit(1);
	}//End WB Stage

	//M Stage
	if (M.opcode == "ADD" ||
			M.opcode == "SUB" ||
			M.opcode == "MOVC" ||
			M.opcode == "MUL" ||
			M.opcode == "AND" ||
			M.opcode == "OR" ||
			M.opcode == "EX-OR" ||
			M.opcode == "LOAD" ||
			M.opcode == "STORE" ||
			M.opcode == "BZ" ||
			M.opcode == "BNZ" ||
			M.opcode == "BAL" ||
			M.opcode == "JUMP" ||
			M.opcode == "HALT" ||
			M.opcode == "NOP"){
				//If the M stage is not empty and ready, and the WB stage is empty,
				//Vacate M and advance to WB
				M.advance(WB);
	}
	else{
		std::cerr << "Unresolvable opcode in M: " << M.opcode << std::endl;
		exit(1);
	}//End M Stage

	//D Stage
	//WARNING: D contests with ALU2 to advance to M
	if (D.opcode == "BZ" ||
			D.opcode == "BNZ" ||
			D.opcode == "BAL" ||
			D.opcode == "JUMP" ||
			D.opcode == "HALT" ||
			D.opcode == "NOP"){

				/* Only one of ALU2 and D can advance to M:
				Therefore if both are ready to advance, set D to !isReady
				and do not advance it. On the next work phase, it gets set
				to isReady (it isReady after EVERY work phase)
				D takes no priority over ALU2 because it does no more work
				after B phase, and it flushes F/DRF in B. There should be
				no conflicts with ALU2 for instructions dispatched after
				the instruction in B.                                  */
				if (D.isReady && !ALU2.isReady){
					D.advance(M);
				}
				else if (ALU2.opcode == "NOP"){
					D.advance(M);
				}
				else{
					D.isReady = false;
				}
	}
	else{
		std::cerr << "Unresolvable opcode in D: " << D.opcode << std::endl;
		exit(1);
	}//End D Stage

	//B Stage
	if (B.opcode == "BZ" ||
			B.opcode == "BNZ" ||
			B.opcode == "BAL" ||
			B.opcode == "JUMP" ||
			B.opcode == "HALT" ||
			B.opcode == "NOP"){
				B.advance(D);
	}
	else{
		std::cerr << "Unresolvable opcode in B: " << B.opcode << std::endl;
		exit(1);
	}//End B Stage

	//ALU2 Stage
	if (ALU2.opcode == "ADD" ||
		ALU2.opcode == "SUB" ||
		ALU2.opcode == "MUL" ||
		ALU2.opcode == "AND" ||
		ALU2.opcode == "OR" ||
		ALU2.opcode == "EX-OR" ||
		ALU2.opcode == "MOVC" ||
		ALU2.opcode == "LOAD" ||
		ALU2.opcode == "STORE" ||
		ALU2.opcode == "NOP"){
				ALU2.advance(M);
	}
	else{
		std::cerr << "Unresolvable opcode in ALU2: " << ALU2.opcode << std::endl;
		exit(1);
	}//End ALU2 Stage

	//ALU1 Stage
	if (ALU1.opcode == "ADD" ||
		ALU1.opcode == "SUB" ||
		ALU1.opcode == "MUL" ||
		ALU1.opcode == "AND" ||
		ALU1.opcode == "OR" ||
		ALU1.opcode == "EX-OR" ||
		ALU1.opcode == "MOVC" ||
		ALU1.opcode == "LOAD" ||
		ALU1.opcode == "STORE" ||
		ALU1.opcode == "NOP"){
				ALU1.advance(ALU2);
	}
	else{
		std::cerr << "Unresolvable opcode in ALU1: " << ALU1.opcode << std::endl;
		exit(1);
	}//End ALU1 Stage

	//DRF Stage
	if (DRF.opcode == "ADD" ||
		DRF.opcode == "SUB" ||
		DRF.opcode == "MUL" ||
		DRF.opcode == "AND" ||
		DRF.opcode == "OR" ||
		DRF.opcode == "EX-OR" ||
		DRF.opcode == "LOAD" ||
		DRF.opcode == "MOVC" ||
		DRF.opcode == "STORE"){
				DRF.advance(ALU1);
	}
	else if (DRF.opcode == "BZ" ||
		DRF.opcode == "BNZ" ||
		DRF.opcode == "BAL" ||
		DRF.opcode == "JUMP" ||
		DRF.opcode == "HALT"){
				DRF.advance(B);
	}
	else if(DRF.opcode == "NOP"){
		DRF.isEmpty = true;
		DRF.isReady = false;
	}
	else{
		std::cerr << "Unresolvable opcode in DRF: " << DRF.opcode << std::endl;
		exit(1);
	} //End DRF Stage

	//F Stage
	if (F.opcode == "ADD" ||
		F.opcode == "SUB" ||
		F.opcode == "MOVC" ||
		F.opcode == "MUL" ||
		F.opcode == "AND" ||
		F.opcode == "OR" ||
		F.opcode == "EX-OR" ||
		F.opcode == "LOAD" ||
		F.opcode == "STORE" ||
		F.opcode == "BZ" ||
		F.opcode == "BNZ" ||
		F.opcode == "BAL" ||
		F.opcode == "JUMP" ||
		F.opcode == "HALT" ||
		F.opcode == "NOP"){
				F.advance(DRF);
	}
	else{
		std::cerr << "Unresolvable opcode in F: " << F.opcode << std::endl;
		exit(1);
	} //End F Stage

	/******************************************************************************/
	/******************************WORKING PHASE***********************************/
	/******************************************************************************/
		//WB Stage
		if (WB.opcode == "ADD" ||
			WB.opcode == "SUB" ||
			WB.opcode == "MOVC" ||
			WB.opcode == "MUL" ||
			WB.opcode == "AND" ||
			WB.opcode == "OR" ||
			WB.opcode == "EX-OR" ||
			WB.opcode == "LOAD"){
			myregisters.write(WB.operands.at(0), WB.values.at(0), WB.valids.at(0));

			WB.isEmpty = false;
			WB.isReady = true;
		}
		else if (WB.opcode == "STORE" ||
			WB.opcode == "BZ" ||
			WB.opcode == "BNZ" ||
			WB.opcode == "BAL" ||
			WB.opcode == "JUMP" ||
			WB.opcode == "NOP"){

			WB.isEmpty = false;
			WB.isReady = true;
		}
		else if (WB.opcode == "HALT"){
			WB.isEmpty = false;
			WB.isReady = true;

			M.isEmpty = true;
			D.isEmpty = true;
			B.isEmpty = true;
			ALU2.isEmpty = true;
			ALU1.isEmpty = true;
			DRF.isEmpty = true;
			F.isEmpty = true;

			return 0; //Terminate program
		}
		else{
			std::cerr << "Unresolvable opcode: " << WB.opcode << std::endl;
			exit(1);
		}//End WB Stage

		//M Stage
		if (M.opcode == "ADD" ||
			M.opcode == "SUB" ||
			M.opcode == "MOVC" ||
			M.opcode == "MUL" ||
			M.opcode == "AND" ||
			M.opcode == "OR" ||
			M.opcode == "EX-OR"){

			M.isEmpty = false;
			M.isReady = true;
		}
		else if (M.opcode == "LOAD"){
			M.values.at(0) = mydata.readMem(M.values.at(1));
			M.valids.at(0) = true;

			M.isEmpty = false;
			M.isReady = true;

			//ALU2
			//Forward loaded data to src1 or src2 for ARITH operations
			if (ALU2.opcode == "ADD" ||
			ALU2.opcode == "SUB" ||
			ALU2.opcode == "MUL" ||
			ALU2.opcode == "AND" ||
			ALU2.opcode == "OR" ||
			ALU2.opcode == "EX-OR"){
				if (ALU2.operands.at(1) == M.operands.at(0)){
					ALU2.values.at(1) = M.values.at(0);
					ALU2.valids.at(1) = M.valids.at(0);
				}

				if (ALU2.operands.at(2) == M.operands.at(0)){
					ALU2.values.at(2) = M.values.at(0);
					ALU2.valids.at(2) = M.valids.at(0);
				}
			}

			//Forward loaded data to src1 or dest1 for Store operations
			if (ALU2.opcode == "STORE"){
				if (ALU2.operands.at(0) == M.operands.at(0)){
					ALU2.values.at(0) = M.values.at(0);
					ALU2.valids.at(0) = M.valids.at(0);
				}
				if (ALU2.operands.at(1) == M.operands.at(0)){
					ALU2.values.at(1) = M.values.at(0);
					ALU2.valids.at(1) = M.valids.at(0);
				}
			}

			//ALU1
			//Forward loaded data to src1 or src2 for ARITH operations
			if (ALU1.opcode == "ADD" ||
			ALU1.opcode == "SUB" ||
			ALU1.opcode == "MUL" ||
			ALU1.opcode == "AND" ||
			ALU1.opcode == "OR" ||
			ALU1.opcode == "EX-OR"){
				if (ALU1.operands.at(1) == M.operands.at(0)){
					ALU1.values.at(1) = M.values.at(0);
					ALU1.valids.at(1) = M.valids.at(0);
				}

				if (ALU1.operands.at(2) == M.operands.at(0)){
					ALU1.values.at(2) = M.values.at(0);
					ALU1.valids.at(2) = M.valids.at(0);
				}
			}

			//Forward loaded data to src1 or dest1 for Store operations
			if (ALU1.opcode == "STORE"){
				if (ALU1.operands.at(0) == M.operands.at(0)){
					ALU1.values.at(0) = M.values.at(0);
					ALU1.valids.at(0) = M.valids.at(0);
				}
				if (ALU1.operands.at(1) == M.operands.at(0)){
					ALU1.values.at(1) = M.values.at(0);
					ALU1.valids.at(1) = M.valids.at(0);
				}
			}

			//B
			//Forward loaded data to src1 or src2 for ARITH operations
			if (B.opcode == "BAL" ||
			B.opcode == "JUMP"){
				if (B.operands.at(0) == M.operands.at(0)){
					B.values.at(0) = M.values.at(0);
					B.valids.at(0) = M.valids.at(0);
				}
			}

			//DRF
			//Forward loaded data to src1 or src2 for ARITH operations
			if (DRF.opcode == "ADD" ||
			DRF.opcode == "SUB" ||
			DRF.opcode == "MUL" ||
			DRF.opcode == "AND" ||
			DRF.opcode == "OR" ||
			DRF.opcode == "EX-OR"){
				if (DRF.operands.at(1) == M.operands.at(0)){
					DRF.values.at(1) = M.values.at(0);
					DRF.valids.at(1) = M.valids.at(0);
				}

				if (DRF.operands.at(2) == M.operands.at(0)){
					DRF.values.at(2) = M.values.at(0);
					DRF.valids.at(2) = M.valids.at(0);
				}
			}

			//Forward loaded data to src1 or dest1 for Store operations
			if (DRF.opcode == "STORE"){
				if (DRF.operands.at(0) == M.operands.at(0)){
					DRF.values.at(0) = M.values.at(0);
					DRF.valids.at(0) = M.valids.at(0);
				}
				if (DRF.operands.at(1) == M.operands.at(0)){
					DRF.values.at(1) = M.values.at(0);
					DRF.valids.at(1) = M.valids.at(0);
				}
			}

			//Forward loaded data to src1 for Branch operations
			if (DRF.opcode == "BAL" ||
				DRF.opcode == "JUMP"){
				if (DRF.operands.at(0) == M.operands.at(0)){
					DRF.values.at(0) = M.values.at(0);
					DRF.valids.at(0) = M.valids.at(0);
				}
			}
		}
		else if (M.opcode == "STORE"){
			mydata.writeMem(M.values.at(1), M.values.at(0));
			M.valids.at(0) = true;

			M.isEmpty = false;
			M.isReady = true;
		}
		else if (M.opcode == "BZ" ||
			M.opcode == "BNZ" ||
			M.opcode == "BAL" ||
			M.opcode == "JUMP" ||
			M.opcode == "HALT" ||
			M.opcode == "NOP"){
			M.isEmpty = false;
			M.isReady = true;
		}
		else{
			std::cerr << "Unresolvable opcode in M: " << M.opcode << std::endl;
			exit(1);
		}//End M Stage

		//D Stage
		if (D.opcode == "BZ" ||
			D.opcode == "BNZ" ||
			D.opcode == "BAL" ||
			D.opcode == "JUMP" ||
			D.opcode == "HALT" ||
			D.opcode == "NOP"){

			D.isEmpty = false;
			D.isReady = true;
		}
		else{
			std::cerr << "Unresolvable opcode in D: " << D.opcode << std::endl;
			exit(1);
		}//End D Stage

		//B Stage
		if (B.opcode == "BZ"){

			if(myregisters.read("Z") == 1){
				pc = B.pc + B.values.at(0);

				F.initialize();
				DRF.initialize();
			} else {
				pc = B.pc + 4;
			}

			B.isEmpty = false;
			B.isReady = true;
		}
		else if (B.opcode == "BNZ"){

			if(myregisters.read("Z") == 1){
				pc = B.pc + 4;
			} else {
				pc = B.pc + B.values.at(0);

				F.initialize();
				DRF.initialize();
			}

			B.isEmpty = false;
			B.isReady = true;
		}
		else if (B.opcode == "BAL"){
			myregisters.write("X",pc + 4, 1);
			pc = B.values.at(0) + B.values.at(1);

			F.initialize();
			DRF.initialize();

			B.isEmpty = false;
			B.isReady = true;
		}
		else if (B.opcode == "JUMP"){
			pc = B.values.at(0) + B.values.at(1);

			F.initialize();
			DRF.initialize();

			B.isEmpty = false;
			B.isReady = true;
		}
		else if (B.opcode == "HALT" ||
			B.opcode == "NOP"){

			B.isEmpty = false;
			B.isReady = true;
		}
		else{
			std::cerr << "Unresolvable opcode in B: " << B.opcode << std::endl;
			exit(1);
		}//End B Stage

		//ALU2 Stage
		if (ALU2.opcode == "ADD"){
			ALU2.values.at(0) = ALU2.values.at(1) + ALU2.values.at(2);
			ALU2.valids.at(0) = true;

			ALU2.isReady = true;

			if (ALU2.values.at(0) == 0){
				myregisters.write("Z", 1, 1);
			}
			else {
				myregisters.write("Z", 0, 1);
			}

			//ALU1
			//Forward result of dest to ARITH src1 or src2
			if (ALU1.opcode == "ADD" ||
			ALU1.opcode == "SUB" ||
			ALU1.opcode == "MUL" ||
			ALU1.opcode == "AND" ||
			ALU1.opcode == "OR" ||
			ALU1.opcode == "EX-OR"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}

				if (ALU1.operands.at(2) == ALU2.operands.at(0)){
					ALU1.values.at(2) = ALU2.values.at(0);
					ALU1.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (ALU1.opcode == "LOAD"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE src1
			if (ALU1.opcode == "STORE"){
				if (ALU1.operands.at(0) == ALU2.operands.at(0)){
					ALU1.values.at(0) = ALU2.values.at(0);
					ALU1.valids.at(0) = ALU2.valids.at(0);
				}
			}


			//B
			//Forward result of dest to BAL, or JUMP src1
			if (B.opcode == "BAL" ||
				B.opcode == "JUMP"){
				if (B.operands.at(0) == ALU2.operands.at(0)){
					B.values.at(0) = ALU2.values.at(0);
					B.valids.at(0) = ALU2.valids.at(0);
				}
			}

			//DRF
			//Forward result of dest to ARITH src1 or src2
			if (DRF.opcode == "ADD" ||
			DRF.opcode == "SUB" ||
			DRF.opcode == "MUL" ||
			DRF.opcode == "AND" ||
			DRF.opcode == "OR" ||
			DRF.opcode == "EX-OR"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}

				if (DRF.operands.at(2) == ALU2.operands.at(0)){
					DRF.values.at(2) = ALU2.values.at(0);
					DRF.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (DRF.opcode == "LOAD"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE, BAL, or JUMP src1
			if (DRF.opcode == "STORE" ||
				DRF.opcode == "BAL" ||
				DRF.opcode == "JUMP"){
				if (DRF.operands.at(0) == ALU2.operands.at(0)){
					DRF.values.at(0) = ALU2.values.at(0);
					DRF.valids.at(0) = ALU2.valids.at(0);
				}
			}

			ALU2.isEmpty = false;
		}
		else if (ALU2.opcode == "SUB"){
			ALU2.values.at(0) = ALU2.values.at(1) - ALU2.values.at(2);
			ALU2.valids.at(0) = true;

			ALU2.isReady = true;

			if (ALU2.values.at(0) == 0){
				myregisters.write("Z", 1, 1);
			}
			else {
				myregisters.write("Z", 0, 1);
			}

			//ALU1
			//Forward result of dest to ARITH src1 or src2
			if (ALU1.opcode == "ADD" ||
			ALU1.opcode == "SUB" ||
			ALU1.opcode == "MUL" ||
			ALU1.opcode == "AND" ||
			ALU1.opcode == "OR" ||
			ALU1.opcode == "EX-OR"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}

				if (ALU1.operands.at(2) == ALU2.operands.at(0)){
					ALU1.values.at(2) = ALU2.values.at(0);
					ALU1.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (ALU1.opcode == "LOAD"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE src1
			if (ALU1.opcode == "STORE"){
				if (ALU1.operands.at(0) == ALU2.operands.at(0)){
					ALU1.values.at(0) = ALU2.values.at(0);
					ALU1.valids.at(0) = ALU2.valids.at(0);
				}
			}


			//B
			//Forward result of dest to BAL, or JUMP src1
			if (B.opcode == "BAL" ||
				B.opcode == "JUMP"){
				if (B.operands.at(0) == ALU2.operands.at(0)){
					B.values.at(0) = ALU2.values.at(0);
					B.valids.at(0) = ALU2.valids.at(0);
				}
			}

			//DRF
			//Forward result of dest to ARITH src1 or src2
			if (DRF.opcode == "ADD" ||
			DRF.opcode == "SUB" ||
			DRF.opcode == "MUL" ||
			DRF.opcode == "AND" ||
			DRF.opcode == "OR" ||
			DRF.opcode == "EX-OR"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}

				if (DRF.operands.at(2) == ALU2.operands.at(0)){
					DRF.values.at(2) = ALU2.values.at(0);
					DRF.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (DRF.opcode == "LOAD"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE, BAL, or JUMP src1
			if (DRF.opcode == "STORE" ||
				DRF.opcode == "BAL" ||
				DRF.opcode == "JUMP"){
				if (DRF.operands.at(0) == ALU2.operands.at(0)){
					DRF.values.at(0) = ALU2.values.at(0);
					DRF.valids.at(0) = ALU2.valids.at(0);
				}
			}

			ALU2.isEmpty = false;
		}
		else if (ALU2.opcode == "MUL"){
			ALU2.values.at(0) = ALU2.values.at(1) * ALU2.values.at(2);
			ALU2.valids.at(0) = true;

			ALU2.isReady = true;

			if (ALU2.values.at(0) == 0){
				myregisters.write("Z", 1, 1);
			}
			else {
				myregisters.write("Z", 0, 1);
			}

			//ALU1
			//Forward result of dest to ARITH src1 or src2
			if (ALU1.opcode == "ADD" ||
			ALU1.opcode == "SUB" ||
			ALU1.opcode == "MUL" ||
			ALU1.opcode == "AND" ||
			ALU1.opcode == "OR" ||
			ALU1.opcode == "EX-OR"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}

				if (ALU1.operands.at(2) == ALU2.operands.at(0)){
					ALU1.values.at(2) = ALU2.values.at(0);
					ALU1.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (ALU1.opcode == "LOAD"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE src1
			if (ALU1.opcode == "STORE"){
				if (ALU1.operands.at(0) == ALU2.operands.at(0)){
					ALU1.values.at(0) = ALU2.values.at(0);
					ALU1.valids.at(0) = ALU2.valids.at(0);
				}
			}


			//B
			//Forward result of dest to BAL, or JUMP src1
			if (B.opcode == "BAL" ||
				B.opcode == "JUMP"){
				if (B.operands.at(0) == ALU2.operands.at(0)){
					B.values.at(0) = ALU2.values.at(0);
					B.valids.at(0) = ALU2.valids.at(0);
				}
			}

			//DRF
			//Forward result of dest to ARITH src1 or src2
			if (DRF.opcode == "ADD" ||
			DRF.opcode == "SUB" ||
			DRF.opcode == "MUL" ||
			DRF.opcode == "AND" ||
			DRF.opcode == "OR" ||
			DRF.opcode == "EX-OR"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}

				if (DRF.operands.at(2) == ALU2.operands.at(0)){
					DRF.values.at(2) = ALU2.values.at(0);
					DRF.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (DRF.opcode == "LOAD"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE, BAL, or JUMP src1
			if (DRF.opcode == "STORE" ||
				DRF.opcode == "BAL" ||
				DRF.opcode == "JUMP"){
				if (DRF.operands.at(0) == ALU2.operands.at(0)){
					DRF.values.at(0) = ALU2.values.at(0);
					DRF.valids.at(0) = ALU2.valids.at(0);
				}
			}

			ALU2.isEmpty = false;
		}
		else if (ALU2.opcode == "AND"){
			ALU2.values.at(0) = ALU2.values.at(1) & ALU2.values.at(2);
			ALU2.valids.at(0) = true;

			ALU2.isReady = true;

			if (ALU2.values.at(0) == 0){
				myregisters.write("Z", 1, 1);
			}
			else {
				myregisters.write("Z", 0, 1);
			}

			//ALU1
			//Forward result of dest to ARITH src1 or src2
			if (ALU1.opcode == "ADD" ||
			ALU1.opcode == "SUB" ||
			ALU1.opcode == "MUL" ||
			ALU1.opcode == "AND" ||
			ALU1.opcode == "OR" ||
			ALU1.opcode == "EX-OR"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}

				if (ALU1.operands.at(2) == ALU2.operands.at(0)){
					ALU1.values.at(2) = ALU2.values.at(0);
					ALU1.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (ALU1.opcode == "LOAD"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE src1
			if (ALU1.opcode == "STORE"){
				if (ALU1.operands.at(0) == ALU2.operands.at(0)){
					ALU1.values.at(0) = ALU2.values.at(0);
					ALU1.valids.at(0) = ALU2.valids.at(0);
				}
			}


			//B
			//Forward result of dest to BAL, or JUMP src1
			if (B.opcode == "BAL" ||
				B.opcode == "JUMP"){
				if (B.operands.at(0) == ALU2.operands.at(0)){
					B.values.at(0) = ALU2.values.at(0);
					B.valids.at(0) = ALU2.valids.at(0);
				}
			}

			//DRF
			//Forward result of dest to ARITH src1 or src2
			if (DRF.opcode == "ADD" ||
			DRF.opcode == "SUB" ||
			DRF.opcode == "MUL" ||
			DRF.opcode == "AND" ||
			DRF.opcode == "OR" ||
			DRF.opcode == "EX-OR"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}

				if (DRF.operands.at(2) == ALU2.operands.at(0)){
					DRF.values.at(2) = ALU2.values.at(0);
					DRF.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (DRF.opcode == "LOAD"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE, BAL, or JUMP src1
			if (DRF.opcode == "STORE" ||
				DRF.opcode == "BAL" ||
				DRF.opcode == "JUMP"){
				if (DRF.operands.at(0) == ALU2.operands.at(0)){
					DRF.values.at(0) = ALU2.values.at(0);
					DRF.valids.at(0) = ALU2.valids.at(0);
				}
			}

			ALU2.isEmpty = false;
		}
		else if (ALU2.opcode == "OR"){
			ALU2.values.at(0) = ALU2.values.at(1) | ALU2.values.at(2);
			ALU2.valids.at(0) = true;

			ALU2.isReady = true;

			if (ALU2.values.at(0) == 0){
				myregisters.write("Z", 1, 1);
			}
			else {
				myregisters.write("Z", 0, 1);
			}

			//ALU1
			//Forward result of dest to ARITH src1 or src2
			if (ALU1.opcode == "ADD" ||
			ALU1.opcode == "SUB" ||
			ALU1.opcode == "MUL" ||
			ALU1.opcode == "AND" ||
			ALU1.opcode == "OR" ||
			ALU1.opcode == "EX-OR"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}

				if (ALU1.operands.at(2) == ALU2.operands.at(0)){
					ALU1.values.at(2) = ALU2.values.at(0);
					ALU1.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (ALU1.opcode == "LOAD"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE src1
			if (ALU1.opcode == "STORE"){
				if (ALU1.operands.at(0) == ALU2.operands.at(0)){
					ALU1.values.at(0) = ALU2.values.at(0);
					ALU1.valids.at(0) = ALU2.valids.at(0);
				}
			}

			//B
			//Forward result of dest to BAL, or JUMP src1
			if (B.opcode == "BAL" ||
				B.opcode == "JUMP"){
				if (B.operands.at(0) == ALU2.operands.at(0)){
					B.values.at(0) = ALU2.values.at(0);
					B.valids.at(0) = ALU2.valids.at(0);
				}
			}

			//DRF
			//Forward result of dest to ARITH src1 or src2
			if (DRF.opcode == "ADD" ||
			DRF.opcode == "SUB" ||
			DRF.opcode == "MUL" ||
			DRF.opcode == "AND" ||
			DRF.opcode == "OR" ||
			DRF.opcode == "EX-OR"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}

				if (DRF.operands.at(2) == ALU2.operands.at(0)){
					DRF.values.at(2) = ALU2.values.at(0);
					DRF.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (DRF.opcode == "LOAD"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE, BAL, or JUMP src1
			if (DRF.opcode == "STORE" ||
				DRF.opcode == "BAL" ||
				DRF.opcode == "JUMP"){
				if (DRF.operands.at(0) == ALU2.operands.at(0)){
					DRF.values.at(0) = ALU2.values.at(0);
					DRF.valids.at(0) = ALU2.valids.at(0);
				}
			}

			ALU2.isEmpty = false;
		}
		else if (ALU2.opcode == "EX-OR"){
			ALU2.values.at(0) = ALU2.values.at(1) ^ ALU2.values.at(2);
			ALU2.valids.at(0) = true;

			ALU2.isReady = true;

			if (ALU2.values.at(0) == 0){
				myregisters.write("Z", 1, 1);
			}
			else {
				myregisters.write("Z", 0, 1);
			}

			//ALU1
			//Forward result of dest to ARITH src1 or src2
			if (ALU1.opcode == "ADD" ||
			ALU1.opcode == "SUB" ||
			ALU1.opcode == "MUL" ||
			ALU1.opcode == "AND" ||
			ALU1.opcode == "OR" ||
			ALU1.opcode == "EX-OR"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}

				if (ALU1.operands.at(2) == ALU2.operands.at(0)){
					ALU1.values.at(2) = ALU2.values.at(0);
					ALU1.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (ALU1.opcode == "LOAD"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE src1
			if (ALU1.opcode == "STORE"){
				if (ALU1.operands.at(0) == ALU2.operands.at(0)){
					ALU1.values.at(0) = ALU2.values.at(0);
					ALU1.valids.at(0) = ALU2.valids.at(0);
				}
			}


			//B
			//Forward result of dest to BAL, or JUMP src1
			if (B.opcode == "BAL" ||
				B.opcode == "JUMP"){
				if (B.operands.at(0) == ALU2.operands.at(0)){
					B.values.at(0) = ALU2.values.at(0);
					B.valids.at(0) = ALU2.valids.at(0);
				}
			}

			//DRF
			//Forward result of dest to ARITH src1 or src2
			if (DRF.opcode == "ADD" ||
			DRF.opcode == "SUB" ||
			DRF.opcode == "MUL" ||
			DRF.opcode == "AND" ||
			DRF.opcode == "OR" ||
			DRF.opcode == "EX-OR"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}

				if (DRF.operands.at(2) == ALU2.operands.at(0)){
					DRF.values.at(2) = ALU2.values.at(0);
					DRF.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (DRF.opcode == "LOAD"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE, BAL, or JUMP src1
			if (DRF.opcode == "STORE" ||
				DRF.opcode == "BAL" ||
				DRF.opcode == "JUMP"){
				if (DRF.operands.at(0) == ALU2.operands.at(0)){
					DRF.values.at(0) = ALU2.values.at(0);
					DRF.valids.at(0) = ALU2.valids.at(0);
				}
			}

			ALU2.isEmpty = false;
		}
		else if (ALU2.opcode == "MOVC"){
			ALU2.values.at(0) = ALU2.values.at(1) + 0;
			ALU2.valids.at(0) = true;

			//ALU1
			//Forward result of dest to ARITH src1 or src2
			if (ALU1.opcode == "ADD" ||
			ALU1.opcode == "SUB" ||
			ALU1.opcode == "MUL" ||
			ALU1.opcode == "AND" ||
			ALU1.opcode == "OR" ||
			ALU1.opcode == "EX-OR"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}

				if (ALU1.operands.at(2) == ALU2.operands.at(0)){
					ALU1.values.at(2) = ALU2.values.at(0);
					ALU1.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (ALU1.opcode == "LOAD"){
				if (ALU1.operands.at(1) == ALU2.operands.at(0)){
					ALU1.values.at(1) = ALU2.values.at(0);
					ALU1.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE src1
			if (ALU1.opcode == "STORE"){
				if (ALU1.operands.at(0) == ALU2.operands.at(0)){
					ALU1.values.at(0) = ALU2.values.at(0);
					ALU1.valids.at(0) = ALU2.valids.at(0);
				}
			}


			//B
			//Forward result of dest to BAL, or JUMP src1
			if (B.opcode == "BAL" ||
				B.opcode == "JUMP"){
				if (B.operands.at(0) == ALU2.operands.at(0)){
					B.values.at(0) = ALU2.values.at(0);
					B.valids.at(0) = ALU2.valids.at(0);
				}
			}

			//DRF
			//Forward result of dest to ARITH src1 or src2
			if (DRF.opcode == "ADD" ||
			DRF.opcode == "SUB" ||
			DRF.opcode == "MUL" ||
			DRF.opcode == "AND" ||
			DRF.opcode == "OR" ||
			DRF.opcode == "EX-OR"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}

				if (DRF.operands.at(2) == ALU2.operands.at(0)){
					DRF.values.at(2) = ALU2.values.at(0);
					DRF.valids.at(2) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to LOAD src1
			if (DRF.opcode == "LOAD"){
				if (DRF.operands.at(1) == ALU2.operands.at(0)){
					DRF.values.at(1) = ALU2.values.at(0);
					DRF.valids.at(1) = ALU2.valids.at(0);
				}
			}

			//Forward result of dest to STORE, BAL, or JUMP src1
			if (DRF.opcode == "STORE" ||
				DRF.opcode == "BAL" ||
				DRF.opcode == "JUMP"){
				if (DRF.operands.at(0) == ALU2.operands.at(0)){
					DRF.values.at(0) = ALU2.values.at(0);
					DRF.valids.at(0) = ALU2.valids.at(0);
				}
			}

			ALU2.isEmpty = false;
			ALU2.isReady = true;
		}
		else if (ALU2.opcode == "LOAD"){
			ALU2.values.at(1) = ALU2.values.at(1) + ALU2.values.at(2);
			ALU2.valids.at(1) = true;

			ALU2.isReady = true;

			ALU2.isEmpty = false;
		}
		else if (ALU2.opcode == "STORE"){
			ALU2.values.at(1) = ALU2.values.at(1) + ALU2.values.at(2);
			ALU2.valids.at(1) = true;

			ALU2.isReady = true;

			ALU2.isEmpty = false;
		}
		else if (ALU2.opcode == "NOP"){
				ALU2.isEmpty = true;
				ALU2.isReady = true;
		}
		else{
			std::cerr << "Unresolvable opcode in ALU2: " << ALU2.opcode << std::endl;
			exit(1);
		}//End ALU2 Stage

		//ALU1 Stage
		if (ALU1.opcode == "ADD" ||
			ALU1.opcode == "SUB" ||
			ALU1.opcode == "MOVC" ||
			ALU1.opcode == "MUL" ||
			ALU1.opcode == "AND" ||
			ALU1.opcode == "OR" ||
			ALU1.opcode == "EX-OR" ||
			ALU1.opcode == "LOAD" ||
			ALU1.opcode == "STORE"){
				ALU1.isEmpty = false;
				ALU1.isReady = true;
		}
		else if(ALU1.opcode == "NOP"){
			ALU1.isEmpty = true;
			ALU1.isReady = true;
		}
		else{
			std::cerr << "Unresolvable opcode in ALU1: " << ALU1.opcode << std::endl;
			exit(1);
		}//End ALU1 Stage

		//DRF Stage
		if (DRF.opcode == "ADD" ||
			DRF.opcode == "SUB" ||
			DRF.opcode == "MUL" ||
			DRF.opcode == "AND" ||
			DRF.opcode == "OR" ||
			DRF.opcode == "EX-OR"){

			DRF.values.at(0) = myregisters.read(DRF.operands.at(0));
			DRF.valids.at(0) = myregisters.isValid(DRF.operands.at(0));

			if (!DRF.valids.at(1)){
				DRF.values.at(1) = myregisters.read(DRF.operands.at(1));
				DRF.valids.at(1) = myregisters.isValid(DRF.operands.at(1));
			}

			if (!DRF.valids.at(2)){
				DRF.values.at(2) = myregisters.read(DRF.operands.at(2));
				DRF.valids.at(2) = myregisters.isValid(DRF.operands.at(2));
			}

			DRF.isEmpty = false;

			if (DRF.valids.at(1) && DRF.valids.at(2)){
				myregisters.write(DRF.operands.at(0), DRF.values.at(0), false);
				DRF.isReady = true;
			}
		}
		else if (DRF.opcode == "MOVC"){

			DRF.values.at(0) = myregisters.read(DRF.operands.at(0));
			DRF.valids.at(0) = myregisters.isValid(DRF.operands.at(0));

			DRF.values.at(1) = DRF.littoi(DRF.operands.at(1));
			DRF.valids.at(1) = true;

			myregisters.write(DRF.operands.at(0), DRF.values.at(0), false);

			DRF.isEmpty = false;

			DRF.isReady = true;
		}
		else if (DRF.opcode == "STORE"){

			if (!DRF.valids.at(0)){
				DRF.values.at(0) = myregisters.read(DRF.operands.at(0));
				DRF.valids.at(0) = myregisters.isValid(DRF.operands.at(0));
			}

			DRF.values.at(1) = myregisters.read(DRF.operands.at(1));
			DRF.valids.at(1) = myregisters.isValid(DRF.operands.at(1));

			DRF.values.at(2) = DRF.littoi(DRF.operands.at(2));
			DRF.valids.at(2) = true;

			DRF.isEmpty = false;

			if (DRF.valids.at(1))
				DRF.isReady = true;
		}

		else if (DRF.opcode == "LOAD"){

			DRF.values.at(0) = myregisters.read(DRF.operands.at(0));
			DRF.valids.at(0) = myregisters.isValid(DRF.operands.at(0));

			if (!DRF.valids.at(1)){
				DRF.values.at(1) = myregisters.read(DRF.operands.at(1));
				DRF.valids.at(1) = myregisters.isValid(DRF.operands.at(1));
			}

			DRF.values.at(2) = DRF.littoi(DRF.operands.at(2));
			DRF.valids.at(2) = true;

			DRF.isEmpty = false;

			if (DRF.valids.at(1)){
				myregisters.write(DRF.operands.at(0), DRF.values.at(0), false);
				DRF.isReady = true;
			}
		}

		else if (DRF.opcode == "BZ" ||
			DRF.opcode == "BNZ"){

			DRF.values.at(0) = DRF.littoi(DRF.operands.at(0));
			DRF.valids.at(0) = true;

			DRF.isEmpty = false;
			DRF.isReady = true;
		}
		else if (DRF.opcode == "BAL" ||
			DRF.opcode == "JUMP"){

			DRF.values.at(0) = myregisters.read(DRF.operands.at(0));
			DRF.valids.at(0) = myregisters.isValid(DRF.operands.at(0));

			DRF.values.at(1) = DRF.littoi(DRF.operands.at(1));
			DRF.valids.at(1) = true;

			DRF.isEmpty = false;

			if (DRF.valids.at(0))
				DRF.isReady = true;
		}
		else if (DRF.opcode == "HALT" ||
			DRF.opcode == "NOP"){
			DRF.isEmpty = false;
			DRF.isReady = true;
		}
		else{
			std::cerr << "Unresolvable opcode in DRF: " << DRF.opcode << std::endl;
			exit(1);
		}//End DRF Stage

		//F Stage
		if (F.isEmpty == true){
			F.initialize();
			std::vector<std::string> instr = mycode.getInstr(pc);

			F.pc = pc;
			F.opcode = instr.at(0);
			for (int i=1;i<instr.size();i++){
				if (instr.at(i) != " ")
					F.operands.push_back(instr.at(i));
			}
			F.isEmpty = false;
			F.isReady = true;

			pc += 4;;
		}//End F Stage

	return 1; //Return 1 for cycle complete and no Halt processed
}
