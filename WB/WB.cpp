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
	
	//CODE TO STORE IN REGS GOES HERE
	
	return 0;
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