#include <iostream>
#include "Vector.h"
namespace vector {
    Vector::Vector(Number x, Number y) :x(x), y(y) {}
    Number Vector::getR()
    {
        return Number(sqrt((x*x+y*y).getNumber()));
    }
    Number Vector::getFi()
    {
        return x.getNumber() == 0 ? Number(atan((y / x).getNumber())) : acos(-1)/2;
    }
    Vector Vector::operator+(const Vector& secondVector) {
            std::cout << "sum\n";
        return Vector(x + secondVector.x, y + secondVector.y);
    }
}
