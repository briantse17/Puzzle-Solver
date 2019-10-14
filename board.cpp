#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  size_ = dim*dim;
  tiles_ = new int[size_];
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::~Board()
{
  //delete the tiles of each board
  delete[] tiles_;
}

Board::Board(const Board& b)
{
  size_ = b.size();
  tiles_ = new int[b.size()];
  for(int i = 0; i < b.size(); i++)
  {
    tiles_[i] = b.tiles_[i];
  }
}

void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(tiles_[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    stringstream ss;
    ss << "Invalid move of tile " << tile << " at ";
    ss << tr << "," << tc << " and blank spot at ";
    ss << br << "," << bc << endl;
    throw BoardMoveError(ss.str());
  }
  // Swap tile and blank spot
  tiles_[j] = tile;
  tiles_[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  map<int, Board*> potMoves;
  int j=-1;
  //find blank tile
  while(tiles_[++j] != 0);
  int br = j / dim();
  int bc = j % dim();
  //check if upper row is within bounds of board
  if(br-1 >= 0)
  {
    Board* potDown = new Board(*this);
    int target = potDown->tiles_[j-dim()];
    potDown->move(target);
    potMoves.insert(make_pair(target, potDown));

  }
  //check if lower row is within bounds of board
  if(br+1 < dim())
  {
    Board* potUp = new Board(*this);
    int target = tiles_[j+dim()];
    potUp->move(target);
    potMoves.insert(make_pair(target, potUp));
  }
  //check if left column is within bounds of board
  if(bc-1 >= 0)
  {
    Board* potRight = new Board(*this);
    int target = potRight->tiles_[j-1];
    potRight->move(target);
    potMoves.insert(make_pair(target, potRight));
  }
  //check if right column is within bounds of board
  if(bc+1 < dim())
  {
    Board* potLeft = new Board(*this);
    int target = potLeft->tiles_[j+1];
    potLeft->move(target);
    potMoves.insert(make_pair(target, potLeft));
  }
  return potMoves;
}

// Complete this function
bool Board::solved() const
{ 
  for(int i = 0; i < size(); i++)
  {
    //if any tiles are not in the correct place
    if(tiles_[i] != i)
    {
      return false;
    }
  }
  //all tiles are in the right spot on board
  return true;
}


const int& Board::operator[](int loc) const 
{ 
  return tiles_[loc]; 
}

int Board::size() const 
{ 
  return size_; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(size_));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}

bool Board::operator<(const Board& rhs) const
{
  //compare all tiles in both boards
  for(int i = 0; i < size(); i++)
  {
    if(tiles_[i] < rhs[i])
    {
      return true;
    }
    if(tiles_[i] > rhs[i])
    {
      return false;
    }
  }
  return false;
}


std::ostream& operator<<(std::ostream &os, const Board &b)
{
  int tile = 0;
  for(int i = 0; i < b.dim(); i++)
  {
    b.printRowBanner(os);
    for(int j = 0; j < b.dim(); j++)
    {
      //check if this is last column
      if(j == b.dim()-1)
      {
        //if tile value is 0
        if(b[tile] == 0)
        {
          //output blank
          os << "|  |" << endl;
          tile++;
        }
        //check if the tile value is two digits
        else if(b[tile] > 9)
        {
          //no space between first "|" and tile value
          os << "|" << b[tile] << "|" << endl;
          tile++;
        }
        
        else
        {
          os<< "| " << b[tile] << "|" << endl;
          tile++;
        }
      }
      else
      {
        //if tile value is 0
        if(b[tile] == 0)
        {
          //output blank
          os << "|  ";
          tile++;
        }
        else if (b[tile] > 9)
        {
          os << "|" << b[tile];
          tile++;
        }
        else
        {
          os << "| " << b[tile];
          tile++;
        }
      }
    }
  }
  b.printRowBanner(os);
  return os;
}