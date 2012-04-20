#include <iostream>
#include <string>
#include <vector>
#include "ID.h"
#include "../UTIL/MEMSlot.h"

using namespace std;

extern vector<MEMSlot> Regs;
extern string tmpWReg;

ID::ID(void)
{
	instruction = "";
	PCin = "";
	NOP = 0;
	PCout = "";
	RSVal = "";
	RTVal = "";
	signExtendedImmediate = "";
	
	control = "";
}

int ID::doJump(void)
{
	if(control[11] == '0')
		return 0;
	
	//First, extract address from instruction
	string tmpPC = instruction.substr(4, 12);
	
	//Next, shift left 1 bit
	tmpPC += "0";
	
	//Then, copy the first 3 bits of the PC
	PCout = PCin.substr(0, 3);
	PCout += tmpPC;
	
	return 0;
}

int ID::getRegistersFromFile(void)
{
	if(instruction.length() != 16)
		return -1;

	tmpWReg = instruction.substr(4, 3);
	
	//CODE GOES HERE TO GET REGISTERS FROM FILE
	
	string opcode = instruction.substr(0, 4);
	string rs, rt;
	
	// R-type
	if((opcode == "0000") || (opcode == "0001"))
	{
		rs = instruction.substr(7, 3);
		rt = instruction.substr(10, 3);
		
		// Set RSVal
		if(rs == "000")
			RSVal = Regs[0].data;
		else if(rs == "001")
			RSVal = Regs[1].data;
		else if(rs == "010")
			RSVal = Regs[2].data;
		else if(rs == "011")
			RSVal = Regs[3].data;
		else if(rs == "100")
			RSVal = Regs[4].data;
		else if(rs == "101")
			RSVal = Regs[5].data;
		else if(rs == "110")
			RSVal = Regs[6].data;
		else if(rs == "111")
			RSVal = Regs[7].data;
		
		// Set RTVal
		if(rt == "000")
			RTVal = Regs[0].data;
		else if(rt == "001")
			RTVal = Regs[1].data;
		else if(rt == "010")
			RTVal = Regs[2].data;
		else if(rt == "011")
			RTVal = Regs[3].data;
		else if(rt == "100")
			RTVal = Regs[4].data;
		else if(rt == "101")
			RTVal = Regs[5].data;
		else if(rt == "110")
			RTVal = Regs[6].data;
		else if(rt == "111")
			RTVal = Regs[7].data;
	}
	else // I-type
	{
		rs = instruction.substr(4, 3);
		rt = instruction.substr(7, 3);
		
		// Set RSVal
		if(rs == "000")
			RSVal = Regs[0].data;
		else if(rs == "001")
			RSVal = Regs[1].data;
		else if(rs == "010")
			RSVal = Regs[2].data;
		else if(rs == "011")
			RSVal = Regs[3].data;
		else if(rs == "100")
			RSVal = Regs[4].data;
		else if(rs == "101")
			RSVal = Regs[5].data;
		else if(rs == "110")
			RSVal = Regs[6].data;
		else if(rs == "111")
			RSVal = Regs[7].data;
		
		// Set RTVal
		if(rt == "000")
			RTVal = Regs[0].data;
		else if(rt == "001")
			RTVal = Regs[1].data;
		else if(rt == "010")
			RTVal = Regs[2].data;
		else if(rt == "011")
			RTVal = Regs[3].data;
		else if(rt == "100")
			RTVal = Regs[4].data;
		else if(rt == "101")
			RTVal = Regs[5].data;
		else if(rt == "110")
			RTVal = Regs[6].data;
		else if(rt == "111")
			RTVal = Regs[7].data;
	}
	
	return 0;
}

int ID::signExtendImmediate(void)
{
	if(instruction.length() != 16)
		return -1;
	
	string immediate = instruction.substr(10, 6);
	
	if((immediate.at(0) != '0') && (immediate.at(0) != '1'))
		return -1;
		
	string SEImmediate = "";
	if(immediate.at(0) == '0')
		SEImmediate = "0000000000";
	if(immediate.at(0) == '1')
		SEImmediate = "1111111111";
	SEImmediate += immediate;
	
	signExtendedImmediate = SEImmediate;
	return 0;
}

void ID::perform(void)
{
	if(NOP == 0)
	{
		int rc = doJump();
		if(rc == -1)
		{
			cout << "ERROR IN INSTRUCTION DECODE." << endl;
			cout << "ERROR IN JUMP DECISION/EXECUTION." << endl;
		}
	
		rc = getRegistersFromFile();
		if(rc == -1)
		{
			cout << "ERROR IN INSTRUCTION DECODE." << endl;
			cout << "ERROR IN OBTAINING REGISTERS." << endl;
		}
	
		rc = signExtendImmediate();
		if(rc == -1)
		{
			cout << "ERROR IN INSTRUCTION DECODE." << endl;
			cout << "ERROR IN SIGN EXTENSION." << endl;
		}
	}
}
