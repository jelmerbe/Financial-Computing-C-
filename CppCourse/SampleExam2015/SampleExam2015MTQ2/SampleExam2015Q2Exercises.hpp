#ifndef _EXAM2015_Q2_EXERCISES_H__
#define _EXAM2015_Q2_EXERCISES_H__

#include <vector>
#include <string>



namespace exercises
{

static std::string sMyName("1079868");
  typedef std::vector<double> dVector;



  class polynomialInterpolator {
  public:

    /** constructor 
     * @param xVec x-values
     * @param yVec y-values
     */
    polynomialInterpolator(const dVector & xVec, const dVector & yVec);
    
    /** addPoint - adds new point to the interpolator
     * @param x new x-value
     * @param y corresponding y value
     */
    void addPoint(double x, double y);
    
    /** operator() - evaluates polynomial at x
     * @param x x-value the polynomial is to be evaluated at
     */
    double operator()(double x) const;

  private:
    dVector m_x,m_v,m_z;
  };


}

#endif //_EXAM2015_Q2_EXERCISES_H__
