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

class LinkedList01
{
public:
  LinkedList01(int);

  LinkedList01 * getNext() const;
  void append(int);
  bool hasNext() const;
  int getData() const;
  void setData(int);

  std::ostream & print(std::ostream &) const;

private:
  int mData;
  LinkedList01 * mNext;
};

class LinkedList02
{
public:
  LinkedList02(int);
  ~LinkedList02();	

  LinkedList02 * getNext() const;
  void append(int);
  bool hasNext() const;
  int getData() const;
  void setData(int);

  std::ostream & print(std::ostream &) const;

private:
  int mData;
  LinkedList02 * mNext;
};

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

class LinkedList04
{
public:
  typedef ptrnamespace::shared_ptr<LinkedList04> LinkedList04Ptr;

  LinkedList04(int);

  LinkedList04Ptr getNext() const;
  void append(int);
  bool hasNext() const;
  int getData() const;
  void setData(int);

  std::ostream & print(std::ostream &) const;

private:
  int mData;
  LinkedList04Ptr mNext;
};



std::ostream & operator<<(std::ostream &, const LinkedList01 &);
std::ostream & operator<<(std::ostream &, const LinkedList02 &);
std::ostream & operator<<(std::ostream &, const LinkedList03 &);
std::ostream & operator<<(std::ostream &, const LinkedList04 &);

#endif //_LINKED_LIST_01_H__
