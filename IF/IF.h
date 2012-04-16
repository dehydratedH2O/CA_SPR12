#ifndef IF_H
#define IF_H

#include <string>

using namespace std;

class IF
{
	private:
		//Inputs
		string PC;
		
		//Outputs
		string incPC;
		string instruction;
		string control;
		
	public:
		//Constructor
		IF();
	
		//Gets and Sets
		string getIncPC(void) {return incPC;}
		string getInstruction(void) {return instruction;}
		string getControl(void) {return control;}
		void setPC(string a) {PC = a;}
		
		//Functions
		int fetchInstruction(void);
		int incrementPC(void);
		void perform(void);
};

#endif
