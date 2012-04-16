#ifndef EX_H
#define EX_H

#include <string>

using namespace std;

class EX
{
	private:
		//Inputs
		string RSVal;
		string RTVal;
		string signExtendedImmediate;
		string PCin;
		
		//Outputs
		string ALUResult;
		string PCout;
		
		//Both
		string control;

        //logic
        int btoi (char* str);
        string itob (int n, int l);

	public:
		//Contructor
		EX();
		
		//Gets and Sets
		string getALUResult(void) {return ALUResult;}
		string getPCout(void) {return PCout;}
		string getControl(void) {return control;}
		void setRSVal(string a) {RSVal = a;}
		void setRTVal(string a) {RTVal = a;}
		void setSignExtendedImmediate(string a) {signExtendedImmediate = a;}
		void setPCin(string a) {PCin = a;}
		void setControl(string a) {control = a;}
		
		//Functions
		int doBranch(void);
		int ALUCompute(void);
		void perform(void);
};

#endif
