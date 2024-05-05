#include "Practical03/LinkedLists.hpp"

using namespace std;


LinkedList03::LinkedList03(int arg) : mData(arg), mRefCount(0) {
  mNext = NULL;
}

LinkedList03::LinkedList03(const LinkedList03 & arg) 
: mData(arg.mData), mRefCount(0) {
  acquireNext(arg.mNext);
}

LinkedList03::~LinkedList03(){
  releaseNext();
}

LinkedList03 & LinkedList03::operator=(const LinkedList03 & arg){
  releaseNext();
  mData = arg.mData;
  acquireNext(arg.mNext);
  return *this;
}

void LinkedList03::releaseNext(){
  if(hasNext() && (mNext->mRefCount > 1))
    mNext->mRefCount--;
  else if(hasNext())
    delete mNext;
}

void LinkedList03::acquireNext(LinkedList03 * arg){
  mNext = arg;
  if(arg)
    arg->mRefCount++;
}

LinkedList03 * LinkedList03::getNext() const {
  return mNext;
}

void LinkedList03::append(int arg) {
  if(hasNext())
    mNext->append(arg); // note: recursive fn call
  else 
    acquireNext(new LinkedList03(arg));
}

bool LinkedList03::hasNext() const {
  return bool(mNext);
}

int LinkedList03::getData() const {
  return mData;
}

void LinkedList03::setData(int arg){
  mData = arg;
}

std::ostream & LinkedList03::print(std::ostream & os) const {
  os << mData ;

  if (hasNext()){
    os << ", " ;
    mNext->print(os);    
  }
  else
    os << " -end-of-list.";

  return os;
}


ostream & operator<<(ostream & os, const LinkedList03 & ls){
  ls.print(os);
  return os;
}

