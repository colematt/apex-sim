#define FORWARDING 0
#include <vector>
#include <string>
#include "cpu.h"
#include "apex.h"

int CPU::simulate(Code &mycode, Registers &myregisters, Data &mydata){

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
		return 0; //Terminate program
		WB.isEmpty = false;
	}
	else{
		std::cerr << "Unresolvable opcode: " << WB.opcode << std::endl;
		exit(1);
	}

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
	}
	else if (M.opcode == "STORE"){
		mydata.writeMem(M.values.at(0), M.values.at(1));
		M.valids.at(0) = true;

		M.isEmpty = false;
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
		std::cerr << "Unresolvable opcode: " << M.opcode << std::endl;
		exit(1);
	}

	//D Stage
	if (D.opcode == "BZ" ||
		D.opcode == "BNZ" ||
		D.opcode == "BAL" ||
		D.opcode == "JUMP"){

		D.isEmpty = false;
		D.isReady = true;
	}
	else{
		std::cerr << "Unresolvable opcode: " << D.opcode << std::endl;
		exit(1);
	}

	//B Stage
	if (B.opcode == "BZ"){

		if(myregisters.read("Z") == 1){
			pc = pc + B.values.at(0);

			F.initialize();
			DRF.initialize();
		} else {
			pc = pc + 4;
		}

		B.isEmpty = false;
	}
	else if (B.opcode == "BNZ"){

		if(myregisters.read("Z") == 1){
			pc = pc + 4;
		} else {
			pc = pc + B.values.at(0);

			F.initialize();
			DRF.initialize();
		}

		B.isEmpty = false;
	}
	else if (B.opcode == "BAL"){
		myregisters.write("X",pc + 4, 1);
		pc = B.values.at(0) + B.values.at(1);

		F.initialize();
		DRF.initialize();

		B.isEmpty = false;
	}
	else if (B.opcode == "JUMP"){
		pc = B.values.at(0) + B.values.at(1);

		F.initialize();
		DRF.initialize();

		B.isEmpty = false;
	}
	else{
		std::cerr << "Unresolvable opcode: " << B.opcode << std::endl;
		exit(1);
	}

	//ALU2 Stage
	if (ALU2.opcode == "ADD" ||
		ALU2.opcode == "SUB" ||
		ALU2.opcode == "MUL" ||
		ALU2.opcode == "AND" ||
		ALU2.opcode == "OR" ||
		ALU2.opcode == "EX-OR" ){
		if (ALU2.valids.at(1) == true && ALU2.valids.at(2) == true){
			ALU2.values.at(0) = ALU2.values.at(1) + ALU2.values.at(2);
			ALU2.valids.at(0) = true;

			if (ALU2.values.at(0) == 0){
				myregisters.write("Z", 1, 1);
			}
		}

		ALU2.isEmpty = false;

	}
	else if (ALU2.opcode == "MOVC"){
		ALU2.values.at(0) = ALU2.values.at(1) + 0;
		ALU2.valids.at(0) = true;

		ALU2.isEmpty = false;
	}
	else if (ALU2.opcode == "LOAD"){
		if (ALU2.valids.at(1) == true && ALU2.valids.at(2) == true){
			ALU2.values.at(1) = ALU2.values.at(1) + ALU2.values.at(2);
			ALU2.valids.at(1) = true;
		}

		ALU2.isEmpty = false;
	}
	else if (ALU2.opcode == "STORE"){
		if (ALU2.valids.at(0) == true && ALU2.valids.at(2) == true){
			ALU2.values.at(0) = ALU2.values.at(0) + ALU2.values.at(2);
			ALU2.valids.at(1) = true;
		}

		ALU2.isEmpty = false;
	}
	else if (ALU2.opcode == "HALT"){
		ALU2.isEmpty = false;
	}
	else if (ALU2.opcode == "NOP"){
		ALU2.isEmpty = false;
	}
	else{
		std::cerr << "Unresolvable opcode: " << ALU2.opcode << std::endl;
		exit(1);
	}

	//ALU1 Stage
	if (ALU1.opcode == "ADD" ||
		ALU1.opcode == "SUB" ||
		ALU1.opcode == "MOVC" ||
		ALU1.opcode == "MUL" ||
		ALU1.opcode == "AND" ||
		ALU1.opcode == "OR" ||
		ALU1.opcode == "EX-OR" ||
		ALU1.opcode == "LOAD" ||
		ALU1.opcode == "STORE" ||
		ALU1.opcode == "HALT" ||
		ALU1.opcode == "NOP"){
		ALU1.isEmpty = false;
		ALU1.isReady = true;
	}
	else{
		std::cerr << "Unresolvable opcode: " << ALU1.opcode << std::endl;
		exit(1);
	}

	//DRF Stage
	if (DRF.opcode == "ADD"){

		for (auto &operand : DRF.operands){
			if(operand[0] != '#'){
				DRF.values.push_back(myregisters.read(operand));
				DRF.valids.push_back(myregisters.isValid(operand));
			}
		}

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "SUB") {

		for (auto &operand : DRF.operands){
			if(operand[0] != '#'){
				DRF.values.push_back(myregisters.read(operand));
				DRF.valids.push_back(myregisters.isValid(operand));
			}
		}

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "MOVC"){

		DRF.values.push_back(myregisters.read(DRF.operands.at(0)));
		DRF.valids.push_back(myregisters.isValid(DRF.operands.at(0)));

		DRF.values.push_back(DRF.littoi(DRF.operands.at(1)));
		DRF.valids.push_back(true);

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "MUL"){

		for (auto &operand : DRF.operands){
			if(operand[0] != '#'){
				DRF.values.push_back(myregisters.read(operand));
				DRF.valids.push_back(myregisters.isValid(operand));
			}
		}
		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "AND"){

		for (auto &operand : DRF.operands){
			if(operand[0] != '#'){
				DRF.values.push_back(myregisters.read(operand));
				DRF.valids.push_back(myregisters.isValid(operand));
			}
		}

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "OR"){

		for (auto &operand : DRF.operands){
			if(operand[0] != '#'){
				DRF.values.push_back(myregisters.read(operand));
				DRF.valids.push_back(myregisters.isValid(operand));
			}
		}

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "EX-OR"){

		for (auto &operand : DRF.operands){
			if(operand[0] != '#'){
				DRF.values.push_back(myregisters.read(operand));
				DRF.valids.push_back(myregisters.isValid(operand));
			}
		}

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "LOAD"){

		for (auto &operand : DRF.operands){
			if(operand[0] != '#'){
				DRF.values.push_back(myregisters.read(operand));
				DRF.valids.push_back(myregisters.isValid(operand));
			}
		}

		DRF.values.push_back(DRF.littoi(DRF.operands.at(2)));
		DRF.valids.push_back(true);

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "STORE"){

		for (auto &operand : DRF.operands){
			if(operand[0] != '#'){
				DRF.values.push_back(myregisters.read(operand));
				DRF.valids.push_back(myregisters.isValid(operand));
			}
		}

		DRF.values.push_back(DRF.littoi(DRF.operands.at(2)));
		DRF.valids.push_back(true);

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "BZ"){

		DRF.values.push_back(DRF.littoi(DRF.operands.at(0)));
		DRF.valids.push_back(true);

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "BNZ"){

		DRF.values.push_back(DRF.littoi(DRF.operands.at(0)));
		DRF.valids.push_back(true);

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "BAL"){

		DRF.values.push_back(myregisters.read(DRF.operands.at(0)));
		DRF.valids.push_back(myregisters.isValid(DRF.operands.at(0)));

		DRF.values.push_back(DRF.littoi(DRF.operands.at(1)));
		DRF.valids.push_back(true);

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "JUMP"){

		DRF.values.push_back(myregisters.read(DRF.operands.at(0)));
		DRF.valids.push_back(myregisters.isValid(DRF.operands.at(0)));

		DRF.values.push_back(DRF.littoi(DRF.operands.at(1)));
		DRF.valids.push_back(true);

		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "HALT"){
		DRF.isEmpty = false;
	}
	else if (DRF.opcode == "NOP"){
		DRF.isEmpty = false;
	}
	else{
		std::cerr << "Unresolvable opcode: " << DRF.opcode << std::endl;
		exit(1);
	}

	//F Stage
	if (F.isEmpty == true){
		F.initialize();
		std::vector<std::string> instr = mycode.getInstr(pc);

		F.pc = pc;
		F.opcode = instr.at(0);
		for (int i=1;i<instr.size();i++){
			F.operands.push_back(instr.at(i));
		}
		F.isEmpty = false;
		F.isReady = true;
	}

