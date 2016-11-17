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
	if (WB.opcode == "ADD"){
		myregisters.write(WB.operands.at(0), WB.values.at(0), WB.valids.at(0));

		WB.isEmpty = false;
	}
	else if (WB.opcode == "SUB") {
		myregisters.write(WB.operands.at(0), WB.values.at(0), WB.valids.at(0));

		WB.isEmpty = false;
	}
	else if (WB.opcode == "MOVC"){
		myregisters.write(WB.operands.at(0), WB.values.at(0), WB.valids.at(0));

		WB.isEmpty = false;
	}
	else if (WB.opcode == "MUL"){
		myregisters.write(WB.operands.at(0), WB.values.at(0), WB.valids.at(0));

		WB.isEmpty = false;
	}
	else if (WB.opcode == "AND"){
		myregisters.write(WB.operands.at(0), WB.values.at(0), WB.valids.at(0));

		WB.isEmpty = false;
	}
	else if (WB.opcode == "OR"){
		myregisters.write(WB.operands.at(0), WB.values.at(0), WB.valids.at(0));

		WB.isEmpty = false;
	}
	else if (WB.opcode == "EX-OR"){
		myregisters.write(WB.operands.at(0), WB.values.at(0), WB.valids.at(0));

		WB.isEmpty = false;
	}
	else if (WB.opcode == "LOAD"){
		myregisters.write(WB.operands.at(0), WB.values.at(0), WB.valids.at(0));
		WB.isEmpty = false;
	}
	else if (WB.opcode == "STORE"){
		WB.isEmpty = false;
	}
	else if (WB.opcode == "BZ"){
		WB.isEmpty = false;
	}
	else if (WB.opcode == "BNZ"){
		WB.isEmpty = false;
	}
	else if (WB.opcode == "BAL"){
		WB.isEmpty = false;
	}
	else if (WB.opcode == "JUMP"){
		WB.isEmpty = false;
	}
	else if (WB.opcode == "HALT"){
		return 0; //Terminate program
		WB.isEmpty = false;
	}
	else if (WB.opcode == "NOP"){
		WB.isEmpty = false;
	}
	else{
		std::cerr << "Unresolvable opcode: " << WB.opcode << std::endl;
		exit(1);
	}

	//M Stage
	if (M.opcode == "ADD"){
		M.isEmpty = false;
	}
	else if (M.opcode == "SUB") {
		M.isEmpty = false;
	}
	else if (M.opcode == "MOVC"){
		M.isEmpty = false;
	}
	else if (M.opcode == "MUL"){
		M.isEmpty = false;
	}
	else if (M.opcode == "AND"){
		M.isEmpty = false;
	}
	else if (M.opcode == "OR"){
		M.isEmpty = false;
	}
	else if (M.opcode == "EX-OR"){
		M.isEmpty = false;
	}
	else if (M.opcode == "LOAD"){
		M.values.at(0) = mydata.readMem(M.values.at(1));
		M.valids.at(0) = true;

		M.isEmpty = false;
	}
	else if (M.opcode == "STORE"){
		mydata.writeMem(M.values.at(1), M.values.at(0));
		M.valids.at(0) = true;

		M.isEmpty = false;
	}
	else if (M.opcode == "BZ"){
		M.isEmpty = false;
	}
	else if (M.opcode == "BNZ"){
		M.isEmpty = false;
	}
	else if (M.opcode == "BAL"){
		M.isEmpty = false;
	}
	else if (M.opcode == "JUMP"){
		M.isEmpty = false;
	}
	else if (M.opcode == "HALT"){
		M.isEmpty = false;
	}
	else if (M.opcode == "NOP"){
		M.isEmpty = false;
	}
	else{
		std::cerr << "Unresolvable opcode: " << M.opcode << std::endl;
		exit(1);
	}

	//D Stage
	if (D.opcode == "BZ"){
		D.isEmpty = false;
	}
	else if (D.opcode == "BNZ"){
		D.isEmpty = false;
	}
	else if (D.opcode == "BAL"){
		D.isEmpty = false;
	}
	else if (D.opcode == "JUMP"){
		D.isEmpty = false;
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
	if (ALU2.opcode == "ADD"){
		ALU1.values.at(0) = ALU1.values.at(1) + ALU1.values.at(2);
		ALU1.valids.at(0) = true;

		if (ALU2.values.at(0) == 0){
			myregisters.write("Z", 1, 1);
		}

		ALU2.isEmpty = false;

	}
	else if (ALU2.opcode == "SUB") {
		ALU1.values.at(0) = ALU1.values.at(1) - ALU1.values.at(2);
		ALU1.valids.at(0) = true;

		if (ALU2.values.at(0) == 0){
			myregisters.write("Z", 1, 1);
		}

		ALU2.isEmpty = false;
	}
	else if (ALU2.opcode == "MOVC"){
		ALU1.values.at(0) = ALU1.values.at(1) + 0;
		ALU1.valids.at(0) = true;

		ALU2.isEmpty = false;
	}
	else if (ALU2.opcode == "MUL"){
		ALU1.values.at(0) = ALU1.values.at(1) * ALU1.values.at(2);
		ALU1.valids.at(0) = true;

		if (ALU2.values.at(0) == 0){
			myregisters.write("Z", 1, 1);
		}

		ALU2.isEmpty = false;
	}
	else if (ALU2.opcode == "AND"){
		ALU1.values.at(0) = ALU1.values.at(1) & ALU1.values.at(2);
		ALU1.valids.at(0) = true;

		if (ALU2.values.at(0) == 0){
			myregisters.write("Z", 1, 1);
		}

		ALU2.isEmpty = false;
	}
	else if (ALU2.opcode == "OR"){
		ALU1.values.at(0) = ALU1.values.at(1) | ALU1.values.at(2);
		ALU1.valids.at(0) = true;

		if (ALU2.values.at(0) == 0){
			myregisters.write("Z", 1, 1);
		}

		ALU2.isEmpty = false;
	}
	else if (ALU2.opcode == "EX-OR"){
		ALU1.values.at(0) = ALU1.values.at(1) ^ ALU1.values.at(2);
		ALU1.valids.at(0) = true;

		if (ALU2.values.at(0) == 0){
			myregisters.write("Z", 1, 1);
		}

		ALU2.isEmpty = false;
	}
	else if (ALU2.opcode == "LOAD"){
		ALU1.values.at(1) = ALU1.values.at(1) + ALU1.values.at(2);
		ALU1.valids.at(1) = true;

		ALU2.isEmpty = false;
	}
	else if (ALU2.opcode == "STORE"){
		ALU1.values.at(1) = ALU1.values.at(1) + ALU1.values.at(2);
		ALU1.valids.at(1) = true;

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
	if (ALU1.opcode == "ADD"){
		ALU1.isEmpty = false;
	}
	else if (ALU1.opcode == "SUB") {
		ALU1.isEmpty = false;
	}
	else if (ALU1.opcode == "MOVC"){
		ALU1.isEmpty = false;
	}
	else if (ALU1.opcode == "MUL"){
		ALU1.isEmpty = false;
	}
	else if (ALU1.opcode == "AND"){
		ALU1.isEmpty = false;
	}
	else if (ALU1.opcode == "OR"){
		ALU1.isEmpty = false;
	}
	else if (ALU1.opcode == "EX-OR"){
		ALU1.isEmpty = false;
	}
	else if (ALU1.opcode == "LOAD"){
		ALU1.isEmpty = false;
	}
	else if (ALU1.opcode == "STORE"){
		ALU1.isEmpty = false;
	}
	else if (ALU1.opcode == "HALT"){
		ALU1.isEmpty = false;
	}
	else if (ALU1.opcode == "NOP"){
		ALU1.isEmpty = false;
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
	if (D.opcode == "ADD"){

	}
	else if (D.opcode == "SUB") {

	}
	else if (D.opcode == "MOVC"){

	}
	else if (D.opcode == "MUL"){

	}
	else if (D.opcode == "AND"){

	}
	else if (D.opcode == "OR"){

	}
	else if (D.opcode == "EX-OR"){

	}
	else if (D.opcode == "LOAD"){

	}
	else if (D.opcode == "STORE"){

	}
	else if (D.opcode == "BZ"){

	}
	else if (D.opcode == "BNZ"){

	}
	else if (D.opcode == "BAL"){

	}
	else if (D.opcode == "JUMP"){

	}
	else if (D.opcode == "HALT"){

	}
	else if (D.opcode == "NOP"){

	}
	else{
		std::cerr << "Unresolvable opcode: " << D.opcode << std::endl;
		exit(1);
	}

	//B Stage
	if (B.opcode == "ADD"){

	}
	else if (B.opcode == "SUB") {

	}
	else if (B.opcode == "MOVC"){

	}
	else if (B.opcode == "MUL"){

	}
	else if (B.opcode == "AND"){

	}
	else if (B.opcode == "OR"){

	}
	else if (B.opcode == "EX-OR"){

	}
	else if (B.opcode == "LOAD"){

	}
	else if (B.opcode == "STORE"){

	}
	else if (B.opcode == "BZ"){

	}
	else if (B.opcode == "BNZ"){

	}
	else if (B.opcode == "BAL"){

	}
	else if (B.opcode == "JUMP"){

	}
	else if (B.opcode == "HALT"){

	}
	else if (B.opcode == "NOP"){

	}
	else{
		std::cerr << "Unresolvable opcode: " << B.opcode << std::endl;
		exit(1);
	}

	//ALU2 Stage
	if (ALU2.opcode == "ADD"){

	}
	else if (ALU2.opcode == "SUB") {

	}
	else if (ALU2.opcode == "MOVC"){

	}
	else if (ALU2.opcode == "MUL"){

	}
	else if (ALU2.opcode == "AND"){

	}
	else if (ALU2.opcode == "OR"){

	}
	else if (ALU2.opcode == "EX-OR"){

	}
	else if (ALU2.opcode == "LOAD"){

	}
	else if (ALU2.opcode == "STORE"){

	}
	else if (ALU2.opcode == "BZ"){

	}
	else if (ALU2.opcode == "BNZ"){

	}
	else if (ALU2.opcode == "BAL"){

	}
	else if (ALU2.opcode == "JUMP"){

	}
	else if (ALU2.opcode == "HALT"){

	}
	else if (ALU2.opcode == "NOP"){

	}
	else{
		std::cerr << "Unresolvable opcode: " << ALU2.opcode << std::endl;
		exit(1);
	}

	//ALU1 Stage
	if (ALU1.opcode == "ADD"){

	}
	else if (ALU1.opcode == "SUB") {

	}
	else if (ALU1.opcode == "MOVC"){

	}
	else if (ALU1.opcode == "MUL"){

	}
	else if (ALU1.opcode == "AND"){

	}
	else if (ALU1.opcode == "OR"){

	}
	else if (ALU1.opcode == "EX-OR"){

	}
	else if (ALU1.opcode == "LOAD"){

	}
	else if (ALU1.opcode == "STORE"){

	}
	else if (ALU1.opcode == "BZ"){

	}
	else if (ALU1.opcode == "BNZ"){

	}
	else if (ALU1.opcode == "BAL"){

	}
	else if (ALU1.opcode == "JUMP"){

	}
	else if (ALU1.opcode == "HALT"){

	}
	else if (ALU1.opcode == "NOP"){

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
		DRF.opcode == "EX-OR"){
		if (ALU1.isEmpty == true && DRF.isEmpty == false && DRF.isReady == true;){
			if (DRF.valids.at(1) == true && DRF.valids.at(2) == true){
				ALU1.pc = DRF.pc;
				ALU1.opcode = DRF.opcode;
			}
		}

	}
	else if (DRF.opcode == "MOVC"){
		if (ALU1.isEmpty == true && DRF.isEmpty == false && DRF.isReady == true;){
			if (DRF.valids.at(1) == true){
				ALU1.pc = DRF.pc;
				ALU1.opcode = DRF.opcode;
			}

	}
	else if (DRF.opcode == "LOAD"){

	}
	else if (DRF.opcode == "STORE"){

	}
	else if (DRF.opcode == "BZ"){

	}
	else if (DRF.opcode == "BNZ"){

	}
	else if (DRF.opcode == "BAL"){

	}
	else if (DRF.opcode == "JUMP"){

	}
	else if (DRF.opcode == "HALT"){

	}
	else if (DRF.opcode == "NOP"){

	}
	else{
		std::cerr << "Unresolvable opcode: " << DRF.opcode << std::endl;
		exit(1);
	}

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
			DRF.pc = F.pc;
			DRF.opcode = F.opcode;
			for (auto &operand : F.operands){
				DRF.operands.push_back(operands);
			}

			F.isEmpty = true;
			F.isReady = false;

		} //TODO verify booleans to set
	}


	else{
		std::cerr << "Unresolvable opcode: " << F.opcode << std::endl;
		exit(1);
	}

	return 0; //Return for compile testing
}
