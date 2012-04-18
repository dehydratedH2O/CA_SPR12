#ifndef CONVERTER_H
#define CONVERTER_H

#include <vector>
#include <string>
#include <algorithm>
#include "../UTIL/MEMSlot.h"

using namespace std;

extern vector<MEMSlot> IMEM;

class Converter
{
	private:
		vector<string> asmCode;
		vector<string> machineCode;


		
	public:
		//Constructor
		Converter() {};
		int parseInput(string);
		int convertToMachine(void);
		int createIMEM(void);
		string itob(int n, int l);
};

#endif
