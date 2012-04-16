#include <string>

using namespace std;

EX::EX(void)
{
	RSVal = "";
	RTVal = "";
	signExtendedImmediate = "";
	PCin = "";
	
	ALUResult = "";
	PCout = "";
	
	control = "";
}

void EX::perform(void)
{
	int rc = doBranch();
	if(rc == -1)
	{
		cout << "ERROR IN EXECUTE." << endl;
		cout << "ERROR IN BRANCH DECISION/EXECUTION." << endl;
	}
	
	rc = ALUCompute();
	if(rc == -1)
	{
		cout << "ERROR IN EXECUTE." << endl;
		cout << "ERROR IN ALU COMPUTATION." << endl;
	}
}

int btoi (char* str)
{
    bool neg;
    int retval;

    if str[0] == '0'
        neg = false;
    else
        neg = true;

    retval = strtol(str,NULL,2);
    if neg
    {
        //undo 2's complement
        retval--;
        retval = ~retval;
    }

    return retval;
}

int ALUCompute(void)
{
    bool iType, rType = false;
    string ALUop;
    int rsi, rti, immi, result;

    //make all the binary into ints
    rsi = btoi(RSVal);
    rti = btoi(RTVal);
    immi = btoi(signExtendedImmediate);

    //decide if R or I type
    if control[1] == '1'
        iType = true;
    else
        rType = true;

    ALUop = control.substr(2,5);
    switch ALUop
    {
        case "00000":
            if control[10] == '1' //if j-type, ALU output is useless
                //ALUResult = "0000000000000000";
                result = 0;
            else:
                //add
                result = rsi + rti;
            break;
        case "00001":
            //sub
            result = rsi - rti;
            break;
        case "00010":
            //set if less than
            if (rsi < rti)
                result = 1;
            else
                result = 0;
            break;
        case "00011":
            //set if greater than
            if (rsi > rti)
                result = 1;
            else
                result = 0;
            break;
        case "00100":
            //set <=
            if (rsi <= rti)
                result = 1;
            else
                result = 0;
            break;
        case "00101":
            //set >=
            if (rsi >= rti)
                result = 1;
            else
                result = 0;
            break;
        case "00110":
            //and
            result = rsi & rti;
            break;
        case "00111":
            //or
            result = rsi | rti;
            break;
        case "01000":
            //nor
            result = ~(rsi | rti);
            break;
        case "01001":
            //xor
            result = rsi ^ rti;
            break;
        case "01010":
            //shift left
            break;
        case "01011":
            //shift right
            break;
        case "01100":
            //branch eq
            break;
        case "01101":
            //branch <
            break;
        case "01110":
            //branch >
            break;
        case "01111":
            //branch <=
            break;
        case "10000":
            //branch >=
            break;
        case "10001":
            //or imm
            break;
        case "10010":
            //and imm
            break;
        case "10011":
            //load word
            break;
        case "10100":
            //store word
            break;
        default:
            cout << "ERROR: invalid ALUop" << endl;
            return 1;
    }
}
