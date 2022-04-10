#pragma once

#include <ostream>
#include <cmath>

#include "Matrix.h"


struct Vector3{
    float x;
    float y;
    float z;

    Vector3(): x{0}, y{0}, z{0} {}
    Vector3(float X, float Y, float Z): x{X}, y{Y}, z{Z} {}

    Vector3(const Vector3& other) = default;
    Vector3& operator=(const Vector3& other) = default;
    Vector3(const Matrix<float>& matrix);

    Vector3(Vector3&& other) = default;
    Vector3& operator=(Vector3&& other) = default;

    ~Vector3() = default;

    operator Matrix<float>() const {return Matrix<float>{{x, y, z}};}

    Vector3& normalize();
    float getLength() const {return std::sqrt(x * x + y * y + z * z);}
    Vector3 getNormalized() const;

    friend Vector3 operator-(const Vector3& v){return Vector3{-v.x, -v.y, -v.z};}

    Vector3& operator*=(float k);
    Vector3& operator/=(float k);
    friend Vector3 operator*(float k, const Vector3& v){return Vector3{v.x * k, v.y * k, v.z * k};}
    friend Vector3 operator*(const Vector3& v, float k){return Vector3{v.x * k, v.y * k, v.z * k};}
    friend Vector3 operator/(const Vector3& v, float k) {return Vector3{v.x / k, v.y / k, v.z / k};}

    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    friend Vector3 operator+(const Vector3& v1, const Vector3& v2){return Vector3{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};}
    friend Vector3 operator-(const Vector3& v1, const Vector3& v2){return Vector3{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};}

    friend bool operator ==(const Vector3& v1, const Vector3& v2) {return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);}
    friend bool operator !=(const Vector3& v1, const Vector3& v2) { return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z == v2.z); }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);

    static float DotProduct(const Vector3& v1, const Vector3& v2) {return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;}
    static Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);
    static Vector3 Reflect(const Vector3& ToReflect, const Vector3& v);
    static float Distance(const Vector3& v1, const Vector3& v2);
};

