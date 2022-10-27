#include "matrix.h"

std::vector<double> threadCalculationResults;
std::vector<double> defaultCalculationResults;

int main()
{
    unsigned int sizeOfMatrix;
    std::cout << "Enter size of matrix:\n";
    std::cin >> sizeOfMatrix;

    std::vector<std::vector<int>> firstMatrix, secondMatrix, result_;
    for (int i = 0; i < sizeOfMatrix; i++)
    {
        firstMatrix.emplace_back();
        secondMatrix.emplace_back();
        result_.emplace_back();
    }
    for (int i = 0; i < sizeOfMatrix; i++)
    {
        for (int j = 0; j < sizeOfMatrix; j++)
        {
            firstMatrix[i].push_back(0);
            secondMatrix[i].push_back(0);
            result_[i].push_back(0);
        }
    }
    Matrix matrix1(firstMatrix), matrix2(secondMatrix);
    Matrix::FillInMatrix(matrix1);
    Matrix::FillInMatrix(matrix2);
    Matrix result(result_);

    Matrix::FindDefaultCalculationTime(matrix1, matrix2, result, sizeOfMatrix);
    Matrix::FindThreadsCalculationTime(matrix1, matrix2, result, sizeOfMatrix);

    for (int i = 0; i < threadCalculationResults.size(); i++)
    {
        std::cout << "Calculation ratio with block size " << i + 1 << " " << defaultCalculationResults[i] / threadCalculationResults[i] << '\n';
    }
    return 0;
}
