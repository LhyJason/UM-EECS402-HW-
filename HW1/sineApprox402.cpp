#include <iostream>
using namespace std;

/*
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 09/14/2025
 * 
 * Purpose: This program let users input angle in degrees or radians,
 * then if input is degrees it will convert degrees to radians. Users
 * also can choose terms they like for Taylor series to approximate the
 * sine value of angle. In the end, the program outputs all other terms
 * approximate value for users to compare. 
 */

// Global Constant
const double PI_VALUE = 3.14159265359;
const double TWO_PI = 2.0 * PI_VALUE;
const char DEGREES = 'd';
const char RADIANS = 'r';
const int LOWER_BOUND_OF_TERMNUM = 1;
const int UPPER_BOUND_OF_TERMNUM = 5;
const int LOWER_BOUND_OF_INITIAL_VALUE = 0;
const int UPPER_BOUND_OF_INITIAL_VALUE = 12;
const double RADIAN_PER_PI = 180.0;

// Functions declaration
/**
 * @brief Converts an angle from degrees to radians.
 * 
 * Uses the constant PI_VALUE to convert the input angle given in degrees 
 * into its equivalent in radians.
 * 
 * @param angleDeg Input angle in degrees
 * @return double  The converted angle in radians.
 */
double degreesToRadians(const double angleDeg);

/**
 * @brief Computes baseVal^exponentVal
 * 
 * Computes baseVal raised to the integer exponent exponentVal. 
 * The result is stored in the reference parameter outResult.
 * 
 * @param baseVal Base value
 * @param exponentVal Exponent value
 * @param outResult The result of (Base value) ^ (Exponent value)
 * @return true  If computation is succeeded.
 * @return false  If computation is failure. The output value is undefined.
 */
bool toThePower(const double baseVal, const int exponentVal, double& outResult);

/**
 * @brief Computes factorial of initial value
 * 
 * Geting Factorial of inVal. But only for number between 0 to 12.
 * 
 * @param inVal Initial value
 * @param outFactorial The result of Initial value factorial
 * @return true  If computation is succeeded.
 * @return false  If computation is failure. The output value is undefined.
 */
bool computeFactorial(const int inVal, int& outFactorial);

/**
 * @brief Approximates the sine of an angle using Taylor series
 * 
 * Using Taylor series with specificated number of terms to get
 * the sine value of angle.
 * 
 * @param angleRad Angle input in radians
 * @param numTerms The number of terms will use in Taylor series
 * @param outSineVal Result of angle sine value
 * @return true  If computation is succeeded.
 * @return false  If computation is failure. The output value is undefined.
 */
bool approximateSine(const double angleRad, const int numTerms, double& outSineVal);

// Main function
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main() {
    // Unit input
    char unitInput;
    cout << "Would you like to enter angle in degrees (" << DEGREES 
    << ") or radians (" << RADIANS << ")? ";
    cin >> unitInput;

    if (unitInput != DEGREES && unitInput != RADIANS){ 
        // Check unit whether valid
        cout << "ERROR: Invalid input - must respond with either " << DEGREES 
        << " or " << RADIANS << "!" << endl;
        cout << "Unable to provide results due to invalid inputs!" << endl;
    } else {
        double angle;
        cout << "Enter the angle: ";
        cin >> angle;
        if (unitInput == DEGREES){
            angle = degreesToRadians(angle);
        }

        // Numbers of terms
        int termNum;
        cout << "How many terms to use in the series (" << LOWER_BOUND_OF_TERMNUM 
        << " to " << UPPER_BOUND_OF_TERMNUM << " inclusive): ";
        cin >> termNum;

        if (termNum < LOWER_BOUND_OF_TERMNUM || termNum > UPPER_BOUND_OF_TERMNUM){
            cout << "ERROR: Invalid input - must respond with value between " 
            << LOWER_BOUND_OF_TERMNUM << " and " << UPPER_BOUND_OF_TERMNUM << "!" << endl;
            cout << "Unable to provide results due to invalid inputs!" << endl;
        } else {
        // Result
        double result;
        approximateSine(angle, termNum, result);
        cout << "sin(angle) = " << result << endl;

        // Other terms values
        cout << endl;
        cout << "Here are results for other numbers of terms:" << endl;
        int i = LOWER_BOUND_OF_TERMNUM;

        while(i <= UPPER_BOUND_OF_TERMNUM){
            if (i != termNum){
                double result;
                approximateSine(angle, i, result);
                cout << "  # terms: " << i << " result: " << result << endl;
                }
            i++;
            }
        }
    }

    return 0;
}
#endif

// Functions definations 
double degreesToRadians(const double angleDeg){
    return angleDeg * PI_VALUE / RADIAN_PER_PI;
}

bool toThePower(const double baseVal, const int exponentVal, double& outResult){
    // Input check
    if (exponentVal < 0){
        return false;
    } 
    
    // Special case
    if (exponentVal == 0){
        outResult = 1.0;
        return true;
    }

    outResult = 1.0;
    for (int i = 0; i < exponentVal; i++){
        outResult *= baseVal;
    }
    return true;
}

bool computeFactorial(const int inVal, int& outFactorial){
    // Input check
    if (inVal < LOWER_BOUND_OF_INITIAL_VALUE || inVal > UPPER_BOUND_OF_INITIAL_VALUE){
        return false;
    }

    // Special case
    if (inVal == 0){
        outFactorial = 1;
        return true;
    }
    
    outFactorial = 1;
    for (int i = 1; i <= inVal; i++){
        outFactorial *= i;
    }
    return true;
}

bool approximateSine(const double angleRad, const int numTerms, double& outSineVal){
    // Input check
    if (numTerms < LOWER_BOUND_OF_TERMNUM || numTerms > UPPER_BOUND_OF_TERMNUM){
        return false;
    }

    // Normalization
    double normalAngleRad = angleRad;
    while (normalAngleRad < -PI_VALUE){
        normalAngleRad +=  TWO_PI;
    }
    while (normalAngleRad > PI_VALUE){
        normalAngleRad -= TWO_PI;
    }

    outSineVal = 0.0;
    for (int n = 0; n < numTerms; n++){
        // Define three variables in Taylor series and two variables to get result
        int exponentNum = 2 * n + 1;
        int factorialNum = exponentNum;
        
        double sign = 0.0;
        double powerResult = 0.0;
        int factorialResult = 0;

        // Input check for three functions
        if (!toThePower(-1.0, n, sign)) {
            return false; 
        }

        if (!toThePower(normalAngleRad, exponentNum, powerResult)){
            return false;
        }

        if(!computeFactorial(factorialNum, factorialResult)){
            return false;
        }

        // Using Taylor series
        outSineVal += sign * powerResult / factorialResult; 
    }
    return true;
}