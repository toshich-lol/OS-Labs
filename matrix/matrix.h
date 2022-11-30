#ifndef MULTITHREADED_MATRIX_MULTIPLICATION_THREAD_MATRIX_H
#define MULTITHREADED_MATRIX_MULTIPLICATION_THREAD_MATRIX_H

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

extern std::vector<double> threadCalculationResults;
extern std::vector<double> defaultCalculationResults;
extern std::mutex mutex;

class Matrix
{
private:
    std::vector<std::vector<int>> matrix;

    class Timer
    {
    public:
        std::chrono::time_point<std::chrono::steady_clock> start, end;
        std::chrono::duration<float> duration;

        Timer()
        {
            start = std::chrono::high_resolution_clock::now();
        }

        ~Timer() = default;

        float getCurrentMs()
        {
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            float ms = duration.count() * 1000.0f;
            return ms;
        }
    };

public:
    explicit Matrix(std::vector<std::vector<int>> matrix);

    ~Matrix() = default;

    void PrintMatrix();

    static void FillInMatrix(Matrix& matrix);

    int GetAmountOfStrings();

    int GetAmountOfColumns();

    static void FindThreadsCalculationTime(Matrix& matrix1, Matrix& matrix2, Matrix& result, int matrixSize);

    static void FindDefaultCalculationTime(Matrix& matrix1, Matrix& matrix2, Matrix& result, int matrixSize);

    static void MultiplyWithThreads(Matrix& matrix1, Matrix& matrix2, Matrix& result, int matrixSize, int blockSize);

    static void MultipleBlocksOfMatrix(const Matrix& matrix1, const Matrix& matrix2, Matrix& result, int blockI, int blockJ, int matrixSize, int blockSize);

    static void MultiplyWithoutThreads(Matrix& matrix1, Matrix& matrix2, Matrix& result, int matrixSize, int blockSize);
};

#endif //MULTITHREADED_MATRIX_MULTIPLICATION_THREAD_MATRIX_H
