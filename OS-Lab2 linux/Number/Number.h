//
// Created by toshich on 22.9.22.
//

#ifndef NUMBER_NUMBER_H
#define NUMBER_NUMBER_H

namespace number {
    class Number {
    public:
        Number(double value = 0);
        Number operator+(const Number& secondValue);
        Number operator-(const Number& secondValue);
        Number operator*(const Number& secondValue);
        Number operator/(const Number& secondValue);
        double getNumber() const;
    private:
        double value;
    };
    Number valueOf(double value);
    const Number ZERO = Number(0);
    const Number ONE = Number(1);
}
#endif //NUMBER_NUMBER_H
