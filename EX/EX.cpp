#include <string>
#include <iostream>
#include "EX.h"
#include "../UTIL/utils.h"

using namespace std;

EX::EX(void)
{
	RSVal = "";
	RTVal = "";
	signExtendedImmediate = "";
	PCin = "";
	NOP = 0;
	ALUResult = "";
	PCout = "FAIL";
	
	control = "";
}

void EX::perform(void)
{
    	if(NOP == 0)
	{
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
        result = rti | immi;
    }
    else if (ALUop == "10010")
    {
        //and imm
        result = rti & immi;
    }
    else if (ALUop == "10011")
    {
        //load word
        result = rti + immi;
    }
    else if (ALUop == "10100")
    {
        //store word
        result = rti + immi;
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
    if (control[11] == '1')
    {
        string hi9 = PCin.substr(0,9);
        string lo7 = signExtendedImmediate.substr(8,7);
        lo7.append("0");
        lo7 = lo7.substr(0,7);
        hi9.append(lo7);
        PCout = hi9;
    }
    else
        PCout = "FAIL";
    return 0;
}
