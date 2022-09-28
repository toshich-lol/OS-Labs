#include <Number.h>
#include <Vector.h>
#include <iostream>
int main() {
    Number s(2);
    vector::Vector a(3, 4);
    vector::Vector b(4, 5);
    vector::Vector c = a + b;
    return 0;
}
