#ifndef WB_H
#define WB_H

#include <string>

using namespace std;

class WB
{
	private:
		//Inputs
		string MemOut;
		string ALUResult;
		string control;
		
	public:
		//Constructor
		WB();
		
		//Gets and Sets
		void setMemOut(string a) {MemOut = a;}
		void setALUResult(string a) {ALUResult = a;}
		void setControl(string a) {control = a;}
		
		//Functions
		int setRegVals(void);
		void perform(void);
		
};

#endif