#include <iostream>
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"
#include "CarClass.h"
using namespace std;

// Helper: print EventClass ordering test
void testEventList()
{
  cout << "\n=== Testing SortedListClass<EventClass> ordering ===\n";

  SortedListClass<EventClass> eventList;

  // Insert events out of order
  eventList.insertValue(EventClass(10, EVENT_ARRIVE_EAST));
  eventList.insertValue(EventClass(3, EVENT_ARRIVE_WEST));
  eventList.insertValue(EventClass(7, EVENT_CHANGE_GREEN_NS));
  eventList.insertValue(EventClass(10, EVENT_ARRIVE_SOUTH)); // duplicate time test
  eventList.insertValue(EventClass(1, EVENT_ARRIVE_NORTH));

  cout << "Expect times in sorted order: 1, 3, 7, 10, 10\n";
  cout << "Actual:\n";
  eventList.printForward();
}

void testSortedListInt()
{
  cout << "\n=== Testing SortedListClass<int> ===\n";

  SortedListClass<int> list;
  list.insertValue(5);
  list.insertValue(2);
  list.insertValue(9);
  list.insertValue(2); // duplicate test

  cout << "Expect: 2, 2, 5, 9\n";
  cout << "Actual:\n";
  list.printForward();

  int removed;
  list.removeFront(removed);
  cout << "removeFront => " << removed << " (expect 2)\n";

  list.removeLast(removed);
  cout << "removeLast => " << removed << " (expect 9)\n";

  cout << "Remaining list:\n";
  list.printForward();
}

void testFIFOInt()
{
  cout << "\n=== Testing FIFOQueueClass<int> ===\n";

  FIFOQueueClass<int> q;
  q.enqueue(10);
  q.enqueue(20);
  q.enqueue(30);

  cout << "Expect print: 10 20 30\n";
  cout << "Actual: ";
  q.print();

  int out;
  q.dequeue(out);
  cout << "dequeue => " << out << " (expect 10)\n";

  cout << "Remaining queue: ";
  q.print();
}

void testFIFOCar()
{
  cout << "\n=== Testing FIFOQueueClass<CarClass> ===\n";

  FIFOQueueClass<CarClass> carQ;

  carQ.enqueue(CarClass("East", 1));
  carQ.enqueue(CarClass("North", 2));
  carQ.enqueue(CarClass("West", 3));

  cout << "Expect 3 cars in FIFO order (using operator<<):\n";
  carQ.print();

  CarClass c;
  carQ.dequeue(c);
  cout << "dequeue => " << c << "\n";

  cout << "Remaining queue:\n";
  carQ.print();
}

int main()
{
  cout << "===== PHASE 1 TEMPLATE TEST =====\n";

  testSortedListInt();
  testEventList();
  testFIFOInt();
  testFIFOCar();

  cout << "\n===== ALL TESTS DONE =====\n";
  return 0;
}
