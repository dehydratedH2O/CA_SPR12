#include <string>
#include <vector>
#include <iostream>
#include "WB.h"
#include "../UTIL/MEMSlot.h"

using namespace std;

extern string stuffFromWriteBack;
extern vector<MEMSlot> Regs;

WB::WB(void)
{
	NOP = 0;
	MemOut = "";
	ALUResult = "";
	control = "";
}

int WB::setRegVals(void)
{
	string wVal = "";

	if(control[0] == '0')
		return 0;

	cout << "WB controls: " << control << endl;
	
	if(control[9] /*MemToReg*/ == '1')
	{
		wVal = MemOut;
	}
	else wVal = ALUResult;
	
	string writeToReg = Regs[10].data;
	for(int i = 0; i < 8; i++)
	{
		if(Regs[i].location == writeToReg)
		{
			Regs[i].data = wVal;
			return 0;
		}
	}
	
	//INVALID REG ADDRESS
	return -1;
}

void WB::perform(void)
{
	if(NOP == 0)
	{
		int rc = setRegVals();
		if(rc == -1)
		{
			cout << "ERROR IN WRITE BACK." << endl;
			cout << "ERROR IN SETTING REGISTER VALUES." << endl;
		}
	}
}
