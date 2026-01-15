#include "readTwoInts.h"
#include "clearBadInput.h"
#include "constants.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

/*
 * Function: readTwoInts
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 * 
 * Purpose:
 *   Read two integers from users.
 */

bool readTwoInts(const std::string &prompt, int &a, int &b)
{
    cout << prompt;
    if (!(cin >> a >> b))
    {
        cout << ERROR_ALERT << endl;
        clearBadInput();
        return false;
    }
    return true;
}
