# File: Makefile
# Purpose: Build Project 3 executable

CXX      = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

SRC = \
  imageMods402.cpp \
  clipIntToRange.cpp \
  clearBadInput.cpp \
  readOneInt.cpp \
  readTwoInts.cpp \
  ColorClass.cpp \
  RowColumnClass.cpp \
  ColorImageClass.cpp \
  PatternClass.cpp \
  RectangleClass.cpp

OBJ  = $(SRC:.cpp=.o)
EXEC = imageMods402.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

# generic compile rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
