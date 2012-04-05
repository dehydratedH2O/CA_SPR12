#include <string>

using namespace std;

ID::ID(void)
{
	instruction = "";
	PCin = "";
	
	PCout = "";
	RSVal = "";
	RTVal = "";
	signExtendedImmediate = "";
	
	control = "";
}

int ID::doJump(void)
{
	if(control.at(11) == '0')
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