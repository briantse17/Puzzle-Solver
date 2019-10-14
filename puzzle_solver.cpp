#include "puzzle_solver.h"

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph): b_(b), expansions_(0), ph_(ph)
{

}

PuzzleSolver::~PuzzleSolver()
{

}

void PuzzleSolver::run()
{
	Board* temp = new Board(b_);
	PuzzleMove* pmove = new PuzzleMove(temp);
	pmove->h = ph_->compute(b_);
	PuzzleMoveScoreComp c1;
	//initialize openlist (heap) with m = 2 and scorecomp object
	Heap<PuzzleMove*, PuzzleMoveScoreComp> openList(2, c1);
	PuzzleMoveSet closedList;
	//push first PuzzleMove into openlist
	openList.push(pmove);
	while(!openList.empty())
	{
		PuzzleMove* top = openList.top();
		closedList.insert(top);
		openList.pop();
		if(top->b->solved())
		{
			//backtrack from solution board to find solution set
			while(top->prev != NULL)
			{
				solution_.push_front(top->tileMove);
				top = top->prev;
			}
			break;
		}
		map<int, Board*> potMoves = top->b->potentialMoves();
		for (map<int,Board*>::iterator it = potMoves.begin(); it != potMoves.end(); ++it)
		{
			//initialize new PuzzleMove with tile value, parent's board state, and current board state  
			PuzzleMove* newMove = new PuzzleMove(it->first, it->second, top);
			newMove->h = ph_->compute(*(it->second));
			//if board state has never been visited before
			if(closedList.find(newMove) == closedList.end())
			{
				closedList.insert(newMove);
				openList.push(newMove);
				expansions_++;
			}
			//if the board state has already been visted before
			else
			{
				delete newMove;
			}
		}
	}
	//delete all remaining PuzzleMove in heap in closedlist
	for (PuzzleMoveSet::iterator it = closedList.begin(); it != closedList.end(); ++it)
	{
		delete *it;
	}
}

std::deque<int> PuzzleSolver::getSolution()
{
	return solution_;
}

int PuzzleSolver::getNumExpansions()
{
	return expansions_;
}