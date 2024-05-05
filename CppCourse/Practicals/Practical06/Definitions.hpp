#ifndef _DEFINITIONS_H__
#define _DEFINITIONS_H__

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#if __cplusplus > 199711L
  #include <memory>
  namespace ptrnamespace = std;
#else
  #include <boost/shared_ptr.hpp>
  namespace ptrnamespace = boost;
#endif

namespace exercises
{

  class IFunction; //forward declaration of IFunction
  class Function;  //forward declaration of Function

  typedef ptrnamespace::shared_ptr<const IFunction> IFunPtr; //smart pointer to IFunction
  typedef boost::numeric::ublas::vector<double> BVector; //boost vector of doubles

}




#endif //_DEFINITIONS_H__
