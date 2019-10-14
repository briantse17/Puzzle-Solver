#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  void trickleDown(int idx);
  void trickleUp(int size);
  PComparator c1;
  std::vector<T> vectorlist;
  int _m;


};


template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
{
  vectorlist = {};
  c1 = c;
  _m = m;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{
}


template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }

  return vectorlist[0];
}


// We will start pop() for you to handle the case of 
// calling pop on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  vectorlist[0] = vectorlist.back();
  vectorlist.pop_back();
  trickleDown(0);
}


template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleDown(int idx)
{
  //if child node not within the tree's boundariesu
  if(idx*_m+1 > int(vectorlist.size()-1))
  {
    return;
  }
  int bestChild = _m*idx+1;
  int rChild = bestChild;
  for(int i = 1; i < _m; i++)
  {
    if(rChild+1 <= int(vectorlist.size()-1))
    {
      rChild += 1;
      //if rChild is preferred to the current bestChild
      if(c1(vectorlist[rChild], vectorlist[bestChild]))
      {
        bestChild = rChild;
      }
    }
  }
  //if bestChild is preferred to current node 
  if(c1(vectorlist[bestChild], vectorlist[idx]))
  {
    std::swap(vectorlist[idx], vectorlist[bestChild]);
    trickleDown(bestChild);
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return vectorlist.empty();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  vectorlist.push_back(item);
  trickleUp(int(vectorlist.size()-1));
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp(int size)
{
  //parent for 0-based indexing
  int parent = (size-1)/_m;
  //if parent is root node or the current node is preffered to parent
  if(parent < 0 || !(c1(vectorlist[size], vectorlist[parent])))
  {
    return;
  }
  std::swap(vectorlist[size], vectorlist[parent]);
  trickleUp(parent);
}
#endif

