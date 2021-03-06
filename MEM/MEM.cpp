#include <string>
#include <vector>
#include <iostream>
#include "MEM.h"
#include "../UTIL/MEMSlot.h"

using namespace std;

extern vector<MEMSlot> DMEM;

MEM::MEM(void)
{
	NOP = 0;	
	RTVal = "";
	RSVal = "";
	
	MemOut = "";
	
	ALUResult = "";
	control = "";
}

int MEM::storeToMem(void)
{
	if(control[8] == '0')
		return 0;
		
	if(DMEM.size() == 0)
		return -1;

	for(int i = 0; i < DMEM.size(); i++)
	{
		if(DMEM[i].location == ALUResult)
		{
			DMEM[i].data = RSVal;
			return 0;
		}
	}
	return -2;
}

int MEM::loadFromMem(void)
{
	if(control[9] == '0')
		return 0;
		
	if(DMEM.size() == 0)
		return -1;
		
	for(int i = 0; i < DMEM.size(); i++)
	{
		if(DMEM[i].location == ALUResult)
		{
			MemOut = DMEM[i].data;
			return 0;
		}
	}
	return -2;
}

void MEM::perform(void)
{
	if(NOP == 0)
	{
		int rc = storeToMem();
		if(rc != 0)
		{
			cout << "ERROR IN MEMORY." << endl;
			cout << "ERROR IN MEMORY STORAGE. RC: " << rc << endl;
		}
	
		rc = loadFromMem();
		if(rc != 0)
		{
			cout << "ERROR IN MEMORY." << endl;
			cout << "ERROR IN MEMORY RETRIEVAL. RC: " << rc << endl;
		}
	}
}
