#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }
  
  
  int size = atoi(argv[1]);
  int initMoves = atoi(argv[2]);
  int seed = atoi(argv[3]);
  int heuristic = atoi(argv[4]);
  //check if size is within boundaries
  if(size < 2 || size > 10)
  {
  	return 1;
  }
  //check if heuristic entered is valid
  if(heuristic < 0 || heuristic > 2)
  {
  	return 1;
  }
  bool solved = false;
  int decision;
  //make initial board
  Board b(size, initMoves, seed);
  cout << b << endl;
  while(!solved)
  {
  	cout << "Enter tile number to move or -1 for a cheat: ";
  	cin >> decision;
  	if(decision == -1)
  	{
  		if(heuristic == 0)
  		{
  			//create a new BFS object if heuristic value is 0 
  			PuzzleHeuristic* bfs = new PuzzleBFSHeuristic();
  			PuzzleSolver sol(b, bfs);
  			sol.run();
  			deque<int> solution = sol.getSolution();
  			cout << "Try this sequenece:" << endl;
  			for(int i = 0; i < int(solution.size()); i++)
  			{
  				cout << solution[i] << " ";
  			}
  			cout << endl;
  			cout << "(Expansions = " << sol.getNumExpansions() << ")" << endl;
  			delete bfs;
  		}
  		else if (heuristic == 1)
  		{
    		//create a new outofplace object if heuristic value is 1 
  			PuzzleHeuristic* out = new PuzzleOutOfPlaceHeuristic();
  			PuzzleSolver sol(b, out);
  			sol.run();
  			deque<int> solution = sol.getSolution();
  			cout << "Try this sequenece:" << endl;
  			for(int i = 0; i < int(solution.size()); i++)
  			{
  				cout << solution[i] << " ";
  			}
  			cout << endl;
  			cout << "(Expansions = " << sol.getNumExpansions() << ")" << endl;
  			delete out;
  		}
  		else if (heuristic == 2)
  		{
  			//create a new manhattan object if heuristic value is 2
  			PuzzleHeuristic* man = new PuzzleManhattanHeuristic();
  			PuzzleSolver sol(b, man);
  			sol.run();
  			deque<int> solution = sol.getSolution();
  			cout << "Try this sequenece:" << endl;
  			for(int i = 0; i < int(solution.size()); i++)
  			{
  				cout << solution[i] << " ";
  			}
  			cout << endl;
  			cout << "(Expansions = " << sol.getNumExpansions() << ")" << endl;
  			delete man;
  		}
  	}
  	//if the user is trying to move a tile, check if it's within boundaries of board
  	else if (decision > 0 && decision < int(b.size()))
  	{
  		//must use try catch block in case user tries to move a invalid block
  		//i.e. not next to a blank tile
  		try
  		{
  			b.move(decision);
	  		if(b.solved())
	  		{
	  			solved = true;
	  		}
  		}
  		catch(BoardMoveError ss)
  		{
  			cout << ss.what() << endl;
  			continue;
  		}
  	
  	}
  	else if (decision == 0)
  	{
  		return 1;
  	}
  	cout << b << endl;
  }







  return 0;
}
