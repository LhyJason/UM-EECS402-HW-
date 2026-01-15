#include "CarClass.h"

#include <iostream>
using namespace std;

//Programmer: Andrew Morgan
//Purpose: A simple class to store data about a car participating in
//         a simualtion of traffic flow through an intersection.

//Assign the static attribute used for auto-assigning unique ids
int CarClass::nextIdVal = 0;

ostream& operator<<(
     ostream& outStream,
     const CarClass &carToPrint
     )
{
  outStream << "Car id: " << carToPrint.uniqueId <<
               " Travel dir: " << carToPrint.travelDir <<
               " Arrived at: " << carToPrint.arrivalTime;

  return outStream;
}

