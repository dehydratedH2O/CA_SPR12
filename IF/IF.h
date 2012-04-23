#ifndef IF_H
#define IF_H

#include <string>

using namespace std;

class IF
{
	private:
		//Inputs
		string PC;

		//Local
		int NOPctr;
		
		//Outputs
		string incPC;
		string instruction;
		string control;
		bool NOP;
		
	public:
		//Constructor
		IF();
	
		//Gets and Sets
		string getIncPC(void) {return incPC;}
		string getInstruction(void) {return instruction;}
		string getControl(void) {return control;}
		string getPC(void) {return PC;}
		int getNOPctr(void) {return NOPctr;}
		bool getNOP(void) {return NOP;}
		void setNOP(bool a) {NOP = a;}	
		void setPC(string a) {PC = a;}
		
		//Functions
		int fetchInstruction(void);
		int incrementPC(void);
		void calcNOPs(void);
		void perform(void);
		int determineControlSignals(void);
};

#endif
