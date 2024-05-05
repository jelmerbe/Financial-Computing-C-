#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

typedef std::function<double(double, double)> BinaryFunction;
typedef std::vector<double> Vector;

double addFunction(double a, double b) {
    return a + b;
}

class MultiplyFunctionObject {
public:
    double operator()(double a, double b) {
        return a * b;
    }
};

auto divideLambda = [](double a, double b){ return a / b; };

double binaryOpOnScalars(double a, double b, BinaryFunction fn) {
    return fn(a, b);
}

void binaryOpOnVectors(const Vector & a, const Vector & b, Vector & c,
               const BinaryFunction & fn) {
    std::transform(a.cbegin(), a.cend(), b.cbegin(), std::back_inserter(c), fn);
}

void testAddVector() {
    Vector a{1.0, 2.0}, b{10.0, 20.0, 30.0 }, c;

    BinaryFunction fn1 = addFunction;
    binaryOpOnVectors(a, b, c, fn1);
    std::copy(c.begin(),c.end(),
            std::ostream_iterator<double>(std::cout," "));
    std::cout << std::endl;

    binaryOpOnVectors(a, b, c, MultiplyFunctionObject());
    std::copy(c.begin(),c.end(),
            std::ostream_iterator<double>(std::cout," "));
    std::cout << std::endl;

    binaryOpOnVectors(a, b, c, divideLambda);
    std::copy(c.begin(),c.end(),
            std::ostream_iterator<double>(std::cout," "));
    std::cout << std::endl;
}