#include "Number.h"
namespace number {
    Number::Number(double value) :value(value) {}
    Number Number::operator+(const Number& secondValue) {
        return value + secondValue.value;
    }
    Number Number::operator-(const Number& secondValue) {
        return value - secondValue.value;
    }
    Number Number::operator*(const Number& secondValue) {
        return value * secondValue.value;
    }
    Number Number::operator/(const Number& secondValue) {
        return value / secondValue.value;
    }
    double Number::getNumber() const {
        return value;
    }
    Number valueOf(double value) {
        return Number(value);
    }
}