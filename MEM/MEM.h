#ifndef MEM_H
#define MEM_H

#include <string>

using namespace std;

class MEM
{
	private:
		//Inputs
		string RTVal;
		
		//Outputs
		string MemOut;
		
		//Both
		string ALUResult;
		string control;
		string instruction;
		bool NOP;
		
	public:
		//Constructor
		MEM();
		
		//Gets and Sets
		string getMemOut(void) {return MemOut;}
		string getControl(void) {return control;}
		string getALUResult(void) {return ALUResult;}
		string getInstruction(void) {return instruction;}
		void setInstruction(string a) {instruction = a;}
		bool getNOP(void) {return NOP;}
		void setNOP(bool a) {NOP = a;}
		void setRTVal(string a) {RTVal = a;}
		void setControl(string a) {control = a;}
		void setALUResult(string a) {ALUResult = a;}
	
		
		//Functions
		int storeToMem(void);
		int loadFromMem(void);
		void perform(void);
};
		
#endif
