#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generator seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

// Schedule next arrival event with specific direction.
void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{
  int eventType = EVENT_UNKNOWN;
  double mean = 0.0;
  double stddev = 0.0;

  // Select the proper arrival distribution parameters and event type
  // based on the specified travel direction.
  if (travelDir == EAST_DIRECTION)
  {
    eventType = EVENT_ARRIVE_EAST;
    mean = eastArrivalMean;
    stddev = eastArrivalStdDev;
  }
  else if (travelDir == WEST_DIRECTION)
  {
    eventType = EVENT_ARRIVE_WEST;
    mean = westArrivalMean;
    stddev = westArrivalStdDev;
  }
  else if (travelDir == NORTH_DIRECTION)
  {
    eventType = EVENT_ARRIVE_NORTH;
    mean = northArrivalMean;
    stddev = northArrivalStdDev;
  }
  else if (travelDir == SOUTH_DIRECTION)
  {
    eventType = EVENT_ARRIVE_SOUTH;
    mean = southArrivalMean;
    stddev = southArrivalStdDev;
  }
  else
  {
    // This should never happen unless the caller provides an invalid direction.
    cout << "ERROR: scheduleArrival called with invalid travel direction: "
         << travelDir << endl;
    return;
  }

  // Compute the time offset until the next arrival using a positive-normal
  // distribution. A value of zero is allowed, meaning cars may arrive
  // at the same simulation time.
  int offset = getPositiveNormal(mean, stddev);
  int eventTime = currentTime + offset;

  // Create and insert the new arrival event into the event list.
  EventClass newEvt(eventTime, eventType);
  eventList.insertValue(newEvt);

  // Required output format, matching the project specifications:
  // Time: <currentTime> Scheduled [Event Type: ... Time: ...]
  cout << "Time: " << currentTime << " Scheduled " << newEvt << endl;
}

void IntersectionSimulationClass::scheduleLightChange()
{
  int nextEventType = EVENT_UNKNOWN;
  int offset = 0;

  // Determine the next light change event type and the time offset
  // based on the current state of the traffic light.
  if (currentLight == LIGHT_GREEN_EW)
  {
    nextEventType = EVENT_CHANGE_YELLOW_EW;
    offset = eastWestGreenTime;
  }
  else if (currentLight == LIGHT_YELLOW_EW)
  {
    nextEventType = EVENT_CHANGE_GREEN_NS;
    offset = eastWestYellowTime;
  }
  else if (currentLight == LIGHT_GREEN_NS)
  {
    nextEventType = EVENT_CHANGE_YELLOW_NS;
    offset = northSouthGreenTime;
  }
  else if (currentLight == LIGHT_YELLOW_NS)
  {
    nextEventType = EVENT_CHANGE_GREEN_EW;
    offset = northSouthYellowTime;
  }
  else
  {
    // Light state must be invalid
    cout << "ERROR: scheduleLightChange called with invalid light state: "
         << currentLight << endl;
    return; 
  }

  // Compute the scheduled time for the next light change event.
  int eventTime = currentTime + offset;

  // Create and insert the event into the event list.
  EventClass newEvt(eventTime, nextEventType);
  eventList.insertValue(newEvt);

  // Required output format, matching project specifications:
  // Time: <currentTime> Scheduled [Event Type: ... Time: ...]
  cout << "Time: " << currentTime << " Scheduled " << newEvt << endl;
}

