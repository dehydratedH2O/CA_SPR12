#include <string>
#include <sstream>
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
	vector<MEMSlot> Regs;
	
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
	
	//INITIALIZE REGISTERS
	MemSlot b;
	b.location = "000";
	b.data = "0000000000000000";
	MemSlot c;
	c.location = "001";
	c.data = "0000000000000000";
	MemSlot d;
	d.location = "010";
	d.data = "0000000000000000";
	MemSlot e;
	e.location = "011";
	e.data = "0000000000000000";
	MemSlot f;
	f.location = "100";
	f.data = "0000000000000000";
	MemSlot g;
	g.location = "101";
	g.data = "0000000000000000";
	MemSlot h;
	h.location = "110";
	h.data = "0000000000000000";
	MemSlot n;
	n.location = "111";
	n.data = "0000000000000000";
	
	Regs.push_back(b);
	Regs.push_back(c);
	Regs.push_back(d);
	Regs.push_back(e);
	Regs.push_back(f);
	Regs.push_back(g);
	Regs.push_back(h);
	Regs.push_back(n);
	
	//INITIALIZE REGS SHORT TERM MEMORY
	//This is a layer of cache attatched to the registers
	//that stores data associated with which register
	//should be written to by associating it with the
	//pipeline phase that it is currently in
	
	MemSlot j;
	MemSlot k;
	MemSlot l;
	MemSlot m;
	
	j.location = "ID";
	j.data = "";
	k.location = "EX";
	k.data = "";
	l.location = "MEM";
	l.data = "";
	m.location = "WB";
	m.data = "";
	
	Regs.push_back(j);
	Regs.push_back(k);
	Regs.push_back(l);
	Regs.push_back(m);
	
	string tmpWReg = "";
	
	//Create converter
	Converter converter;
	
	//Convert ASM and store in IMEM
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
	
	//Shift Regs MEM
	Regs[11].data = Regs[10].data;
	Regs[10].data = Regs[9].data;
	Regs[9].data = Regs[8].data;
	Regs[8].data = tmpWReg;
}