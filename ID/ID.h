#ifndef ID_H
#define ID_H

#include <string>

using namespace std;

class ID
{
	private:
		//Inputs
		string instruction;
		string PCin;
		
		//Outputs
		string PCout;
		string RSVal;
		string RTVal;
		string signExtendedImmediate;
		
		//Both
		string control;
		
	public:
		//Constructor
		ID();
		
		//Gets and Sets
		string getPCout(void) {return PCout;}
		string getRSVal(void) {return RSVal;}
		string getRTVal(void) {return RTVal;}
		string getSignExtendedImmediate(void) {return signExtendedImmediate;}
		string getControl(void) {return control;}
		void setInstruction(string a) {instruction = a;}
		void setPCin(string a) {PCin = a;}
		void setControl(string a) {control = a;}
		
		//Functions
		int doJump(void);
		int getRegistersFromFile(void);
		int signExtendImmediate(void);
		void perform(void);
}	

#endif