bool IntersectionSimulationClass::handleNextEvent()
{
  EventClass nextEvent;

  // If there are no events left, the simulation stops quietly.
  if (!eventList.getElemAtIndex(0, nextEvent))
  {
    return false;
  }

  // If the next event is scheduled after the simulation end time,
  // print the required message and stop the simulation.
  if (nextEvent.getTimeOccurs() > timeToStopSim)
  {
    cout << endl << "Next event occurs AFTER the simulation end time ("
         << nextEvent << ")!" << endl;
    return false;
  }

  // Remove the next event from the list and handle it.
  eventList.removeFront(nextEvent);

  // Advance current time to the event time.
  currentTime = nextEvent.getTimeOccurs();

  // Print which event we are handling, matching sample output:
  cout << endl << "Handling " << nextEvent << endl;

  int eventType = nextEvent.getType();

  // ===== ARRIVAL EVENTS =====
  if (eventType == EVENT_ARRIVE_EAST)
  {
    CarClass newCar(EAST_DIRECTION, currentTime);
    eastQueue.enqueue(newCar);

    int curLen = eastQueue.getNumElems();
    if (curLen > maxEastQueueLength)
    {
      maxEastQueueLength = curLen;
    }

    cout << "Time: " << currentTime << " " << newCar
         << " - new queue length: " << curLen << endl;

    scheduleArrival(EAST_DIRECTION);
  }
  else if (eventType == EVENT_ARRIVE_WEST)
  {
    CarClass newCar(WEST_DIRECTION, currentTime);
    westQueue.enqueue(newCar);

    int curLen = westQueue.getNumElems();
    if (curLen > maxWestQueueLength)
    {
      maxWestQueueLength = curLen;
    }

    cout << "Time: " << currentTime << " " << newCar
         << " - new queue length: " << curLen << endl;

    scheduleArrival(WEST_DIRECTION);
  }
  else if (eventType == EVENT_ARRIVE_NORTH)
  {
    CarClass newCar(NORTH_DIRECTION, currentTime);
    northQueue.enqueue(newCar);

    int curLen = northQueue.getNumElems();
    if (curLen > maxNorthQueueLength)
    {
      maxNorthQueueLength = curLen;
    }

    cout << "Time: " << currentTime << " " << newCar
         << " - queue length: " << curLen << endl;

    scheduleArrival(NORTH_DIRECTION);
  }
  else if (eventType == EVENT_ARRIVE_SOUTH)
  {
    CarClass newCar(SOUTH_DIRECTION, currentTime);
    southQueue.enqueue(newCar);

    int curLen = southQueue.getNumElems();
    if (curLen > maxSouthQueueLength)
    {
      maxSouthQueueLength = curLen;
    }

    cout << "Time: " << currentTime << " " << newCar
         << " - queue length: " << curLen << endl;

    scheduleArrival(SOUTH_DIRECTION);
  }

  // ===== LIGHT CHANGE: EW GREEN -> EW YELLOW (advance on EW green) =====
  else if (eventType == EVENT_CHANGE_YELLOW_EW)
  {
    cout << "Advancing cars on east-west green!" << endl;

    int eastBefore = eastQueue.getNumElems();
    int westBefore = westQueue.getNumElems();
    cout << "  East-bound queue length before advancing: "
         << eastBefore << endl;
    cout << "  West-bound queue length before advancing: "
         << westBefore << endl;

    int numEastAdvanced = 0;
    int numWestAdvanced = 0;

    // Advance east-bound cars on green.
    {
      int i = 0;
      while (i < eastWestGreenTime && eastQueue.getNumElems() > 0)
      {
        CarClass car;
        eastQueue.dequeue(car);
        cout << "  Car #" << car.getId()
             << " advances east-bound on green" << endl;

        numEastAdvanced++;
        numTotalAdvancedEast++;
        i++;
      }
    }

    // Advance west-bound cars on green.
    {
      int i = 0;
      while (i < eastWestGreenTime && westQueue.getNumElems() > 0)
      {
        CarClass car;
        westQueue.dequeue(car);
        cout << "  Car #" << car.getId()
             << " advances west-bound on green" << endl;

        numWestAdvanced++;
        numTotalAdvancedWest++;
        i++;
      }
    }

    cout << "  At time " << currentTime << ", "
         << numEastAdvanced
         << " east-bound cars advanced on green, remaining queue length: "
         << eastQueue.getNumElems() << endl;
    cout << "  At time " << currentTime << ", "
         << numWestAdvanced
         << " west-bound cars advanced on green, remaining queue length: "
         << westQueue.getNumElems() << endl;

    currentLight = LIGHT_YELLOW_EW;
    scheduleLightChange();
  }

  // ===== LIGHT CHANGE: EW YELLOW -> NS GREEN (advance on EW yellow) =====
  else if (eventType == EVENT_CHANGE_GREEN_NS)
  {
    cout << "Advancing cars on east-west yellow" << endl;
  
    int eastBefore = eastQueue.getNumElems();
    int westBefore = westQueue.getNumElems();
    cout << "  East-bound queue length before advancing: "
         << eastBefore << endl;
    cout << "  West-bound queue length before advancing: "
         << westBefore << endl;
  
    int numEastAdvanced = 0;
    int numWestAdvanced = 0;
  
    // East-bound on yellow.
    if (eastBefore == 0)
    {
      cout << "  No cars in east-bound queue waiting to advance!" << endl;
    }
    else
    {
      bool keepAdvancingEast = true;
      int i = 0;
      while (i < eastWestYellowTime &&
             keepAdvancingEast &&
             eastQueue.getNumElems() > 0)
      {
        int roll = getUniform(1, 100);
        if (roll <= percentCarsAdvanceOnYellow)
        {
          cout << "  Next car will advance east-bound on yellow" << endl;
        
          CarClass car;
          eastQueue.dequeue(car);
          cout << "  Car #" << car.getId()
               << " advances east-bound on yellow" << endl;
        
          numEastAdvanced++;
          numTotalAdvancedEast++;
        }
        else
        {
          cout << "  Next car will NOT advance east-bound on yellow" << endl;
          keepAdvancingEast = false;
        }
        i++;
      }
      if (eastQueue.getNumElems() == 0)
      {
        cout << "  No cars in east-bound queue waiting to advance!" << endl;
      }
    }
  
    // West-bound on yellow.
    if (westBefore == 0)
    {
      cout << "  No cars in west-bound queue waiting to advance!" << endl;
    }
    else
    {
      bool keepAdvancingWest = true;
      int i = 0;
      while (i < eastWestYellowTime &&
             keepAdvancingWest &&
             westQueue.getNumElems() > 0)
      {
        int roll = getUniform(1, 100);
        if (roll <= percentCarsAdvanceOnYellow)
        {
          cout << "  Next car will advance west-bound on yellow" << endl;
        
          CarClass car;
          westQueue.dequeue(car);
          cout << "  Car #" << car.getId()
               << " advances west-bound on yellow" << endl;
        
          numWestAdvanced++;
          numTotalAdvancedWest++;
        }
        else
        {
          cout << "  Next car will NOT advance west-bound on yellow" << endl;
          keepAdvancingWest = false;
        }
        i++;
      }
      if (westQueue.getNumElems() == 0)
      {
        cout << "  No cars in west-bound queue waiting to advance!" << endl;
      }
    }
  
    cout << "  At time " << currentTime << ", "
         << numEastAdvanced
         << " east-bound cars advanced on yellow, remaining queue length: "
         << eastQueue.getNumElems() << endl;
    cout << "  At time " << currentTime << ", "
         << numWestAdvanced
         << " west-bound cars advanced on yellow, remaining queue length: "
         << westQueue.getNumElems() << endl;
  
    currentLight = LIGHT_GREEN_NS;
    scheduleLightChange();
  }

  // ===== LIGHT CHANGE: NS GREEN -> NS YELLOW (advance on NS green) =====
  else if (eventType == EVENT_CHANGE_YELLOW_NS)
  {
    cout << "Advancing cars on north-south green" << endl;

    int northBefore = northQueue.getNumElems();
    int southBefore = southQueue.getNumElems();
    cout << "  North-bound queue length before advancing: "
         << northBefore << endl;
    cout << "  South-bound queue length before advancing: "
         << southBefore << endl;

    int numNorthAdvanced = 0;
    int numSouthAdvanced = 0;

    // North-bound on green.
    {
      int i = 0;
      while (i < northSouthGreenTime && northQueue.getNumElems() > 0)
      {
        CarClass car;
        northQueue.dequeue(car);
        cout << "  Car #" << car.getId()
             << " advances north-bound on green" << endl;

        numNorthAdvanced++;
        numTotalAdvancedNorth++;
        i++;
      }
    }

    // South-bound on green.
    {
      int i = 0;
      while (i < northSouthGreenTime && southQueue.getNumElems() > 0)
      {
        CarClass car;
        southQueue.dequeue(car);
        cout << "  Car #" << car.getId()
             << " advances south-bound on green" << endl;

        numSouthAdvanced++;
        numTotalAdvancedSouth++;
        i++;
      }
    }

    cout << "  At time " << currentTime << ", "
         << numNorthAdvanced
         << " north-bound cars advanced on green, remaining queue length: "
         << northQueue.getNumElems() << endl;
    cout << "  At time " << currentTime << ", "
         << numSouthAdvanced
         << " south-bound cars advanced on green, remaining queue length: "
         << southQueue.getNumElems() << endl;

    currentLight = LIGHT_YELLOW_NS;
    scheduleLightChange();
  }

  // ===== LIGHT CHANGE: NS YELLOW -> EW GREEN (advance on NS yellow) =====
  // ===== LIGHT CHANGE: NS YELLOW -> EW GREEN (advance on NS yellow) =====
  else if (eventType == EVENT_CHANGE_GREEN_EW)
  {
    cout << "Advancing cars on north-south yellow" << endl;

    int northBefore = northQueue.getNumElems();
    int southBefore = southQueue.getNumElems();
    cout << "  North-bound queue length before advancing: "
         << northBefore << endl;
    cout << "  South-bound queue length before advancing: "
         << southBefore << endl;

    int numNorthAdvanced = 0;
    int numSouthAdvanced = 0;

    // North-bound on yellow.
    if (northBefore == 0)    // ← 用 northBefore，而不是现查长度
    {
      cout << "  No cars in north-bound queue waiting to advance!" << endl;
    }
    else
    {
      bool keepAdvancingNorth = true;
      int i = 0;
      while (i < northSouthYellowTime &&
             keepAdvancingNorth &&
             northQueue.getNumElems() > 0)
      {
        int roll = getUniform(1, 100);
        if (roll <= percentCarsAdvanceOnYellow)
        {
          cout << "  Next car will advance north-bound on yellow" << endl;

          CarClass car;
          northQueue.dequeue(car);
          cout << "  Car #" << car.getId()
               << " advances north-bound on yellow" << endl;

          numNorthAdvanced++;
          numTotalAdvancedNorth++;
        }
        else
        {
          cout << "  Next car will NOT advance north-bound on yellow" << endl;
          keepAdvancingNorth = false;
        }
        i++;
      }
      if (northQueue.getNumElems() == 0)
      {
        cout << "  No cars in north-bound queue waiting to advance!" << endl;
      }
    }

    // South-bound on yellow.
    if (southBefore == 0)
    {
      cout << "  No cars in south-bound queue waiting to advance!" << endl;
    }
    else
    {
      bool keepAdvancingSouth = true;
      int i = 0;
      while (i < northSouthYellowTime &&
             keepAdvancingSouth &&
             southQueue.getNumElems() > 0)
      {
        int roll = getUniform(1, 100);
        if (roll <= percentCarsAdvanceOnYellow)
        {
          cout << "  Next car will advance south-bound on yellow" << endl;

          CarClass car;
          southQueue.dequeue(car);
          cout << "  Car #" << car.getId()
               << " advances south-bound on yellow" << endl;

          numSouthAdvanced++;
          numTotalAdvancedSouth++;
        }
        else
        {
          cout << "  Next car will NOT advance south-bound on yellow" << endl;
          keepAdvancingSouth = false;
        }
        i++;
      }
      if (southQueue.getNumElems() == 0)
      {
        cout << "  No cars in south-bound queue waiting to advance!" << endl;
      }
    }

    cout << "  At time " << currentTime << ", "
         << numNorthAdvanced
         << " north-bound cars advanced on yellow, remaining queue length: "
         << northQueue.getNumElems() << endl;
    cout << "  At time " << currentTime << ", "
         << numSouthAdvanced
         << " south-bound cars advanced on yellow, remaining queue length: "
         << southQueue.getNumElems() << endl;

    currentLight = LIGHT_GREEN_EW;
    scheduleLightChange();
  }
  else
  {
    // Unknown event type (should not occur).
    cout << "ERROR: Unknown event type encountered in handleNextEvent: "
         << eventType << endl;
  }

  // If we reach here, one event was handled successfully.
  return true;
}


void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
