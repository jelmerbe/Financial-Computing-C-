#include <iostream>
#include <vector>
#include <iterator> // for ostream_iterator
#include <algorithm> // for copy
#include "Utils/UtilityFunctions.hpp" // for NormalDist
#include "Lecture0708/FunctionExample.hpp" // for NormalDist
using namespace std;
using namespace utils;

void containerExample(){
  vector<double> dVec(5);
  NormalDist(dVec); 

  copy(dVec.begin(),dVec.end(),ostream_iterator<double>(cout," "));
  cout<< endl;

  //removing negative entries
  vector<double>::iterator iter=dVec.begin();
  while(iter!=dVec.end()){
    if((*iter)<0)
      iter=dVec.erase(iter);
    else 
      ++iter;
  }

  copy(dVec.begin(),dVec.end(),ostream_iterator<double>(cout," "));
  cout<< endl;
}

#include <map>
#include <utility>
#include <string>

void mapExample(){
  typedef map<int,string,greater<int> > MyMap;
  MyMap mmExample;
  //inserting elements
  mmExample.insert(make_pair(1,"aaa"));
  pair<MyMap::iterator,bool> pIfDone = 
    mmExample.insert(make_pair(1,"bbb"));
  if(!pIfDone.second)
    cout << "Insertion did not succeed" << endl;

  mmExample.insert(make_pair(12,"aaa"));
  mmExample.insert(make_pair(3,"bbb"));
  mmExample.insert(MyMap::value_type(23,"ccc"));
  mmExample[10]="c"; //same outcome, but might be slower
  
  //iterating through a map
  MyMap::const_iterator citer = mmExample.begin();
  MyMap::const_iterator eiter = mmExample.end();
  for(; citer != eiter; ++citer)
    cout << "[" << (*citer).first << "]=\"" 
	 << citer->second << "\"" << endl;

  //changing keys: 1 to 100, indirectly!
  MyMap::iterator iter = mmExample.find(1);
  MyMap::mapped_type elem(iter->second);
  mmExample.erase(iter);
  mmExample.insert(make_pair(100,elem));
  //checking if 1 is still in
  iter=mmExample.find(1);
  if(iter==mmExample.end())
    cout << "1 is no longer in the map" << endl;
  //checking if 100 is still in
  iter=mmExample.find(100);
  if(iter != mmExample.end())
    cout << "100 is in the map, with value: \""
	 << iter->second << "\"" << endl;
}

//functor
class add_value_byref
{
public:
  add_value_byref(double dArg) : dValue_(dArg){}
  void operator()(double & dArg){ dArg+=dValue_;}
private: 
  double dValue_;
};

//functor
class add_value_byval : public unary_function<double,double>
{
public:
  add_value_byval(double dArg) : dValue_(dArg){}
  double operator()(double & dArg){return dArg+dValue_;}
private:
  double dValue_;
};


int main()
{
  containerExample();
  /* possible output:
    1.58883 1.14627 -1.69412 0.295142 -0.895352
    1.58883 1.14627 0.295142
  */

  mapExample();
  /* output:
    Insertion did not succeed
    [23]="ccc"
    [12]="aaa"
    [10]="c"
    [3]="bbb"
    [1]="aaa"
    1 is no longer in the map
    100 is in the map, with value: "aaa"
  */

  //in the main
  vector<double> Vec(5,3.0);
  for_each(Vec.begin(),Vec.end(),add_value_byref(2.5));

  //in the main
  vector<double> Vec2(5);
  Vec2[0]=2;
  transform(Vec2.begin(),Vec2.end()-1,Vec2.begin()+1,
	    add_value_byval(2.5));



  // versions with lambda
    {
        vector<double> Vec(5, 3.0);
        vector<double> Vec2(5);
        Vec2[0] = 2;

        for_each(Vec.begin(), Vec.end(), [](double &x) { x += 2.5; });

        transform(Vec2.begin(), Vec2.end() - 1, Vec2.begin() + 1,
                  [](double x) { return x + 2.5; });

        for (const auto &x : Vec) { std::cout << x << ", "; }
        std::cout << std::endl;

        for (const auto &x : Vec2) { std::cout << x << ", "; }
        std::cout << std::endl;

        // a dummy lambda example
        std::vector<double> vec{0.0, 1.0};
        double a(2.1);

        auto fn = [a, &vec](double x) -> bool {
            if (a != x) {
                vec.push_back(x);
                return true;
            } else { return false; }
        };

        std::cout << fn(0.5) << ", " << fn(2.1) << std::endl;

        for (const auto &i : vec) { std::cout << i << ", "; }
        std::cout << std::endl;

    }
  // std::function example
    testAddVector();

  return 0;
}
