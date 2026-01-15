# File: Makefile
# Purpose: Build Project 5 executable

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -g

SRC = \
	CarClass.cpp \
	EventClass.cpp \
	IntersectionSimulationClass.cpp \
	random.cpp \
	project5.cpp

OBJ = $(SRC:.cpp=.o)
EXEC = proj5.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

# generic compile rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:# File: Makefile
# Purpose: Build Project 5 executable

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -g

SRC = \
    CarClass.cpp \
    EventClass.cpp \
    IntersectionSimulationClass.cpp \
    random.cpp \
    project5.cpp

# Object files built from .cpp sources
OBJ = $(SRC:.cpp=.o)

EXEC = proj5.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

# Generic compile rule
%.o: %.cpp \
      LinkedNodeClass.h SortedListClass.h SortedListClass.inl \
      FIFOQueueClass.h FIFOQueueClass.inl
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

	rm -f $(OBJ) $(EXEC)