/******************************************************************************/
/************************STAGE ADVANCEMENT PHASE*******************************/
/******************************************************************************/

	//WB Stage
	if (WB.opcode == "ADD"){

	}
	else if (WB.opcode == "SUB") {

	}
	else if (WB.opcode == "MOVC"){

	}
	else if (WB.opcode == "MUL"){

	}
	else if (WB.opcode == "AND"){

	}
	else if (WB.opcode == "OR"){

	}
	else if (WB.opcode == "EX-OR"){

	}
	else if (WB.opcode == "LOAD"){

	}
	else if (WB.opcode == "STORE"){

	}
	else if (WB.opcode == "BZ"){

	}
	else if (WB.opcode == "BNZ"){

	}
	else if (WB.opcode == "BAL"){

	}
	else if (WB.opcode == "JUMP"){

	}
	else if (WB.opcode == "HALT"){

	}
	else if (WB.opcode == "NOP"){

	}
	else{
		std::cerr << "Unresolvable opcode: " << WB.opcode << std::endl;
		exit(1);
	}

	//M Stage
	if (M.opcode == "ADD"){

	}
	else if (M.opcode == "SUB") {

	}
	else if (M.opcode == "MOVC"){

	}
	else if (M.opcode == "MUL"){

	}
	else if (M.opcode == "AND"){

	}
	else if (M.opcode == "OR"){

	}
	else if (M.opcode == "EX-OR"){

	}
	else if (M.opcode == "LOAD"){

	}
	else if (M.opcode == "STORE"){

	}
	else if (M.opcode == "BZ"){

	}
	else if (M.opcode == "BNZ"){

	}
	else if (M.opcode == "BAL"){

	}
	else if (M.opcode == "JUMP"){

	}
	else if (M.opcode == "HALT"){

	}
	else if (M.opcode == "NOP"){

	}
	else{
		std::cerr << "Unresolvable opcode: " << M.opcode << std::endl;
		exit(1);
	}

	//D Stage
	if (D.opcode == "BZ"){

	}
	else if (D.opcode == "BNZ"){

	}
	else if (D.opcode == "BAL"){

	}
	else if (D.opcode == "JUMP"){

	}
	else{
		std::cerr << "Unresolvable opcode: " << D.opcode << std::endl;
		exit(1);
	}

	//B Stage
	if (B.opcode == "BZ" ||
			B.opcode == "BNZ" ||
			B.opcode == "BAL" ||
			B.opcode == "JUMP"){
		if (D.isEmpty == true && B.isEmpty == false && B.isReady == true){
			D.pc = B.pc;
			D.opcode = B.opcode;
			for (auto &operand : B.operands){
				D.operands.push_back(operand);
			}
			B.isEmpty = true;
			B.isReady = false;
		}
	}
	else{
		std::cerr << "Unresolvable opcode: " << B.opcode << std::endl;
		exit(1);
	}

	//ALU2 Stage
	if (ALU2.opcode == "ADD" ||
		ALU2.opcode == "SUB" ||
		ALU2.opcode == "MUL" ||
		ALU2.opcode == "AND" ||
		ALU2.opcode == "OR" ||
		ALU2.opcode == "EX-OR" ||
		ALU2.opcode == "MOVC" ||
		ALU2.opcode == "LOAD" ||
		ALU2.opcode == "STORE"){
		if (M.isEmpty == true && ALU2.isEmpty == false && ALU2.isReady == true){
			M.pc = ALU2.pc;
			M.opcode = ALU2.opcode;

			for (auto &operand : ALU2.operands){
				M.operands.push_back(operand);
			}

			ALU2.isEmpty = true;
			ALU2.isReady = false;
		}

	}
	else if (ALU2.opcode == "HALT" ||
		ALU2.opcode == "NOP"){
		if (M.isEmpty == true && ALU2.isEmpty == false && ALU2.isReady == true){
			M.pc = ALU2.pc;
			M.opcode = ALU2.opcode;

			for (auto &operand : ALU2.operands){
				M.operands.push_back(operand);
			}

			ALU2.isEmpty = true;
			ALU2.isReady = true;
		}

	}
	else{
		std::cerr << "Unresolvable opcode: " << ALU2.opcode << std::endl;
		exit(1);
	}

	//ALU1 Stage
	if (ALU1.opcode == "ADD" ||
		ALU1.opcode == "SUB" ||
		ALU1.opcode == "MUL" ||
		ALU1.opcode == "AND" ||
		ALU1.opcode == "OR" ||
		ALU1.opcode == "EX-OR" ||
		ALU1.opcode == "MOVC" ||
		ALU1.opcode == "LOAD" ||
		ALU1.opcode == "STORE"){
		if (ALU2.isEmpty == true && ALU1.isEmpty == false && ALU1.isReady == true){
			ALU2.pc = ALU1.pc;
			ALU2.opcode = ALU1.opcode;

			for (auto &operand : ALU1.operands){
				ALU2.operands.push_back(operand);
			}

			ALU1.isEmpty = true;
			ALU1.isReady = false;
		}
	}
	else if (ALU1.opcode == "HALT" ||
		ALU1.opcode == "NOP"){
		if (ALU2.isEmpty == true && ALU1.isEmpty == false && ALU1.isReady == true){
			ALU2.pc = ALU1.pc;
			ALU2.opcode = ALU1.opcode;

			ALU1.isEmpty = true;
			ALU1.isReady = true;
		}
	}
	else{
		std::cerr << "Unresolvable opcode: " << ALU1.opcode << std::endl;
		exit(1);
	}

	//DRF Stage
	if (DRF.opcode == "ADD" ||
		DRF.opcode == "SUB" ||
		DRF.opcode == "MUL" ||
		DRF.opcode == "AND" ||
		DRF.opcode == "OR" ||
		DRF.opcode == "EX-OR" ||
		DRF.opcode == "LOAD"){
		if (ALU1.isEmpty == true && DRF.isEmpty == false && DRF.isReady == true){
			if (DRF.valids.at(1) == true && DRF.valids.at(2) == true){
				ALU1.pc = DRF.pc;
				ALU1.opcode = DRF.opcode;

				for (auto &operand : DRF.operands){
					ALU1.operands.push_back(operand);
				}

				DRF.isEmpty = true;
				DRF.isReady = false;
			}
		}
	}
	else if (DRF.opcode == "MOVC"){
		if (ALU1.isEmpty == true && DRF.isEmpty == false && DRF.isReady == true){
			if (DRF.valids.at(1) == true){
				ALU1.isEmpty = false;
				ALU1.isReady = false;
				ALU1.pc = DRF.pc;
				ALU1.opcode = DRF.opcode;

				for (auto &operand : DRF.operands){
					ALU1.operands.push_back(operand);
				}

				DRF.isEmpty = true;
				DRF.isReady = false;
			}
		}
	}
	else if (DRF.opcode == "STORE"){
		if (ALU1.isEmpty == true && DRF.isEmpty == false && DRF.isReady == true){
			if (DRF.valids.at(0) == true && DRF.valids.at(2) == true){
				ALU1.isEmpty = false;
				ALU1.isReady = false;
				ALU1.pc = DRF.pc;
				ALU1.opcode = DRF.opcode;

				for (auto &operand : DRF.operands){
					ALU1.operands.push_back(operand);
				}

				DRF.isEmpty = true;
				DRF.isReady = false;
			}
		}
	}
	else if (DRF.opcode == "BZ" || DRF.opcode == "BNZ"){
		if (ALU1.isEmpty == true && DRF.isEmpty == false && DRF.isReady == true){
			if (DRF.valids.at(0) == true){
				ALU1.isEmpty = false;
				ALU1.isReady = false;
				ALU1.pc = DRF.pc;
				ALU1.opcode = DRF.opcode;

				for (auto &operand : DRF.operands){
					ALU1.operands.push_back(operand);
				}

				DRF.isEmpty = true;
				DRF.isReady = false;
			}
		}
	}
	else if (DRF.opcode == "BAL" || DRF.opcode == "JUMP"){
		if (ALU1.isEmpty == true && DRF.isEmpty == false && DRF.isReady == true){
			if (DRF.valids.at(0) == true && DRF.valids.at(1) == true){
				ALU1.isEmpty = false;
				ALU1.isReady = false;
				ALU1.pc = DRF.pc;
				ALU1.opcode = DRF.opcode;

				for (auto &operand : DRF.operands){
					ALU1.operands.push_back(operand);
				}

				DRF.isEmpty = true;
				DRF.isReady = false;
			}
		}
	}
	else if (DRF.opcode == "HALT" ||
		DRF.opcode == "NOP"){
		if (ALU1.isEmpty == true && DRF.isEmpty == false && DRF.isReady == true){
			ALU1.isEmpty = false;
			ALU1.isReady = false;
			ALU1.pc = DRF.pc;
			ALU1.opcode = DRF.opcode;

			DRF.isEmpty = true;
			DRF.isReady = false;
		}
	}
	else{
		std::cerr << "Unresolvable opcode: " << DRF.opcode << std::endl;
		exit(1);
	} //END DRF Stage

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

		if (DRF.isEmpty == true){
			DRF.isEmpty = false;
			DRF.isReady = false;
			DRF.pc = F.pc;
			DRF.opcode = F.opcode;
			for (auto &operand : F.operands){
				DRF.operands.push_back(operand);
			}
			F.isEmpty = true;
			F.isReady = false;
		}
	} //END F stage


	else{
		std::cerr << "Unresolvable opcode: " << F.opcode << std::endl;
		exit(1);
	}

	return 0; //Return for compile testing
}
