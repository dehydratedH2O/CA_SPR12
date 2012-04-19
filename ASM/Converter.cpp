#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include "../UTIL/MEMSlot.h"
#include "Converter.h"

using namespace std;

#define FILEPATH "../testASM.txt"

extern vector<MEMSlot> IMEM;

string Converter::itob(int n, int l)
{
    bool neg;
    string result;

    if (n < 0)
        neg = true;
    else
        neg = false;

    if (neg)
    {
        //do 2's complement
        n = ~n;
        n++;
    }

    do result.push_back( '0' + (n & 1) );
    while (n >>= 1);

    reverse( result.begin(), result.end() );

    //pad
    if (result.length() < l)
    {
        for (int i = 0; i < (l - result.length()); i++)
        {
            if (neg)
                result.insert(0,"1");
            else
                result.insert(0,"0");
        }
    }

    if (result.length() > l)
    //result overflow!
    {
        cout << "ERROR: binary representation of " << n << " bigger than " << l << " bits!" << endl;
    }

    return result;
}

int Converter::parseInput(string filepath)
{
    string temp;
    ifstream fin;
	
    //exception handling for input
    fin.exceptions(ifstream::failbit|ifstream::badbit);
    try
    {
	    fin.open("testASM.txt");

    	//PARSE ASM FROM TXT HERE
        while(getline(fin,temp))
        {
            asmCode.push_back(temp);
        }
    }
    catch (ifstream::failure e)
    {
        cout << "error opening/reading file" << endl;
    }

	fin.close();
	return 0;
}

