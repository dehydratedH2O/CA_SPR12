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
		string instruction;
		bool NOP;
		
	public:
		//Constructor
		WB();
		
		//Gets and Sets
		bool getNOP(void) {return NOP;}
		string getALUResult(void) {return ALUResult;}
		string getInstruction(void) {return instruction;}		
		void setInstruction(string a) {instruction = a;}
		void setNOP(bool a) {NOP = a;}
		void setMemOut(string a) {MemOut = a;}
		void setALUResult(string a) {ALUResult = a;}
		void setControl(string a) {control = a;}
		
		//Functions
		int setRegVals(void);
		void perform(void);
		
};

#endif
