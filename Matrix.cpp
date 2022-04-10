#include <string> 

#include "Matrix.hpp"


Matrix4x4::Matrix4x4(const std::initializer_list<std::initializer_list<float>>& list):
    Matrix(list)
{
    if(getHeight() != 4 || getWidth() != 4)
        throw InvalidMatrixSizeException(4, 4, getHeight(), getWidth(), MatrixErrors::INIT_FAILED);
}


Matrix4x4::Matrix4x4(const Matrix<float>& matrix):
    Matrix(matrix)
{
    if(getHeight() != 4 || getWidth() != 4)
        throw InvalidMatrixSizeException(4, 4, getHeight(), getWidth(), MatrixErrors::INIT_FAILED);
}


Matrix4x4::Matrix4x4(Matrix<float>&& matrix):
    Matrix(matrix)
{
    if(getHeight() != 4 || getWidth() != 4)
        throw InvalidMatrixSizeException(4, 4, getHeight(), getWidth(), MatrixErrors::INIT_FAILED);
}


InvalidMatrixSizeException::InvalidMatrixSizeException(size_t origin_height, size_t origin_width, \
                                                        size_t height, size_t width, MatrixErrors p)
{
    // constructors
    if(p == MatrixErrors::INIT_FAILED)
        m_info = "Matrix Initialization failed: \n";
    // operators
    else if(p == MatrixErrors::OPERATORS_FAILED)
        m_info = "Matrix operations failed: \n";
    else if(p == MatrixErrors::FUNCTIONS_FAILED)
        m_info = "Matrix functions failed: \n";

    m_info += "Origin Matrix: height = " + std::to_string(origin_height) + ", width = " + std::to_string(origin_width) + \
             "\nGiven Matrix: height = " + std::to_string(height) + ", width = " + std::to_string(width) + "\n";
}
