#define FORWARDING 0
#include "cpu.h"

int CPU::simulate(Code &mycode, Registers &myregisters, Data &mydata){

	/********WORK PHASE*********/
	//F Stage
	if (F.opcode == "ADD"){

	}
	else if (F.opcode == "SUB") {
		/* code */
	}
	else if (F.opcode == "MOVC"){

	}
	else if (F.opcode == "MUL"){

	}
	else if (F.opcode == "AND"){

	}
	else if (F.opcode == "OR"){

	}
	else if (F.opcode == "EX-OR"){

	}
	else if (F.opcode == "LOAD"){

	}
	else if (F.opcode == "STORE"){

	}
	else if (F.opcode == "BZ"){

	}
	else if (F.opcode == "BNZ"){

	}
	else if (F.opcode == "BAL"){

	}
	else if (F.opcode == "JUMP"){

	}
	else if (F.opcode == "HALT"){

	}
	else if (F.opcode == "NOP"){

	}
	else{
		std::cerr << "Unresolvable opcode: " << F.opcode << std::endl;
		exit(1);
	}

	//DRF Stage
	if (DRF.opcode == "ADD"){

	}
	else if (DRF.opcode == "SUB") {
		/* code */
	}
	else if (DRF.opcode == "MOVC"){

	}
	else if (DRF.opcode == "MUL"){

	}
	else if (DRF.opcode == "AND"){

	}
	else if (DRF.opcode == "OR"){

	}
	else if (DRF.opcode == "EX-OR"){

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

	//B Stage
	if (B.opcode == "ADD"){

	}
	else if (B.opcode == "SUB") {
		/* code */
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

	//D Stage
	if (D.opcode == "ADD"){

	}
	else if (D.opcode == "SUB") {
		/* code */
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

#if 0
	/*****FORWARDING PHASE*****/
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
	if (DRF.opcode == "ADD"){

	}
	else if (DRF.opcode == "SUB") {

	}
	else if (DRF.opcode == "MOVC"){

	}
	else if (DRF.opcode == "MUL"){

	}
	else if (DRF.opcode == "AND"){

	}
	else if (DRF.opcode == "OR"){

	}
	else if (DRF.opcode == "EX-OR"){

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
	if (F.opcode == "ADD"){

	}
	else if (F.opcode == "SUB") {

	}
	else if (F.opcode == "MOVC"){

	}
	else if (F.opcode == "MUL"){

	}
	else if (F.opcode == "AND"){

	}
	else if (F.opcode == "OR"){

	}
	else if (F.opcode == "EX-OR"){

	}
	else if (F.opcode == "LOAD"){

	}
	else if (F.opcode == "STORE"){

	}
	else if (F.opcode == "BZ"){

	}
	else if (F.opcode == "BNZ"){

	}
	else if (F.opcode == "BAL"){

	}
	else if (F.opcode == "JUMP"){

	}
	else if (F.opcode == "HALT"){

	}
	else if (F.opcode == "NOP"){

	}
	else{
		std::cerr << "Unresolvable opcode: " << F.opcode << std::endl;
		exit(1);
	}
#endif

	/*****STAGE ADVANCEMENT PHASE*****/
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
	if (DRF.opcode == "ADD"){

	}
	else if (DRF.opcode == "SUB") {

	}
	else if (DRF.opcode == "MOVC"){

	}
	else if (DRF.opcode == "MUL"){

	}
	else if (DRF.opcode == "AND"){

	}
	else if (DRF.opcode == "OR"){

	}
	else if (DRF.opcode == "EX-OR"){

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
	if (F.opcode == "ADD"){

	}
	else if (F.opcode == "SUB") {

	}
	else if (F.opcode == "MOVC"){

	}
	else if (F.opcode == "MUL"){

	}
	else if (F.opcode == "AND"){

	}
	else if (F.opcode == "OR"){

	}
	else if (F.opcode == "EX-OR"){

	}
	else if (F.opcode == "LOAD"){

	}
	else if (F.opcode == "STORE"){

	}
	else if (F.opcode == "BZ"){

	}
	else if (F.opcode == "BNZ"){

	}
	else if (F.opcode == "BAL"){

	}
	else if (F.opcode == "JUMP"){

	}
	else if (F.opcode == "HALT"){

	}
	else if (F.opcode == "NOP"){

	}
	else{
		std::cerr << "Unresolvable opcode: " << F.opcode << std::endl;
		exit(1);
	}

	return 0; //Temporary declare for compile test
}
