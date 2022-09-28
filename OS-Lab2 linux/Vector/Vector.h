//
// Created by toshich on 22.9.22.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H


#include<Number.h>
#include<cmath>
using namespace number;

namespace vector {
    class Vector {
            public:
            Vector(Number x, Number y);
            Number getR();
            Number getFi();
            Vector operator+ (const Vector& secondVector);
            private:
            Number x;
            Number y;
    };

    const Vector ZERO = Vector(0, 0);
    const Vector ONE = Vector(1, 1);
}


#endif //VECTOR_VECTOR_H
