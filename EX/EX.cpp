#include <string>

using namespace std;

EX::EX(void)
{
	RSVal = "";
	RTVal = "";
	signExtendedImmediate = "";
	PCin = "";
	
	ALUResult = "";
	PCout = "";
	
	control = "";
}

void EX::perform(void)
{
	int rc = doBranch();
	if(rc == -1)
	{
		cout << "ERROR IN EXECUTE." << endl;
		cout << "ERROR IN BRANCH DECISION/EXECUTION." << endl;
	}
	
	rc = ALUCompute();
	if(rc == -1)
	{
		cout << "ERROR IN EXECUTE." << endl;
		cout << "ERROR IN ALU COMPUTATION." << endl;
	}
}