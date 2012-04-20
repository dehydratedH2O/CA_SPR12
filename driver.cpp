#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "ASM/Converter.h"
#include "UTIL/MEMSlot.h"
#include "IF/IF.h"
#include "ID/ID.h"
#include "EX/EX.h"
#include "MEM/MEM.h"
#include "WB/WB.h"
#include "UTIL/utils.h"

using namespace std;

#define OUTPUT_MEMORY

int currentPC;

void transfer(IF*,ID*,EX*,MEM*,WB*);

vector<MEMSlot> Regs;
vector<MEMSlot> IMEM;
vector<MEMSlot> DMEM;

string tmpWReg;

int MAXMEM, BANDWIDTH;

int cycle;

int NOPctr;

int doBr;
int doJ;
string branchLoc;
string jumpLoc;
string stuffFromMemory;
string stuffFromExecute;

int main()
{
	//CODE HERE TO CONVERT ASM TO BINARY
	//AS WELL AS STORE MACHINE INSTRUCTIONS
	//IN IMEM
	
	currentPC = 0;
	tmpWReg = "";
	MAXMEM = 4096;
	BANDWIDTH = 16;
	cycle = 1;
	NOPctr = 0;
	doBr = 0;
	doJ = 0;
	branchLoc = "";
	jumpLoc = "";
	stuffFromMemory = "";
	stuffFromExecute = "";

	//INITIALIZE DMEM
	for(int i = 4096; i < 65536; i = i + 2)
	{
		int tmp = i;
		MEMSlot a;
		a.location = "0";
		a.data = "0";
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
	MEMSlot b;
	b.location = "000";
	b.data = "0000000000000000";
	MEMSlot c;
	c.location = "001";
	c.data = "0000000000000000";
	MEMSlot d;
	d.location = "010";
	d.data = "0000000000000000";
	MEMSlot e;
	e.location = "011";
	e.data = "0000000000000000";
	MEMSlot f;
	f.location = "100";
	f.data = "0000000000000000";
	MEMSlot g;
	g.location = "101";
	g.data = "0000000000000000";
	MEMSlot h;
	h.location = "110";
	h.data = "0000000000000000";
	MEMSlot n;
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
	
	MEMSlot j;
	MEMSlot k;
	MEMSlot l;
	MEMSlot m;
	
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

	//TEST IMEM
	cout << endl << endl << "--------------------------------------" << endl;
	cout << "                IMEM" << endl;
	cout << "--------------------------------------" << endl << endl;
	for(int i = 0; i < 23; i++)
	{
		cout << IMEM[i].data << endl;
	}
	
	string a = "";
	while(currentPC < MAXMEM)
	{
		//THREADING CODE NEEDED HERE
		dIF->perform();
		if(cycle > 1)
			dID->perform();
		if(cycle > 2)
			dEX->perform();
		if(cycle > 3)
			dMEM->perform();
		if(cycle > 4)
			dWB->perform();
	
		transfer(dIF, dID, dEX, dMEM, dWB);

		//---------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------
		//------------------------------- MEMORY OUTPUT TESTING ---------------------------
		//---------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------
		#ifdef OUTPUT_MEMORY
			//TEST IMEM
			cout << endl << endl << "--------------------------------------" << endl;
			cout << "                IMEM" << endl;
			cout << "--------------------------------------" << endl << endl;
			for(int i = 0; i < 23; i++)
			{
				cout << IMEM[i].data << endl;
			}

			//TEST DMEM
			cout << endl << endl << "--------------------------------------" << endl;
			cout << "                DMEM" << endl;
			cout << "--------------------------------------" << endl << endl;
			for(int i = 4096; i < 5000; i = i + 2)
			{
				cout << DMEM[i-4096].data << ",";
			}
		#endif
		//---------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------

		cout << "Type and press ENTER to continue.";
		//cin >> a;
		cin.ignore();
		cout << endl << endl << endl << endl;
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
	//Cycle Initialization
	cout << "--------------------------------------" << endl;
	cout << "             Cycle " << cycle << endl;
	cout << "--------------------------------------" << endl << endl;
	cycle++;
	cout << "NOPctr: " << NOPctr << endl << endl;

	//NOP Handling
	if(NOPctr > 0) 
	{
		dIF->setNOP(1);
		NOPctr--;
	}
	else dIF->setNOP(0);

	//Data Forwarding
	stuffFromMemory = dMEM->getMemOut();
	stuffFromExecute = dEX->getALUResult();

	//Set WB Inputs
	dWB->setMemOut(dMEM->getMemOut());
	dWB->setALUResult(dMEM->getALUResult());
	dWB->setControl(dMEM->getControl());
	dWB->setNOP(dMEM->getNOP());

	//Output MEM/WB Buffer
	cout << "MEM/WB Buffer" << endl;
	cout << "-------------" << endl;
	cout << "Memory Output: " << dMEM->getMemOut() << endl;
	cout << "ALU Result: " << dMEM->getALUResult() << endl;
	cout << "Control Signals: " << dMEM->getControl() << endl;
	cout << "MEM/WB NOP value: " << dMEM->getNOP() << endl << endl;
	
	//Set MEM Inputs
	dMEM->setALUResult(dEX->getALUResult());
	dMEM->setRTVal(dEX->getRTVal());
	dMEM->setControl(dEX->getControl());
	dMEM->setNOP(dEX->getNOP());

	//Output EX/MEM Buffer
	cout << "EX/MEM Buffer" << endl;
	cout << "-------------" << endl;
	cout << "ALUResult: " << dEX->getALUResult() << endl;
	cout << "Rt Value: " << dEX->getRTVal() << endl;
	cout << "Control Signals: " << dEX->getControl() << endl;
	cout << "EX/MEM NOP value: " << dEX->getNOP() << endl << endl;
	
	//Set EX Inputs
	dEX->setRSVal(dID->getRSVal());
	dEX->setRTVal(dID->getRTVal());
	dEX->setSignExtendedImmediate(dID->getSignExtendedImmediate());
	dEX->setPCin(dID->getPCout());
	dEX->setControl(dID->getControl());
	dEX->setNOP(dID->getNOP());
	dEX->setInstruction(dID->getInstruction());

	//Output ID/EX Buffer
	cout << "ID/EX Buffer" << endl;
	cout << "------------" << endl;
	cout << "Rs Value: " << dID->getRSVal() << endl;
	cout << "Rt Value: " << dID->getRTVal() << endl;
	cout << "Sign Extended Immediate: " << dID->getSignExtendedImmediate() << endl;
	cout << "PC: " << dID->getPCout() << endl;
	cout << "Control Signals: " << dID->getControl() << endl;
	cout << "Instruction: " << dID->getInstruction() << endl;
	cout << "ID/EX NOP value: " << dID->getNOP() << endl << endl;
	
	//Set ID Inputs
	dID->setInstruction(dIF->getInstruction());
	dID->setPCin(dIF->getIncPC());
	dID->setControl(dIF->getControl());
	dID->setNOP(dIF->getNOP());
	
	//Output IF/ID Buffer
	cout << "IF/ID Buffer" << endl;
	cout << "------------" << endl;
	cout << "Instruction: " << dIF->getInstruction() << endl;
	cout << "PC: " << dIF->getIncPC() << endl;
	cout << "Control Signals: " << dIF->getControl() << endl;
	cout << "IF/ID NOP value: " << dIF->getNOP() << endl << endl;

	//Set IF Inputs
	if((doBr == 0) && (doJ == 0))
		dIF->setPC(itob(currentPC,16));
	if((cycle != 1) && (doBr == 0) && (doJ == 0))
		dIF->setPC(dIF->getIncPC());
	if(doBr > 0)
	{
		dIF->setPC(branchLoc);
		doBr--;
	}
	if(doJ > 0)
	{
		dIF->setPC(jumpLoc);
		doJ--;
	}

	//Output Finalization
	cout << "PC incoming to IF phase: " << dIF->getPC() << endl << endl;
	cout << endl << endl;	

	//Shift Regs MEM
	Regs[10].data = Regs[9].data;
	Regs[9].data = Regs[8].data;
	Regs[8].data = tmpWReg;
}
