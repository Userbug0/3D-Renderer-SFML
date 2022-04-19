#pragma once

#include <ostream>
#include <cmath>

#include "Vector3.h"


class Vector4 {
public:
    // all dimensions = 0
    Vector4();
    Vector4(float X, float Y, float Z, float W);

    Vector4(const Vector4& other)            = default;
    Vector4& operator=(const Vector4& other) = default;
    Vector4(Vector4&& other)                 = default;
    Vector4& operator=(Vector4&& other)      = default;
    ~Vector4()                               = default;

    explicit Vector4(const Vector3& vec3);

public:
    Vector4& Normalize();
    Vector4 GetNormalized() const;

    float GetLength() const;
    float GetSqrLength() const;

public:
    static float DotProduct(const Vector4& v1, const Vector4& v2);
    static float Distance(const Vector4& v1, const Vector4& v2);

public:
    explicit operator Vector3() const;

    float operator[](size_t index) const;
    float& operator[](size_t index);

    Vector4& operator+=(const Vector4& other);
    Vector4& operator-=(const Vector4& other);
    Vector4& operator+=(float k);
    Vector4& operator-=(float k);
    Vector4& operator*=(float k);
    Vector4& operator/=(float k);

    Vector4 operator+(const Vector4& other) const;
    Vector4 operator-(const Vector4& other) const;
    Vector4 operator+(float k) const;
    Vector4 operator-(float k) const;
    Vector4 operator*(float k) const;
    Vector4 operator/(float k) const;

    Vector4 operator-();

    bool operator ==(const Vector4& v) const;
    bool operator !=(const Vector4& v) const;

public:
    friend Vector4 operator+(float k, const Vector4& v);
    friend Vector4 operator*(float k, const Vector4& v);
    friend std::ostream& operator<<(std::ostream& out, const Vector4& v);

public:
    float x;
    float y;
    float z;
    float w;
};

