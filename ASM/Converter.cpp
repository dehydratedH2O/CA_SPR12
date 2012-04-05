#include <iostream>

using namespace std;

#define FILEPATH ../testASM

int Converter::parseInput(string filepath)
{
	if((filepath == NULL) || (filepath == ""))
		filepath = FILEPATH;
		
	ifstream input;
	input.open(filepath);
	
	//PARSE ASM FROM TXT HERE
	
	input.close();
	return 0;
}

int Converter::convertToMachine(void)
{
	for(int i = 0; i < asmCode.size(); i++)
	{
		//CODE TO CONVERT EACH ASM LINE INTO MACHINE CODE GOES HERE
	}
	return 0;
}

int Converter::createIMEM(void)
{
	for(int i = 0; i < machineCode.size(); i++)
	{
		//Stores Machine Code in IMEM
		MEMSlot MemSlot;
		MemSlot.data = machineCode[i];
		int memLoc = 2 * i;
		MemSlot.location = intToString(memLoc);
		IMEM.push_back(MemSlot);
	}
}