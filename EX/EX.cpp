#include <string>
#include <iostream>
#include <vector>
#include "EX.h"
#include "../UTIL/utils.h"
#include "../UTIL/MEMSlot.h"

using namespace std;

extern int doBr;
extern string branchLoc;
extern vector<MEMSlot> Regs;
extern string stuffFromMemory;
extern string stuffFromExecute;
extern string stuffFromWriteBack;
extern bool EXnop;
extern bool MEMnop;
extern bool WBnop;

EX::EX(void)
{
	RSVal = "";
	RTVal = "";
	signExtendedImmediate = "";
	PCin = "";
	NOP = 0;
	ALUResult = "";
	PCout = "";
	
	control = "";
}

void EX::perform(void)
{
	cout << "bcontrols b4 ex: " << control<<endl;
    	if(NOP == 0)
	{
		hazardCheck();		

		int rc;
		rc = ALUCompute();
		if(rc == -1)
		{
			cout << "ERROR IN EXECUTE." << endl;
			cout << "ERROR IN ALU COMPUTATION." << endl;
		}
				
		rc = doBranch();
		if(rc == -1)
		{
			cout << "ERROR IN EXECUTE." << endl;
			cout << "ERROR IN BRANCH DECISION/EXECUTION." << endl;
		}
	}
}

int EX::ALUCompute(void)
{
    bool iType, rType = false;
    string ALUop;
    int rsi, rti, immi, result;

    //make all the binary into ints
    rsi = btoi(RSVal);
    rti = btoi(RTVal);
    immi = btoi(signExtendedImmediate);

    //decide if R or I type
    if (control[1] == '1')
        iType = true;
    else
        rType = true;

    ALUop = control.substr(2,5);
    if (ALUop == "00000")
    {
        if (control[10] == '1') //if j-type, ALU output is useless
            //ALUResult = "0000000000000000";
            result = 0;
        else
            //add
            result = rsi + rti;
    }
    else if(ALUop == "00001")
    {
        //sub
        result = rsi - rti;
    }
    else if (ALUop == "00010")
    {
        //set if less than
        if (rsi < rti)
            result = 1;
        else
            result = 0;
    }
    else if (ALUop == "00011")
    { 
        //set if greater than
        if (rsi > rti)
            result = 1;
        else
            result = 0;
    }
    else if (ALUop == "00100")
    { 
        //set <=
        if (rsi <= rti)
            result = 1;
        else
            result = 0;
    }
    else if (ALUop == "00101")
    { 
        //set >=
        if (rsi >= rti)
            result = 1;
        else
            result = 0;
    }
    else if (ALUop == "00110")
    {
        //and
        result = rsi & rti;
    }
    else if (ALUop == "00111")
    {
        //or
        result = rsi | rti;
    }
    else if (ALUop == "01000")
    {
        //nor
        result = ~(rsi | rti);
    }
    else if (ALUop == "01001")
    {
        //xor
        result = rsi ^ rti;
    }
    else if (ALUop == "01010")
    {
        //shift left
        string temp = RSVal;
        for (int i = 0; i < immi; i++)
            temp.append("0");
        temp = temp.substr((temp.length()-16),16);
        result = btoi(temp);
    }
    else if (ALUop == "01011")
    {
        //shift right
        string tChr, temp = RSVal;
        tChr = temp[0];
        for (int i = 0; i < immi; i++)
            temp.insert(0,tChr);
        temp = temp.substr(0,16);
        result = btoi(temp);
    }
    else if (ALUop == "01100")
    {
        //branch eq
        if (rsi == rti)
            control[11] = '1';
        else
            control[11] = '0';
        result = 0;
    }
    else if (ALUop == "01101")
    {
        //branch <
        if (rsi < rti)
            control[11] = '1';
        else
            control[11] = '0';
        result = 0;
    }
    else if (ALUop == "01110")
    {
        //branch >
        if (rsi > rti)
            control[11] = '1';
        else
            control[11] = '0';
        result = 0;
    }
    else if (ALUop == "01111")
    {
	cout << "rsi: " << rsi << endl <<"rti" << rti << endl;
        //branch <=
        if (rsi <= rti)
            control[11] = '1';
        else
            control[11] = '0';
        result = 0;
    }
    else if (ALUop == "10000")
    {
        //branch >=
        if (rsi >= rti)
            control[11] = '1';
        else
            control[11] = '0';
        result = 0;
    }
    else if (ALUop == "10001")
    {
        //or imm
        result = rsi | immi;
    }
    else if (ALUop == "10010")
    {
        //and imm
        result = rsi & immi;
    }
    else if (ALUop == "10011")
    {
        //load word
        result = rsi + immi;
    }
    else if (ALUop == "10100")
    {
        //store word
        result = rsi + immi;
    }
    else
    {
        cout << "ERROR: invalid ALUop" << endl;
        return 1;
    }
    ALUResult = itob(result, 16);
    return 0;
}

