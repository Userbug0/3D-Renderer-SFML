#pragma once

#include <array>

#include "Vector4.h"
#include "Vector3.h"


class Matrix4
{
public:
    Matrix4() = default;
    Matrix4(float value);
    Matrix4(const std::initializer_list<Vector4>& list);

    Matrix4(const Matrix4& matrix)           = default;
    Matrix4& operator=(const Matrix4& other) = default;
    Matrix4(Matrix4&& matrix)                = default;
    Matrix4& operator=(Matrix4&& other)      = default;
    ~Matrix4()                               = default;

public:
    // Applies for each element: matrix[i][j] = func(matrix[i][j])
    Matrix4& Apply(float (*func)(float));
    Matrix4& Transpose();

    // Only for Rotation/Translation Matrices
    Matrix4& QuickInverse();

    Vector4 GetColumn(size_t index) const;

    inline auto begin()       { return m_array.begin(); }
    inline auto begin() const { return m_array.begin(); }

    inline auto end()         { return m_array.end(); }
    inline auto end()   const { return m_array.end(); }

public:
    static void ApplyMultiplication(Vector4& vec, const Matrix4& mat);
    static void ApplyMultiplication(Vector3& vec, const Matrix4& mat);

public:
    inline const Vector4& operator[] (size_t index) const { return m_array[index]; }
    inline Vector4& operator[]       (size_t index)       { return m_array[index]; }

    Matrix4& operator+=(const Matrix4& other);
    Matrix4& operator-=(const Matrix4& other);
    Matrix4& operator+=(float k);
    Matrix4& operator-=(float k);
    Matrix4& operator*=(float k);
    Matrix4& operator/=(float k);
    
    Matrix4 operator+(const Matrix4& other) const;
    Matrix4 operator-(const Matrix4& other) const;
    Matrix4 operator-(float k) const;
    Matrix4 operator+(float k) const;
    Matrix4 operator/(float k) const;
    Matrix4 operator*(float k) const;

    Matrix4 operator*(const Matrix4& other) const;

public:
    friend Matrix4 operator+(float k, const Matrix4& mat);
    friend Matrix4 operator*(float k, const Matrix4& mat);
    friend std::ostream& operator<<(std::ostream& out, const Matrix4& mat);

private:
    std::array<Vector4, 4> m_array;
};

