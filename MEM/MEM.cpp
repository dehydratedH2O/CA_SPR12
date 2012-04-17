#include <string>
#include <vector>
#include <iostream>
#include "MEM.h"
#include "../UTIL/MEMSlot.h"

using namespace std;

extern vector<MEMSlot> DMEM;

MEM::MEM(void)
{
	RTVal = "";
	
	MemOut = "";
	
	ALUResult = "";
	control = "";
}

int MEM::storeToMem(void)
{
	if(control[8] == 0)
		return 0;
		
	if(DMEM.size() == 0)
		return -1;

	for(int i = 0; i < DMEM.size(); i++)
	{
		if(DMEM[i].location == ALUResult)
		{
			DMEM[i].data = RTVal;
			return 0;
		}
	}
	return -1;
}

int MEM::loadFromMem(void)
{
	if(control[9] == 0)
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
	return -1;
}

void MEM::perform(void)
{
	int rc = storeToMem();
	if(rc == -1)
	{
		cout << "ERROR IN MEMORY." << endl;
		cout << "ERROR IN MEMORY STORAGE." << endl;
	}
	
	rc = loadFromMem();
	if(rc == -1)
	{
		cout << "ERROR IN MEMORY." << endl;
		cout << "ERROR IN MEMORY RETRIEVAL." << endl;
	}
}
