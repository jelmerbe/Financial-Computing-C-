#include "Lecture06/LinkedLists.hpp"

using namespace std;

LinkedList01::LinkedList01(int arg) : mData(arg) {
  mNext = NULL;
}

LinkedList01 * LinkedList01::getNext() const {
  return mNext;
}

void LinkedList01::append(int arg) {
  if(hasNext())
    mNext->append(arg); // note: recursive fn call
  else
    mNext = new LinkedList01(arg);
}


bool LinkedList01::hasNext() const {
  return bool(mNext);
}

int LinkedList01::getData() const {
  return mData;
}

void LinkedList01::setData(int arg){
  mData = arg;
}

std::ostream & LinkedList01::print(std::ostream & os) const {
  os << mData ;

  if (hasNext()){
    os << ", " ;
    mNext->print(os);    
  }
  else
    os << " -end-of-list.";

  return os;
}

LinkedList02::LinkedList02(int arg) : mData(arg) {
  mNext = NULL;
}

LinkedList02::~LinkedList02(){
  if(hasNext())
    delete mNext;
}


LinkedList02 * LinkedList02::getNext() const {
  return mNext;
}

void LinkedList02::append(int arg) {
  if(hasNext())
    mNext->append(arg); // note: recursive fn call
  else
    mNext = new LinkedList02(arg);
}

bool LinkedList02::hasNext() const {
  return bool(mNext);
}

int LinkedList02::getData() const {
  return mData;
}

void LinkedList02::setData(int arg){
  mData = arg;
}

std::ostream & LinkedList02::print(std::ostream & os) const {
  os << mData ;

  if (hasNext()){
    os << ", " ;
    mNext->print(os);    
  }
  else
    os << " -end-of-list.";

  return os;
}

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

LinkedList04::LinkedList04(int arg) : mData(arg) {}
// no need to set ptr to NULL, 
// the constructor of shared_ptr<...> does it 
// automatically

LinkedList04::LinkedList04Ptr LinkedList04::getNext() const {
  return mNext;
}

void LinkedList04::append(int arg) {
  if(hasNext())
    mNext->append(arg); // note: recursive fn call
  else
    mNext = LinkedList04Ptr(new LinkedList04(arg));
}

bool LinkedList04::hasNext() const {
  return bool(mNext);
}

int LinkedList04::getData() const {
  return mData;
}

void LinkedList04::setData(int arg){
  mData = arg;
}

std::ostream & LinkedList04::print(std::ostream & os) const {
  os << mData ;

  if (hasNext()){
    os << ", " ;
    mNext->print(os);    
  }
  else
    os << " -end-of-list.";

  return os;
}

ostream & operator<<(ostream & os, const LinkedList01 & ls){
  ls.print(os);
  return os;
}

ostream & operator<<(ostream & os, const LinkedList02 & ls){
  ls.print(os);
  return os;
}

ostream & operator<<(ostream & os, const LinkedList03 & ls){
  ls.print(os);
  return os;
}

ostream & operator<<(ostream & os, const LinkedList04 & ls){
  ls.print(os);
  return os;
}
