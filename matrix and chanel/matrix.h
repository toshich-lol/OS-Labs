#ifndef MATRIX_BUFF_CHANNEL_MATRIX_H
#define MATRIX_BUFF_CHANNEL_MATRIX_H

#include "buffered_channel.h"

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
        std::chrono::steady_clock::time_point start, end;
        std::chrono::duration<float> duration;

        Timer()
        {
            start = std::chrono::steady_clock::now();
        }

        ~Timer() = default;

        float getCurrentMs()
        {
            end = std::chrono::steady_clock::now();
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

    static void MultiplyWithThreads(Matrix *matrix1, Matrix *matrix2, Matrix *result, int matrixSize, int blockSize);

    static void MultipleBlocksOfMatrix(const Matrix& matrix1, const Matrix& matrix2, Matrix& result, int blockI, int blockJ, int matrixSize, int blockSize);

    static void MultiplyWithoutThreads(Matrix& matrix1, Matrix& matrix2, Matrix& result, int matrixSize, int blockSize);
};

#endif //MATRIX_BUFF_CHANNEL_MATRIX_H
