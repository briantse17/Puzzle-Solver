CXX=g++
CXXFLAGS=-g -Wall -std=c++11
DEFS=-DDEBUG

OBJS=board.o puzzle_heur.o puzzle_move.o puzzle_solver.o puzzle.o 

all: puzzle

puzzle: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

puzzle.o: puzzle.cpp puzzle_solver.h puzzle_heur.h board.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle.cpp
board.o: board.cpp board.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c board.cpp
puzzle_heur.o: puzzle_heur.cpp puzzle_heur.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_heur.cpp
puzzle_solver.o: puzzle_solver.cpp puzzle_solver.h heap.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_solver.cpp
puzzle_move.o: puzzle_move.cpp puzzle_move.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_move.cpp

clean:
	rm -f *.o puzzle
