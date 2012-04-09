#include <string>

using namespace std;

WB::WB(void)
{
	MemOut = "";
	ALUResult = "";
	control = "";
}

int WB::setRegVals(void)
{
	string wVal = "";
	
	if(control[10] /*MemToReg*/ == 1)
	{
		wVal = MemOut;
	}
	else wVal = ALUResult;
	
	string writeToReg = Regs[11].data;
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
	int rc = setRegVals();
	if(rc == -1)
	{
		cout << "ERROR IN WRITE BACK." << endl;
		cout << "ERROR IN SETTING REGISTER VALUES." << endl;
	}
}