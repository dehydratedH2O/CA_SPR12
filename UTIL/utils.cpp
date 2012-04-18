#include <string>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "utils.h"

using namespace std;

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

int btoi (string& str)
{
    bool neg;
    int retval;

    if(str[0] == '0')
        neg = false;
    else
        neg = true;

    retval = strtol(str.c_str(),NULL,2);
    if(neg == true)
    {
        //undo 2's complement
        retval--;
        retval = ~retval;
    }

    return retval;
}
