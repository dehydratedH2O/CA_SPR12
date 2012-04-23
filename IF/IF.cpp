#include <string>
#include <iostream>
#include <vector>
#include "IF.h"
#include "../UTIL/MEMSlot.h"
#include "../UTIL/utils.h"

using namespace std;

extern int MAXMEM;
extern vector<MEMSlot> IMEM;
extern int BANDWIDTH;
extern int doBr;
extern string branchLoc;

//CONSTRUCTOR
IF::IF (void)
{
	PC = "0000000000000000";
	NOP = 0;
	incPC = "";
	instruction = "";
	control = "";
	NOPctr = 0;
}
	
int IF::fetchInstruction(void)
{
	if(btoi(PC) > MAXMEM)
		return -1;
		
	if(btoi(PC) < 0)
		return -1;
	
	int location = btoi(PC);
	int vecloc = location/2;
	
	instruction = IMEM[vecloc].data;
	cout << "PC IN IF: " << PC << endl;
	cout << "INSTRUC IN IF: " << instruction << endl;
	cout << "NOPVAL: " << NOP << endl;
	
	return 0;
}

int IF::incrementPC(void)
{
	int PCVal = btoi(PC);
	
	if(PCVal > 0xFFFB)
		return -1;
	else PCVal = PCVal + 2;
	
	incPC = itob(PCVal,16);
	
	return 0;
}
	
/*
	
<--------------------------------------------------->
<--------------Control Signals Design -------------->
<--------------------------------------------------->


<--------------------------------------------------->
BIT 0
<--------------------------------------------------->
RegWrite

--Is anything being written to the registers?


<--------------------------------------------------->
BIT 1
<--------------------------------------------------->
R/I Type

--Is it an R (0) or I (1) type instruction?
--(J-Type gets 0)


<--------------------------------------------------->
BITS 3 - 7
<--------------------------------------------------->
ALUOP

--Defines what operation the ALU will run.
--Full list in Control Signals.xlsx


<--------------------------------------------------->
BIT 8
<--------------------------------------------------->
MemWrite

--Is anything being written to Data Memory?


<--------------------------------------------------->
BIT 9
<--------------------------------------------------->
MemRead

--Is anything being read from Data Memory?


<--------------------------------------------------->
BIT 10
<--------------------------------------------------->
MemToReg

--Is any value being passed from Data Memory to
--the register file?


<--------------------------------------------------->
BIT 11
<--------------------------------------------------->
J-Type

--Is this instruction a J-Type instruction?


<--------------------------------------------------->
BIT 12
<--------------------------------------------------->
Branch

--Is this instruction a branch instruction?


<--------------------------------------------------->
BIT 13
<--------------------------------------------------->
LogComp

--Is this instruction a logical comparison?
--NOTE: This value is 0 for branches that use
--logical comparisons within them.
	
*/
	
int IF::determineControlSignals(void)
{
	string instr = "";
	for(int i = 0; i < BANDWIDTH; i++)
	{
		instr += instruction[i];
	}
	
	string opcode = instr.substr(0, 4);
	string func = instr.substr(13, 3);
	string controlSignals = "";
	
	if((opcode == "1110") || (opcode == "1111"))
		return -1;
	if((opcode == "0000") && ((func == "110") || (func == "111")))
		return -1;
	if((opcode == "0001") && ((func == "100") || (func == "101") || (func == "110") || (func == "111")))
		return -1;
	
	if(opcode == "0000")
	{
		if(func == "000")
			controlSignals = "1000000000000";
		if(func == "001")
			controlSignals = "1000001000000";
		if(func == "010")
			controlSignals = "1000010000001";
		if(func == "011")
			controlSignals = "1000011000001";
		if(func == "100")
			controlSignals = "1000100000001";
		if(func == "101")
			controlSignals = "1000101000001";
	}
	if(opcode == "0001")
	{
		if(func == "000")
			controlSignals = "1000110000000";
		if(func == "001")
			controlSignals = "1000111000000";
		if(func == "010")
			controlSignals = "1001000000000";
		if(func == "011")
			controlSignals = "1001001000000";
	}
	if(opcode == "0010")
		controlSignals = "1101010000000";
	if(opcode == "0011")
		controlSignals = "1101011000000";
	if(opcode == "0100")
		controlSignals = "0101100000010";
	if(opcode == "0101")
		controlSignals = "0101101000010";
	if(opcode == "0110")
		controlSignals = "0101110000010";
	if(opcode == "0111")
		controlSignals = "0101111000010";
	if(opcode == "1000")
		controlSignals = "0110000000010";
	if(opcode == "1001")
		controlSignals = "1110001000000";
	if(opcode == "1010")
		controlSignals = "1110010000000";
	if(opcode == "1011")
		controlSignals = "1110011001000";
	if(opcode == "1100")
		controlSignals = "0110100110000";
	if(opcode == "1101")
		controlSignals = "0000000000100";

	control = controlSignals;
	return 0;
}

void IF::calcNOPs(void)
{
	string instr = "";
	for(int i = 0; i < BANDWIDTH; i++)
	{
		instr += instruction[i];
	}
	string opcode = instr.substr(0, 4);

	if(opcode == "1011" /* LW */)
		NOP = 1;
	
	if((opcode == "0100") || (opcode == "0101") || (opcode == "0110") || (opcode == "0111") || (opcode == "1000") /*branches*/)
	{
		NOPctr = 1;
		NOP = 1;
	}

	if(opcode == "1101")
		NOP = 1;

	return;	
}

void IF::perform(void)
{
	NOP = 0;
	calcNOPs();
	cout <<"NOP: " << NOP << endl;

			int rc = fetchInstruction();
		if(rc == -1)
		{
			cout << "ERROR IN INSTRUCTION FETCH." << endl;
			cout << "ERROR IN GETTING INSTRUCTION." << endl;
		}

	if((NOP == 0))
	{	
		if (NOPctr == 1)
		{
			NOPctr--;
			NOP = 1;
			return;
		}

		if(NOP == 0)
		{
			rc = determineControlSignals();
			if(rc == -1)
			{
				cout << "ERROR IN INSTRUCTION FETCH." << endl;
				cout << "ERROR IN DETERMINING CONTROL SIGNALS." << endl;
			}
			cout << "PC BEFORE INC: " << incPC << endl;
			rc = incrementPC();
			cout << "PC AFTER INC: " << incPC << endl;
			if(rc == -1)
			{
				cout << "ERROR IN INSTRUCTION FETCH." << endl;
				cout << "ERROR IN INCREMENTING PC." << endl;
			}
		}
	}
}

