#include "puzzle_move.h"

using namespace std;

PuzzleMove::PuzzleMove(Board* board)
{
	
	tileMove = -1;
	b = board;
	prev = NULL;
	g = 0;
}

PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent)
{
	tileMove = tile;
	b = board;
	prev = parent;
	//moves from initial board state is one more than parent's
	g = parent->g+1;
}

PuzzleMove::~PuzzleMove()
{
	//must delete boards that PuzzleMove objects instantiate
	delete b;
}