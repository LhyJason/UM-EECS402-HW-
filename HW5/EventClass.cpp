#include <iostream>
using namespace std;

#include "EventClass.h"
#include "constants.h"

//Programmer: Andrew Morgan, Hanyang Liu
//Purpose: A simple class to represent event objects that can be used in
//         an event-driven simulation.  The overloaded insertion operator
//         for this class ties it to a simulation of traffic flow through
//         an intersection managed by a traffic light, but the rest of
//         the class is intended to be more generic to represent events
//         in most event-driven simulations.

// Overload "<"
// Comparison operator needed by templated SortedListClass.
// Event "A" is less than event "B" iff A's timeOccurs < B's timeOccurs.
bool EventClass::operator<(
     const EventClass &rhs
     ) const
{
  return timeOccurs < rhs.timeOccurs;
}

// Overload "<="
// Comparison operator needed by templated SortedListClass.
// Event "A" is less than or equal to event "B" iff A's timeOccurs <= B's
// timeOccurs.
bool EventClass::operator<=(
     const EventClass &rhs
     ) const
{
  return timeOccurs <= rhs.timeOccurs;
}

ostream& operator<<(
     ostream& outStream,
     const EventClass &eventToPrint
     )
{
  outStream << "[";
  outStream << "Event Type: ";
  if (eventToPrint.typeId == EVENT_ARRIVE_EAST)
  {
    outStream << "East-Bound Arrival";
  }
  else if (eventToPrint.typeId == EVENT_ARRIVE_WEST)
  {
    outStream << "West-Bound Arrival";
  }
  else if (eventToPrint.typeId == EVENT_ARRIVE_NORTH)
  {
    outStream << "North-Bound Arrival";
  }
  else if (eventToPrint.typeId == EVENT_ARRIVE_SOUTH)
  {
    outStream << "South-Bound Arrival";
  }
  else if (eventToPrint.typeId == EVENT_CHANGE_GREEN_EW)
  {
    outStream << "Light Change to EW Green";
  }
  else if (eventToPrint.typeId == EVENT_CHANGE_YELLOW_EW)
  {
    outStream << "Light Change to EW Yellow";
  }
  else if (eventToPrint.typeId == EVENT_CHANGE_GREEN_NS)
  {
    outStream << "Light Change to NS Green";
  }
  else if (eventToPrint.typeId == EVENT_CHANGE_YELLOW_NS)
  {
    outStream << "Light Change to NS Yellow";
  }
  else
  {
    outStream << "UNKNOWN";
  }
  outStream << " Time: " << eventToPrint.timeOccurs;
  outStream << "]";
  return outStream;
}

