#include <string> 

#include "Matrix.hpp"


Matrix4x4::Matrix4x4(const std::initializer_list<std::initializer_list<float>>& list):
    Matrix(list)
{
    if(getHeight() != 4 || getWidth() != 4)
        throw InvalidMatrixSizeException(4, 4, getHeight(), getWidth(), "Invalid initialization of Matrix4x4 with initializer list");
}


Matrix4x4::Matrix4x4(const Matrix<float>& matrix):
    Matrix(matrix)
{
    if(getHeight() != 4 || getWidth() != 4)
        throw InvalidMatrixSizeException(4, 4, getHeight(), getWidth(), "Invalid initialization of Matrix4x4 by copy of Matrix");
}


Matrix4x4::Matrix4x4(Matrix<float>&& matrix):
    Matrix(matrix)
{
    if(getHeight() != 4 || getWidth() != 4)
        throw InvalidMatrixSizeException(4, 4, getHeight(), getWidth(), "Invalid initialization of Matrix4x4 by move of Matrix");
}


InvalidMatrixSizeException::InvalidMatrixSizeException(size_t origin_height, size_t origin_width, \
                                                        size_t height, size_t width, const std::string& info)
{
    info_ = "Invalid Matrix Size Error: " + info;
    info_ += "\n\tOrigin Matrix: height = " + std::to_string(origin_height) + ", width = " + std::to_string(origin_width) + \
             "\n\tGiven Matrix: height = " + std::to_string(height) + ", width = " + std::to_string(width) + "\n";
}
