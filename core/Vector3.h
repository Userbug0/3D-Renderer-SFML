#pragma once

#include <ostream>
#include <cmath>

#include "Matrix.h"


class Vector3{
public:
    float x;
    float y;
    float z;

public:
    Vector3();
    Vector3(float X, float Y, float Z);

    Vector3(const Vector3& other)            = default;
    Vector3& operator=(const Vector3& other) = default;
    Vector3(Vector3&& other)                 = default;
    Vector3& operator=(Vector3&& other)      = default;
    ~Vector3()                               = default;

    Vector3(const Matrix<float>& matrix);

public:
    operator Matrix<float>() const {return Matrix<float>{{x, y, z}};}

    Vector3& Normalize();
    Vector3 GetNormalized() const;

    float GetLength() const;
    float GetSqrLength() const;

    Vector3& ApplyMultiplication(const Matrix4x4& matrix);

public:
    static float DotProduct(const Vector3& v1, const Vector3& v2);
    static Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);
    static Vector3 Reflect(const Vector3& ToReflect, const Vector3& v);
    static float Distance(const Vector3& v1, const Vector3& v2);

public:
    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator+=(float k);
    Vector3& operator-=(float k);
    Vector3& operator*=(float k);
    Vector3& operator/=(float k);

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator+(float k) const;
    Vector3 operator-(float k) const;
    Vector3 operator*(float k) const;
    Vector3 operator/(float k) const;

    Vector3 operator-() const;

    bool operator ==(const Vector3& other) const;
    bool operator !=(const Vector3& other) const;

public:
    friend Vector3 operator*(float k, const Vector3& v);
    friend Vector3 operator+(float k, const Vector3& v);
    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};

