#pragma once

#include <ostream>
#include <vector>


template <typename T>
class Matrix;
class Matrix4x4;
class InvalidMatrixSizeException;


// Simple 2D matrix
// T is expected to be a numeric type such as int, float, unsigned int...
template <typename T = float>
class Matrix
{
public:
    Matrix(): m_height(1), m_width(0) {}
    Matrix(size_t height, size_t width, const T& value = 0);
    Matrix(const std::initializer_list<std::initializer_list<T>>& list);

    Matrix& operator=(const Matrix& other) = default;
    Matrix(const Matrix& matrix) = default;
    Matrix(Matrix&& matrix) = default;
    Matrix& operator=(Matrix&& other) = default;

    virtual ~Matrix() = default;

    // apply func for each element (Array[i][j] = func(Array[i][j]))
    Matrix<T>& Apply(T (* func)(T));
    Matrix<T>& Transpose();
    Matrix<T>& Resize(int new_height, int new_width);

    size_t GetHeight() const {return m_height;}
    size_t GetWidth() const {return m_width;}
    std::vector<T> operator[] (size_t index) const {return Array[index];} // read
    std::vector<T>& operator[] (size_t index) {return Array[index];}      // write


    Matrix<T> operator-(T k);
    Matrix<T> operator+(T k);
    Matrix<T> operator/(T k);
    Matrix<T> operator*(T k);

    Matrix<T>& operator+=(T k);
    Matrix<T>& operator-=(T k);
    Matrix<T>& operator*=(T k);
    Matrix<T>& operator/=(T k);

    Matrix<T> operator* (const Matrix<T>& other);
    Matrix<T> operator+(const Matrix<T>& other);
    Matrix<T> operator-(const Matrix<T>& other);
    Matrix<T>& operator+=(const Matrix<T>& other);
    Matrix<T>& operator-=(const Matrix<T>& other);


protected:
    std::vector<std::vector<T>> Array;

    //          Helper functions for operators
    // Array[i][j] = func(m1[i][j], m2[i][j])
    Matrix<T>& apply(const Matrix<T>& m1, const Matrix<T>& m2, T (*func)(T, T));
    // Array[i][j] = func(m[i][j], k)
    Matrix<T>& apply(const Matrix<T>& m, T k, T (*func)(T, T));
    // expects that row.size() = column.size()
    static T dotProduct(const std::vector<T>& row, const std::vector<T>& column);

private:
    size_t m_height;
    size_t m_width;
};


#include "Matrix.tpp"


class Matrix4x4: public Matrix<float>
{
public:
    Matrix4x4(float value = 0): Matrix(4, 4, value) {}
    Matrix4x4(const std::initializer_list<std::initializer_list<float>>& list);
    Matrix4x4(const Matrix<float>& matrix);
    Matrix4x4(Matrix<float>&& matrix);
    virtual ~Matrix4x4() = default;

private:
    using Matrix::Resize;
};


class InvalidMatrixSizeException: public std::exception
{
public:
    InvalidMatrixSizeException(const std::string& info): m_info(info) {};
    InvalidMatrixSizeException(size_t origin_height, size_t origin_width, size_t height, size_t width, const std::string& info);
    const char* what() const noexcept {return m_info.c_str();}

private:
    std::string m_info;
};

