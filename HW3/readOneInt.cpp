#include "readOneInt.h"
#include "clearBadInput.h"
#include "constants.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

/*
 * Function: readOneInt
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 * 
 * Purpose:
 *   Read two integers from users.
 */

bool readOneInt(const std::string &prompt, int &a)
{
    cout << prompt;
    if (!(cin >> a))
    {
        cout << ERROR_ALERT << endl;
        clearBadInput();
        return false;
    }
    return true;
}
