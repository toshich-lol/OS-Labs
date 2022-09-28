g++ -c -o Number/Number.o Number/Number.cpp
ar r Number/libNumber.a Number/Number.o 
g++ -c -o Vector/Vector.o Vector/Vector.cpp -INumber -LNumber -lNumber -fPIC
g++ -shared -o Vector/libVector.so Vector/Vector.o -fPIC
g++ -o Test test/main.cpp -INumber -IVector Number/libNumber.a Vector/libVector.so
./Test