int Converter::convertToMachine(void)
{
    string opcode, operands, binary, func;
    int currPos, nextPos;
    char type;

	for(int i = 0; i < asmCode.size(); i++)
	{
	//CODE TO CONVERT EACH ASM LINE INTO MACHINE CODE GOES HERE
        //first split into opcode and operands
	currPos = 0;
	nextPos = asmCode[i].find_first_of(" ",currPos);
        opcode = asmCode[i].substr(currPos,nextPos-currPos);
	currPos = nextPos;
	nextPos = asmCode[i].length();//asmCode[i].find_first_of(" ",currPos);
        operands = asmCode[i].substr(currPos,nextPos-currPos);
        binary = "";
        cout << "found opcode " << opcode << " with operands " << operands << endl;

        if (opcode == "nop")
        {
            binary.append("0001"); //just and it with itself
            type = 'R';
            func = "000";
            operands = "$r0,$r0,$r0";
        }
        else if(opcode == "add")
                {
		binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "000";
		}
            else if (opcode == "sub")
                {
		binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "001";
		}
            else if (opcode == "slt")
                {
		binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "010";
		}
            else if (opcode == "sgt")
                {
		binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "011";
		}
            else if (opcode == "sle")
                {
		binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "100";
		}
            else if (opcode == "sge")
                {
		binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "101";
		}
            else if (opcode == "and")
                {
		binary.append("0001"); //append opcode to binary
                type = 'R';
                func = "000";
		}
            else if (opcode == "or")
                {
		binary.append("0001"); //append opcode to binary
                type = 'R';
                func = "001";
		}
            else if (opcode == "nor")
                {
		binary.append("0001"); //append opcode to binary
                type = 'R';
                func = "010";
		}
            else if (opcode == "xor")
                {
		binary.append("0001"); //append opcode to binary
                type = 'R';
                func = "011";
		}
            else if (opcode == "sll")
                {
		binary.append("0010"); //append opcode to binary
                type = 'I';
                func = "";
		}
            else if (opcode == "srl")
                {
		binary.append("0011"); //append opcode to binary
                type = 'I';
                func = "";
		}
            else if (opcode == "beq")
                {
		binary.append("0100"); //append opcode to binary
                type = 'I';
                func = "";
		}
            else if (opcode == "blt")
                {
		binary.append("0101"); //append opcode to binary
                type = 'I';
                func = "";
		}
            else if (opcode == "bgt")
                {
		binary.append("0110"); //append opcode to binary
                type = 'I';
                func = "";
		}
            else if (opcode == "ble")
                {
		binary.append("0111"); //append opcode to binary
                type = 'I';
                func = "";
		}
            else if (opcode == "bge")
		{                
		binary.append("1000"); //append opcode to binary
                type = 'I';
                func = "";
		}
            else if (opcode == "ori")
                {
		binary.append("1001"); //append opcode to binary
                type = 'I';
                func = "";
		}
            else if (opcode == "andi")
		{                
		binary.append("1010"); //append opcode to binary
                type = 'I';
                func = "";
		}
            else if (opcode == "lw")
                {
		binary.append("1011"); //append opcode to binary
                type = 'I';
                func = "";
		}
            else if (opcode == "sw")
            {
		binary.append("1100"); //append opcode to binary
                type = 'I';
                func = "";
	    }
            else if (opcode == "j")
            {
		binary.append("1101"); //append opcode to binary
                type = 'J';
                func = "";
	    }
            else
		{
                cout << "bad opcode " << opcode << endl;
                return 1;
        } // end switch
        //now switch on type
	string rd, rs, rt, imm;
	string rdstr, rsstr, rtstr;
        string bRd,bRs,bRt, bRst;
	int iRs, iRt, iRd;
        string bImm, bAddr;
        
	switch(type)
        {
            case 'R':
                //string rd,rs,rt;
                //int currPos, nextPos;
                currPos = 0;
                nextPos = operands.find_first_of(',',currPos);
                rd = operands.substr(currPos,nextPos-currPos);
                currPos = nextPos;
                nextPos = operands.find_first_of(',',currPos);
                rs = operands.substr(currPos,nextPos-currPos);
                currPos = nextPos;
                nextPos = operands.length();//operands.find_first_of(',',currPos);
                rt = operands.substr(currPos,nextPos-currPos);
                
                //make sure they're registers
                if((rd[0] != '$') || (rd[1] != 'r') || (rs[0] != '$') || (rs[1] != 'r') || (rt[0] != '$') || (rt[1] != 'r'))
                {
                    cout << "bad operand!" << endl;
                    return 1;
                }

                //int iRd, iRs, iRt;


		rdstr = "";
		rsstr = "";
		rtstr = "";
		rdstr += rd[2];
		rsstr += rs[2];
		rtstr += rt[2];


                iRd = atoi(rdstr.c_str());
                iRs = atoi(rsstr.c_str());
                iRt = atoi(rtstr.c_str());

                if((iRd < 0) || (iRd > 7) || (iRs < 0) || (iRs > 7) || (iRt < 0) || (iRt > 7))
                {
                    cout << "bad register number!" << endl;
                    return 1;
                }
                
                bRd = itob(iRd,3);
                bRs = itob(iRs,3);
                bRt = itob(iRt,3);

                binary.append(bRd);
                binary.append(bRs);
                binary.append(bRt);

                //registers finished, so append func
                binary.append(func);

                //finished
                break;
            case 'I':
                //string rs, rt, imm;
                //int currPos, nextPos;
                currPos = 0;
                nextPos = operands.find_first_of(',',currPos);
                rs = operands.substr(currPos,nextPos-currPos);
                currPos = nextPos;
                nextPos = operands.find_first_of(',',currPos);
                rt = operands.substr(currPos,nextPos-currPos);
                currPos = nextPos;
                nextPos = operands.length() - 1; //operands.find_first_of(',',currPos);
                imm = operands.substr(currPos,nextPos-currPos);

                //make sure they're registers
                if((rs[0] != '$') || (rs[1] != 'r') || (rt[0] != '$') || (rt[1] != 'r'))
                {
                    cout << "bad operand!" << endl;
                    return 1;
                }

                //int iRt, iRs;

		rsstr = "";
		rtstr = "";
		rsstr += rs[2];
		rtstr += rt[2];

                iRs = atoi(rsstr.c_str());
                iRt = atoi(rtstr.c_str());

                if((iRs < 0) || (iRs > 7) || (iRt < 0) || (iRt > 7))
                {
                    cout << "bad register number!" << endl;
                    return 1;
                }
                
                bRs = itob(iRs,3);
                bRt = itob(iRt,3);

                binary.append(bRs);
                binary.append(bRt);

                //handle immediate
                int iImm;
                iImm = atoi(imm.c_str());
                bImm = itob(iImm,6);
                binary.append(bImm);
                
                break;
            case 'J':

                //handle address in operands
                int iAddr;
                iAddr = atoi(operands.c_str());
                bAddr = itob(iAddr,12);
                binary.append(bAddr);

                break;
            default:
                return 1; //should never get here
        } // end type switch

        //binary is ready; push it back
        machineCode.push_back(binary);
    } // end for
	return 0;
}

int Converter::createIMEM(void)
{
	for(int i = 0; i < machineCode.size(); i++)
	{
		//Stores Machine Code in IMEM
		MEMSlot MemSlot;
		MemSlot.data = machineCode[i];
		int memLoc = 2 * i;

		stringstream s;
		s << memLoc;

		MemSlot.location = s.str();
		IMEM.push_back(MemSlot);
	}
}
