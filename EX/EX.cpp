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
	rc = ALUCompute();
	if(rc == -1)
	{
		cout << "ERROR IN EXECUTE." << endl;
		cout << "ERROR IN ALU COMPUTATION." << endl;
	}

	int rc = doBranch();
	if(rc == -1)
	{
		cout << "ERROR IN EXECUTE." << endl;
		cout << "ERROR IN BRANCH DECISION/EXECUTION." << endl;
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

string itob (int n, int l)
{
    bool neg;
    string result;

    if (n < 0)
        neg = true;
    else
        neg = false;

    if (neg)
    {
        //2's complement
        n = ~n;
        n++;
    }

    do result.push_back( '0' + (n & 1));
    while (n >>= 1);

    reverse(result.begin(), result.end());

    //padding
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
        //overflow
        cout << "ERROR: binary " << n << " bigger than " << l << " bits" << endl;

    return result;
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
            string temp = RSVal;
            for (int i = 0; i < immi; i++)
                temp.append("0");
            temp = temp.substr((temp.length()-16),16);
            result = btoi(temp, 16);
            break;
        case "01011":
            //shift right
            string temp = RSVal;
            for (int i = 0; i < immi; i++)
                temp.insert(0,temp[0]);
            temp = temp.substr(0,16);
            result = btoi(temp, 16);
            break;
        case "01100":
            //branch eq
            if (rsi == rti)
                control[11] = '1';
            else
                control[11] = '0';
            result = 0;
            break;
        case "01101":
            //branch <
            if (rsi < rti)
                control[11] = '1';
            else
                control[11] = '0';
            result = 0;
            break;
        case "01110":
            //branch >
            if (rsi > rti)
                control[11] = '1';
            else
                control[11] = '0';
            result = 0;
            break;
        case "01111":
            //branch <=
            if (rsi <= rti)
                control[11] = '1';
            else
                control[11] = '0';
            result = 0;
            break;
        case "10000":
            //branch >=
            if (rsi >= rti)
                control[11] = '1';
            else
                control[11] = '0';
            result = 0;
            break;
        case "10001":
            //or imm
            result = rti | immi;
            break;
        case "10010":
            //and imm
            result = rti & immi;
            break;
        case "10011":
            //load word
            result = rti + immi;
            break;
        case "10100":
            //store word
            result = rti + immi;
            break;
        default:
            cout << "ERROR: invalid ALUop" << endl;
            return 1;
    }
    ALUResult = itob(result, 16);
    return 0;
}

int doBranch(void)
{
    if (control[11] == '1')
    {
        string hi9 = PCin.substr(0,9);
        string lo7 = signExtendedImmiediate.substr(8,7);
        lo7.append("0");
        lo7 = lo7.substr(0,7);
        hi9.append(lo7);
        PCout = hi9;
    }
    else
        PCout = PCin;
    return 0;
}
