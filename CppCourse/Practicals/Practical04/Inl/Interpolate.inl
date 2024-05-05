
#include <iostream>

namespace exercises {

template<typename PreOp, typename PostOp>
double Interpolate<PreOp,PostOp>::operator()(double dX) const
{

    // check all three cases:
    if (m_xVals.front() > dX) // x < x1
    {
        return m_postOp(m_yVals.front(), dX);
    }
    else if ( dX >= m_xVals.back()) // xn <= X
    {
        return m_postOp(m_yVals.back(), dX);
    }

    // last case, so use STL algorithm
    int i = std::lower_bound(m_xVals.begin(), m_xVals.end(), dX) - m_xVals.begin();

    double z = m_yVals[i-1] + (m_yVals[i] - m_yVals[i-1]) * (dX - m_xVals[i-1])/ (m_xVals[i] - m_xVals[i-1]);

    return m_postOp(z, dX);

}

}
