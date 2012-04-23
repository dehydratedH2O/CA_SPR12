#ifndef EX_H
#define EX_H

#include <string>
#include "../UTIL/utils.h"

using namespace std;

class EX
{
	private:
		//Inputs
		string instruction;
		string RSVal;
		string RTVal;
		string signExtendedImmediate;
		string PCin;
		
		//Outputs
		string ALUResult;
		string PCout;
		
		//Both
		string control;
		bool NOP;

	public:
		//Contructor
		EX();
		
		//Gets and Sets
		string getALUResult(void) {return ALUResult;}
		string getPCout(void) {return PCout;}
		string getControl(void) {return control;}
		string getRTVal(void) {return RTVal;}
		string getPCin(void) {return PCin;}
		string getInstruction(void) {return instruction;}
		bool getNOP(void) {return NOP;}
		void setNOP(bool a) {NOP = a;}
		void setRSVal(string a) {RSVal = a;}
		void setRTVal(string a) {RTVal = a;}
		void setSignExtendedImmediate(string a) {signExtendedImmediate = a;}
		void setPCin(string a) {PCin = a;}
		void setControl(string a) {control = a;}
		void setInstruction(string a) {instruction = a;}
		
		//Functions
		int doBranch(void);
		int ALUCompute(void);
		void perform(void);
		void hazardCheck(void);
};

#endif
