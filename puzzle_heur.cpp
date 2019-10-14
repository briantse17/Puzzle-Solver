#include "puzzle_heur.h"

int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int total = 0;
	for(int i = 0; i < b.size(); i++)
	{
		//skip the current tile if it's blank
		if(b[i] != i)
		{
			if(b[i] == 0)
			{
				continue;
			}
			//find the row and col of current tile
			int currR = i / b.dim();
			int currC = i % b.dim();
			//find row and col of where it should be
			int targR = b[i] / b.dim();
			int targC = b[i] % b.dim();
			//add absolute value of difference to total
			total += abs(targR - currR);
			total += abs(targC - currC);
		}
	}
	return total;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	int total = 0;
	for(int i = 0; i < b.size(); i++)
	{
		//if a tile is not in the right place, increment total
		if(b[i] != i)
		{
			++total;
		}
	}
	return total;
}

int PuzzleBFSHeuristic::compute(const Board& b)
{
	return 0;
}
