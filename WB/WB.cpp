#include <string>

using namespace std;

WB::WB(void)
{
	MemOut = "";
	ALUResult = "";
	control = "";
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