#include "matrix.h"

Matrix::Matrix(std::vector<std::vector<int>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        this->matrix.emplace_back();
    }
    this->matrix = std::move(matrix);
}

void Matrix::PrintMatrix()
{
    for (auto &i: matrix)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            std::cout << i[j] << " ";
        }
        std::cout << '\n';
    }
}

int Matrix::GetAmountOfStrings()
{
    return matrix.size();
}

int Matrix::GetAmountOfColumns()
{
    return matrix[0].size();
}

void
Matrix::MultipleBlocksOfMatrix(const Matrix &matrix1, const Matrix &matrix2, Matrix &result, int blockI, int blockJ,
                               int matrixSize, int blockSize)
{
    for (int i = blockI; i < std::min(blockI + blockSize, matrixSize); i++)
    {
        for (int j = blockJ; j < std::min(blockJ + blockSize, matrixSize); j++)
        {
            for (int k = 0; k < matrixSize; ++k)
            {
                result.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
            }
        }
    }
}

void Matrix::FillInMatrix(Matrix &matrix)
{
    srand((unsigned int) time(0));

    for (int i = 0; i < matrix.GetAmountOfStrings(); i++)
    {
        for (int j = 0; j < matrix.GetAmountOfColumns(); j++)
        {
            matrix.matrix[i][j] = rand() % 10;
        }
    }
}

void Matrix::MultiplyWithoutThreads(Matrix &matrix1, Matrix &matrix2, Matrix &result, int matrixSize,
                                    int blockSize)
{
    for (int blockI = 0; blockI < matrixSize; blockI += blockSize)
    {
        for (int blockJ = 0; blockJ < matrixSize; blockJ += blockSize)
        {
            MultipleBlocksOfMatrix(matrix1, matrix2, result, blockI, blockJ, matrixSize, blockSize);
        }
    }
}

void Matrix::MultiplyWithThreads(Matrix *matrix1, Matrix *matrix2, Matrix *result, int matrixSize, int blockSize)
{
    struct MultData
    {
        Matrix *m1 = nullptr;
        Matrix *m2 = nullptr;
        Matrix *result = nullptr;
        int blockI = 0;
        int blockJ = 0;
        int matrixSize = 0;
        int blockSize = 0;
    };
    BufferedChannel<MultData> channel(matrixSize * matrixSize / blockSize);
    std::vector<std::thread> threads;
    threads.emplace_back([&]()
                         {
                             for (int blockI = 0; blockI < matrixSize; blockI += blockSize)
                             {
                                 for (int blockJ = 0; blockJ < matrixSize; blockJ += blockSize)
                                 {
                                     channel.Send({matrix1, matrix2, result, blockI, blockJ, matrixSize, blockSize});
                                 }
                             }
                             channel.Close();
                         });
    for (int i = 0; i < 10000; ++i)
    {
        threads.emplace_back([&channel]()
                             {
                                 bool open = true;
                                 while (open)
                                 {
                                     auto x = channel.Recv();
                                     open = x.second;
                                     if (open)
                                     {
                                         MultipleBlocksOfMatrix(*(x.first.m1), *(x.first.m2), *(x.first.result),
                                                                x.first.blockI, x.first.blockJ,
                                                                x.first.matrixSize,
                                                                x.first.blockSize);
                                     }
                                 }
                             });
    }
    for (std::thread &tr: threads)
    {
        tr.join();
    }
}

void Matrix::FindThreadsCalculationTime(Matrix &matrix1, Matrix &matrix2, Matrix &result, int matrixSize)
{
    Timer time;

    for (int i = 1; i <= matrixSize; i++)
    {
        MultiplyWithThreads(&matrix1, &matrix2, &result, matrixSize, i);
        threadCalculationResults.push_back(time.getCurrentMs());
    }
}

void Matrix::FindDefaultCalculationTime(Matrix &matrix1, Matrix &matrix2, Matrix &result, int matrixSize)
{
    Timer time;

    for (int i = 1; i <= matrixSize; i++)
    {
        MultiplyWithoutThreads(matrix1, matrix2, result, matrixSize, i);
        defaultCalculationResults.push_back(time.getCurrentMs());
    }
}
