#include <iostream>
#include <functional> // for std::less<> and std::greater<>
using namespace std;

int myMax(int a, int b)
{
  return (a<b ? b : a);
}

template<typename T>
T myMax(T a, T b)
{
  return (a<b ? b : a);
}

template<typename T, typename op>
T myComparison(T a, T b){
  return (op()(a,b)? b : a);
}

template<typename T, typename Op=std::less<T> >
class myComparisonFunObj
{
public:
  myComparisonFunObj(Op opArg=Op()) : m_Op(opArg) {}
  T operator()(const T & a, const T & b){
    return (m_Op(a,b)? b : a);
  } 
private:
  Op m_Op;
};

//template class with non-type argument
template<unsigned int n>
class Fibonacci
{
public:
  static const int result =
    Fibonacci<n-1>::result+Fibonacci<n-2>::result;
};
//specialization of Fibonacci<n> for n=0
template<>
class Fibonacci<0>
{
public: 
  static const int result=1;
};
//specialization of Fibonacci<n> for n=1
template<>
class Fibonacci<1>
{
public: 
  static const int result=1;
};
// end of Fibonacci


#if __cplusplus >= 201402L  || (defined(_MSC_VER) && _MSC_VER >= 1916)
// type traits
#include <type_traits>

template<class T,
  class = 
    typename std::enable_if_t<std::is_default_constructible<T>::value> >
void foo(){
  std::cout << "Default constructed instance: " << T() << std::endl;  
}

class DefaultConstructible{};
class NotDefaultConstructible{NotDefaultConstructible() = delete;};

std::ostream & operator<<(std::ostream & os, DefaultConstructible const &){
  return os << "DefaultConstructible instance";
}

std::ostream & operator<<(std::ostream & os, NotDefaultConstructible const &){
  return os << "NotDefaultConstructible instance";
}
#endif

int main()
{

  {
    int a(1), b(2);
    cout << "The max of " << a << " and " << b << " is: " 
	 << myMax(a,b) << endl;

    /*
      The max of 1 and 2 is: 2
    */
  }

  {
    /* May not compile.
    int a(1);
    double c(1.25);
    cout << "The max of " << a << " and " << c << " is: "
	 << myMax(a,c) << endl;
    */
  }

  {
    int a(1);
    double c(1.25);
    cout << "The max of " << a << " and " << c << " is: "
	 << myMax<double>(a,c) << endl;
    cout << "The max of " << a << " and " << c << " is: "
	 << myMax<int>(a,c) << endl;
    /*
      The max of 1 and 1.25 is: 1.25
      The max of 1 and 1.25 is: 1
    */
  }

  {
    int a(1), b(2);
    myComparisonFunObj<int> myMax;
    myComparisonFunObj<int,std::greater<int> > myMin;
    cout << "Using op=less, " << a << " and " << b << " is: "
	 << myMax(a,b) << endl;
    cout << "Using op=greater, " << a << " and " << b << " is: "
	 << myMin(a,b) << endl;
    /*
      Using op=less, 1 and 2 is: 2
      Using op=greater, 1 and 2 is: 1
    */
  }

  {
    //****************************************
    //Fibonacci numbers (e.g. in main):
    int fib10=Fibonacci<10>::result;
    cout << "The 10th Fibonacci number is: " << fib10 << endl;
    /*
      The 10th Fibonacci number is: 89
    */
  }

#if __cplusplus >= 201402L  || (defined(_MSC_VER) && _MSC_VER >= 1916)
  {
    foo<DefaultConstructible>();
    //foo<NotDefaultConstructible>(); // compiler picks up the type constraint
  }
#endif
  return 0;
  
}
