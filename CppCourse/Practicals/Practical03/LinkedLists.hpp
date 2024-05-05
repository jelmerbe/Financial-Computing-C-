#ifndef _LINKED_LIST_01_H__
#define _LINKED_LIST_01_H__

#include <iostream>

#if __cplusplus > 199711L
  #include <memory> // c++11
  namespace ptrnamespace = std;
#else
  #include <boost/shared_ptr.hpp> // boost
  namespace ptrnamespace = boost;
#endif

class LinkedList03
{
public:
  LinkedList03(int);
  LinkedList03(const LinkedList03 &);
  ~LinkedList03();	

  LinkedList03 & operator=(const LinkedList03 &);

  LinkedList03 * getNext() const;
  void append(int);
  bool hasNext() const;
  int getData() const;
  void setData(int);

  std::ostream & print(std::ostream &) const;

private:
  void releaseNext();
  void acquireNext(LinkedList03 *);

private:
  int mData;
  LinkedList03 * mNext;
  unsigned int mRefCount;
};

std::ostream & operator<<(std::ostream &, const LinkedList03 &);

#endif //_LINKED_LIST_01_H__
