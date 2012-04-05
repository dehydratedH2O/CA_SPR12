#include <string>
#include <stringstream>
#include <vector>

#include "ASM/Converter.h"
#include "UTIL/MEMSlot.h"
#include "IF/IF.h"
#include "ID/ID.h"
#include "EX/EX.h"
#include "MEM/MEM.h"
#include "WB/WB.h"

using namespace std;

int main()
{
	//CODE HERE TO CONVERT ASM TO BINARY
	//AS WELL AS STORE MACHINE INSTRUCTIONS
	//IN IMEM
	
	string INITIAL_PC = "0000000000000000";
	int MAXMEM = //highest imem memory location in program
	vector<MEMSlot> IMEM;
	vector<MEMSlot> DMEM;
	
	//INITIALIZE DMEM
	for(int i = 0; i < 65536; i = i + 2)
	{
		int tmp = i;
		MemSlot a;
		a.location = 0;
		a.data = 0;
		string loc = "";
		
		if(tmp >= 32768)
		{
			tmp = tmp - 32768;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 16384)
		{
			tmp = tmp - 16384;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 8192)
		{
			tmp = tmp - 8192;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 4096)
		{
			tmp = tmp - 4096;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 2048)
		{
			tmp = tmp - 2048;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 1024)
		{
			tmp = tmp - 1024;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 512)
		{
			tmp = tmp - 512;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 256)
		{
			tmp = tmp - 256;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 128)
		{
			tmp = tmp - 128;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 64)
		{
			tmp = tmp - 64;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 32)
		{
			tmp = tmp - 32;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 16)
		{
			tmp = tmp - 16;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 8)
		{
			tmp = tmp - 8;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 4)
		{
			tmp = tmp - 4;
			loc += "1";
		}
		else loc += "0";
		
		if(tmp >= 2)
		{
			tmp = tmp - 2;
			loc += "1";
		}
		else loc += "0";
		
		a.location = loc;
		DMEM.push_back(a);
	}
	
	Converter converter;
	
	converter.parseInput("");
	converter.convertToMachine();
	converter.createIMEM();
	
	IF* dIF = new IF();
	ID* dID = new ID();
	EX* dEX = new EX();
	MEM* dMEM = new MEM();
	WB* dWB = new WB();
	
	while(currentPC < MAXMEM)
	{
		//THREADING CODE NEEDED HERE
		dIF->perform(void);
		dID->perform(void);
		dEX->perform(void);
		dMEM->perform(void);
		dWB->perform(void);
		
		transfer(dIF, dID, dEX, dMEM, dWB);
	}

	return 0;
}

string intToString(int a)
{
	stringstream s;
	s << a;
	return s.str();
}

void transfer(IF* dIF, ID* dID, EX* dEX, MEM* dMEM, WB* dWB)
{
	//Set WB Inputs
	dWB->setMemOut(dMEM->getMemOut());
	dWB->setALUResult(dMEM->getALUResult());
	dWB->setControl(dMEM->getControl());
	
	//Set MEM Inputs
	dMEM->setALUResult(dEX->getALUResult());
	dMEM->setRTVal(dEX->getRTVal());
	dMEM->setControl(dMEM->getControl());
	
	//Set EX Inputs
	dEX->setRSVal(dID->getRSVal());
	dEX->setRTVal(dID->getRTVal());
	dEX->setSignExtendedImmediate(dID->getSignExtendedImmediate());
	dEX->setPCin(dID->getPCout());
	dEX->setControl(dID->getControl());
	
	//Set ID Inputs
	dID->setInstruction(dIF->getInstruction());
	dID->setPCin(dIF->getIncPC());
	dID->setControl(dIF->getControl());
	
	//Set IF Inputs
	dIF->setPC();
}