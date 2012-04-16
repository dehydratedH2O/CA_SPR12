#ifndef CONVERTER_H
#define CONVERTER_H

#include <vector>
#include <string>
#include "../UTIL/MEMSlot.h"

using namespace std;

class Converter
{
	private:
		vector<string> asmCode;
		vector<string> machineCode;
		extern vector<MEMSlot> IMEM;

        string itob(int n, int l);
		
	public:
		//Constructor
		Converter() {};
	
		int parseInput(string);
		int convertToMachine(void);
		int createIMEM(void);
};

#endif
