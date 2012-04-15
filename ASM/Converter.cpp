#include <iostream>

using namespace std;

#define FILEPATH ../testASM

string itob(int n, int l)
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
                result.insert(0,'1');
            else
                result.insert(0,'0');
        }
    }

    if (result.length() > l)
    //result overflow!
    {
        cout << "ERROR: binary representation of " << n << " bigger than " << l " bits!" << endl;
    }

    return result;
}

int Converter::parseInput(string filepath)
{
    string temp;

	if((filepath == NULL) || (filepath == ""))
		filepath = FILEPATH;
	
    //exception handling for input
	ifstream fin;
    fin.exceptions(ifstream::failbit|ifstream::badbit);
    try
    {
	    fin.open(filepath);

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
    str opcode, operands, binary, func;
    char type;

	for(int i = 0; i < asmCode.size(); i++)
	{
		//CODE TO CONVERT EACH ASM LINE INTO MACHINE CODE GOES HERE
	    //first split into opcode and operands
        opcode = strtok(asmCode[i],' ');
        operands = strtok(asmCode[i],' ');
        binary = "";
        cout << "found opcode " << opcode << " with operands " << operands << endl;
        switch (opcode)
        {
            case "add":
                binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "000";
                break;
            case "sub":
                binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "001";
                break;
            case "slt":
                binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "010";
                break;
            case "sgt":
                binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "011";
                break;
            case "sle":
                binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "100";
                break;
            case "sge":
                binary.append("0000"); //append opcode to binary
                type = 'R';
                func = "101";
                break;
            case "and":
                binary.append("0001"); //append opcode to binary
                type = 'R';
                func = "000";
                break;
            case "or":
                binary.append("0001"); //append opcode to binary
                type = 'R';
                func = "001";
                break;
            case "nor":
                binary.append("0001"); //append opcode to binary
                type = 'R';
                func = "010";
                break;
            case "xor":
                binary.append("0001"); //append opcode to binary
                type = 'R';
                func = "011";
                break;
            case "sll":
                binary.append("0010"); //append opcode to binary
                type = 'I';
                func = "";
                break;
            case "srl":
                binary.append("0011"); //append opcode to binary
                type = 'I';
                func = "";
                break;
            case "beq":
                binary.append("0100"); //append opcode to binary
                type = 'I';
                func = "";
                break;
            case "blt":
                binary.append("0101"); //append opcode to binary
                type = 'I';
                func = "";
                break;
            case "bgt":
                binary.append("0110"); //append opcode to binary
                type = 'I';
                func = "";
                break;
            case "ble":
                binary.append("0111"); //append opcode to binary
                type = 'I';
                func = "";
                break;
            case "bge":
                binary.append("1000"); //append opcode to binary
                type = 'I';
                func = "";
                break;
            case "ori":
                binary.append("1001"); //append opcode to binary
                type = 'I';
                func = "";
                break;
            case "andi":
                binary.append("1010"); //append opcode to binary
                type = 'I';
                func = "";
                break;
            case "lw":
                binary.append("1011"); //append opcode to binary
                type = 'I';
                func = "";
                break;
            case "sw":
                binary.append("1100"); //append opcode to binary
                type = 'I';
                func = "";
                break;
            case "j":
                binary.append("1101"); //append opcode to binary
                type = 'J';
                func = "";
                break;
            default:
                cout << "bad opcode " << opcode << endl;
                return 1;
        } // end switch
        //now switch on type
        switch(type)
        {
            case 'R':
                string rd,rs,rt;
                rd = strtok(operands,',');
                rs = strtok(operands,',');
                rt = strtok(operands,',');
                
                //make sure they're registers
                if (rd[0] != '$') || (rd[1] != 'r') || (rs[0] != '$') || (rs[1] != 'r') || (rt[0] != '$') || (rt[1] != 'r')
                {
                    cout << "bad operand!" << endl;
                    return 1;
                }

                int iRd, iRs, iRt;
                string bRd,bRs,bRt;

                iRd = atoi(rd[2]);
                iRs = atoi(rs[2]);
                iRt = atoi(rt[2]);

                if (iRd < 0) || (iRd > 7) || (iRs < 0) || (iRs > 7) || (iRt < 0) || (iRt > 7)
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
                string rs, rt, imm;
                rs = strtok(operands,',');
                rt = strtok(operands,',');
                imm = strtok(operands',');

                //make sure they're registers
                if (rs[0] != '$') || (rs[1] != 'r') || (rt[0] != '$') || (rt[1] != 'r')
                {
                    cout << "bad operand!" << endl;
                    return 1;
                }

                int iRt, iRs;
                string bRt,bRst;

                iRs = atoi(rs[2]);
                iRt = atoi(rt[2]);

                if (iRs < 0) || (iRs > 7) || (iRt < 0) || (iRt > 7)
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
                string bImm;
                iImm = atoi(imm.c_str());
                bImm = itob(iImm,6);
                binary.append(bImm);
                
                break;
            case 'J':

                //handle address in operands
                int iAddr;
                string bAddr;
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
		MemSlot.location = intToString(memLoc);
		IMEM.push_back(MemSlot);
	}
}
