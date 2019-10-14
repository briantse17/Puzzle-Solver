- **Name**: Brian Tse
- **USC ID**: 1664305014
- **Email**: briancht@usc.edu

PUZZLE SOLVER PROJECT:
This program simulates an interactive puzzle game in which users can either
try to solve the puzzle tile by tile or can also request for a hint.
If users ask for a hint, all they need to do is input "-1" when prompted
and the program will use a pre-specified heuristic to run A* search in 
order to return a correct answer sequence. If the user would like to use
BFS heuristic, they should enter 0 when running program. If they would like
to use the TilesOutOfPlace heuristic, they should enter 1. Finally, it they
would like to use the Manhattan Distance heuristic, they can enter 2. 

In order to run the program, please run the below code in terminal.
To compile: make puzzle
To run: ./puzzle puzzle_size initialmoves seed_value heurisitc
