#include <iostream>
#include <vector>
#include <mutex>
#include <ctime>
#include <chrono>
#include <windows.h>


struct Parameters{
    int**a;
    int** b;
    int** result;
    int i, k, j, block_size;
    Parameters(int** a, int** b, int**result, int i, int k, int j, int block_size) : a(a), b(b), result(result){
        this->i = i;
        this->j = j;
        this->k = k;
        this->block_size = block_size;
    }
};


void ZeroTheMatrix(int**& matrix, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = 0;
        }
    }
}

void FillMatrices(int**& a, int**& b, int**& result, int n){
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        a[i] = new int[n];
        b[i] = new int[n];
        result[i] = new int[n];
    }
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            a[i][j] = rand() % 15;
            b[i][j] = rand() % 15;
            result[i][j] = 0;
        }
    }
}

void PrintMatrix(int**& matrix, int& n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void MultiplyTheRest(int** a, int** b, int**& result, int start, int n){
    for (int i = 0; i < n; i++) {
        for (int j = start; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for(int j = 0; j < n; j++){
        for(int i = start; i < n; i++){
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int l = start; l < n; l++){
                result[i][j] += a[i][l] * b[l][j];
            }
        }
    }
}
void MultiplyMatrices(int**& a, int**& b, int**& result, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = new int[n];
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void MultiplyBlocks(int** a, int** b, int**& result, int i_, int k_, int j_, int size) {
    for (int i = i_; i < i_ + size; i++) {
        for (int j = j_; j < j_ + size; j++) {
            int current = 0;
            for (int k = 0; k < size; k++) {
                current += a[i][k_ + k] * b[k_ + k][j];
            }
            result[i][j] += current;
        }
    }
}
void MultiplyByBlocks(int**& a, int**& b, int**& result, int& n, int& block_size){
    int rest = n - (n % block_size);
    if (n % block_size != 0){
        MultiplyTheRest(a,b, std::ref(result), rest, n);

    }
    std::vector<HANDLE> threads;
    for (int i = 0; i < rest; i += block_size){
        for (int j = 0; j < rest; j += block_size) {
            for (int k = 0; k < rest; k += block_size) {
                Parameters params(a, b, result, i, k, j, block_size);
                threads.emplace_back(CreateThread(nullptr,0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&MultiplyBlocks), &params, 0,
                                                  nullptr));
            }
        }
    }
    auto* thrArr = new HANDLE[threads.size()];
    for(int i = 0; i < threads.size(); i++){
        thrArr[i] = threads[i];
    }
    WaitForMultipleObjects((DWORD)block_size, thrArr, TRUE, INFINITE);
}

int main() {
    int n;
    std::cout << "Enter the size of matrices:";
    std::cin >> n;
    int** a = new int*[n];
    int** b = new int*[n];
    int** result = new int*[n];
    FillMatrices(a, b, result, n);
    auto begin = std::chrono::steady_clock::now();
    MultiplyMatrices(a, b,  result, n);
    auto end = std::chrono::steady_clock::now();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    std::cout << "simple multiplication takes: "<< nanoseconds.count() << " nanoseconds" << std::endl;
    std::cout << std::endl;

    for(int i = 1; i <= n; i++){
        ZeroTheMatrix(result, n);
        begin = std::chrono::steady_clock::now();
        MultiplyByBlocks(a,b,result,n,i);
        end = std::chrono::steady_clock::now();
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        if (n % i != 0){
            std::cout << i  << ", it takes " << nanoseconds.count() << " nanoseconds\n";
            std::cout << std::endl;
        }else {
            std::cout << i << ", it takes " << nanoseconds.count() << " nanoseconds\n";
            std::cout << std::endl;
        }
    }
    return 0;
}
