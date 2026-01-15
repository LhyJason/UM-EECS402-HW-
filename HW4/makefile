# File: Makefile
# Purpose: Build Project 4 executable

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -g

SRC = \
	LinkedNodeClass.cpp \
	SortedListClass.cpp \
	FIFOQueueClass.cpp \
	LIFOStackClass.cpp \
	project4.cpp

OBJ = $(SRC:.cpp=.o)
EXEC = proj4.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

# generic compile rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