int EX::doBranch(void)
{
	cout << "b controls: " <<control<< endl;    
if (control[11] == '1')
    {
        string hi9 = PCin.substr(0,8);
        string lo7 = signExtendedImmediate.substr(9,7);
        lo7.append("0");
        //lo7 = lo7.substr(1,7);
        hi9.append(lo7);
        PCout = hi9;
	doBr = 3;
	branchLoc = PCout;
	cout << "branchLoc " << branchLoc << endl;
    }
    else
        PCout = PCin;
    return 0;
}

void EX::hazardCheck(void)
{
	bool iType = false, rType = false;
	string RSloc = "";
	string RTloc = "";
	string MEMRegLoc = "";
	string EXRegLoc = "";
	string WBRegLoc = "";
	
	if (control[1] == '1')
		iType = true;
	else
		rType = true;

	if(iType)
	{
		RSloc = instruction.substr(4,3);
		RTloc = instruction.substr(7,3);
	}
	if(rType)
	{
		RSloc = instruction.substr(7,3);
		RTloc = instruction.substr(10,3);
	}

	WBRegLoc = Regs[11].data;
	MEMRegLoc = Regs[10].data;
	EXRegLoc = Regs[9].data;

	cout << "instruction: " << instruction << endl << endl;

	cout << "RSLOC: " << RSloc <<endl;
	cout <<"RTLOC: " << RTloc <<endl;
	if(rType == true) cout << control << endl;
	
	if((RSloc == WBRegLoc) && (WBnop == false))
	{
		cout << endl << "Forwarding to RS: " << stuffFromWriteBack << " from WRITE BACK." << endl << endl << endl;
		RSVal = stuffFromWriteBack;	
	}
	if((RSloc == MEMRegLoc) && (MEMnop == false))
	{
		cout << endl << "Forwarding to RS: " << stuffFromMemory << " from MEMORY." << endl << endl << endl;
		RSVal = stuffFromMemory;
	}
	if((RSloc == EXRegLoc) && (EXnop == false))
	{
		cout << endl << "Forwarding to RS: " << stuffFromExecute << " from EXECUTE." << endl << endl << endl;
		RSVal = stuffFromExecute;
	}
	if((RTloc == WBRegLoc) && (WBnop == false))
	{
		cout << endl << "Forwarding to RT: " << stuffFromWriteBack << " from WRITE BACK." << endl << endl << endl;
		RTVal = stuffFromWriteBack;
	}	
	if((RTloc == MEMRegLoc) && (MEMnop == false))
	{
		cout << endl << "Forwarding to RT: " << stuffFromMemory << " from MEMORY." << endl << endl << endl;
		RTVal = stuffFromMemory;
	}	
	if((RTloc == EXRegLoc) && (EXnop == false))
	{
		cout << endl << "Forwarding to RT: " << stuffFromExecute << " from EXECUTE." << endl << endl << endl;
		RTVal = stuffFromExecute;
	}
}
