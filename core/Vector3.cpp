#include <string> 
#include <iostream>

#include "Vector3.h"


Vector3::Vector3(const Matrix<float>& matrix)
{
    if(matrix.GetHeight() != 1 || matrix.GetWidth() != 3)
        throw InvalidMatrixSizeException("Vector3 cannot be copied by this matrix (height = " + \
                            std::to_string(matrix.GetHeight()) + ", width = " + std::to_string(matrix.GetWidth()) + ")\n");
    x = matrix[0][0];
    y = matrix[0][1];
    z = matrix[0][2];
}


Vector3& Vector3::ApplyMultiplication(const Matrix4x4& mat)
{
    Vector3 result;
    float w;

    result.x = mat[0][0] * x + mat[1][0] * y + mat[2][0] * z + mat[3][0];
    result.y = mat[0][1] * x + mat[1][1] * y + mat[2][1] * z + mat[3][1];
    result.z = mat[0][2] * x + mat[1][2] * y + mat[2][2] * z + mat[3][2];
    w        = mat[0][3] * x + mat[1][3] * y + mat[2][3] * z + mat[3][3];

    if(w != 0)
        return *this = result / w;

    return *this = result;
}


Vector3 Vector3::GetNormalized() const
{
    float l = GetLength();
    return Vector3{ x / l, y / l, z / l };
}


Vector3& Vector3::Normalize()
{
    float l = GetLength();
    x /= l, y /= l, z /= l;
    return *this;
}



float Vector3::Distance(const Vector3& v1, const Vector3& v2)
{
    return (v1 - v2).GetLength();
}


Vector3 Vector3::Reflect(const Vector3& ToReflect, const Vector3& v)
{
    Vector3 res = ToReflect;

    float m = v.GetLength();
    float temp = Vector3::DotProduct(res, v) / (m * m);

    res -= 2 * temp * v;
    return res;
}


Vector3 Vector3::CrossProduct(const Vector3& v1, const Vector3& v2)
{
    Vector3 result;
    result.x =  v1.y * v2.z - v1.z * v2.y;
    result.y = - v1.x * v2.z + v1.z * v2.x;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}


Vector3& Vector3::operator+=(float k)
{
    x += k;
    y += k;
    z += k;
    return *this;
}


Vector3& Vector3::operator-=(float k)
{
    x -= k;
    y -= k;
    z -= k;
    return *this;
}


Vector3& Vector3::operator*=(float k)
{
    x *= k;
    y *= k;
    z *= k;
    return *this;
}


Vector3& Vector3::operator/=(float k)
{
    x /= k;
    y /= k;
    z /= k;
    return *this;
}


Vector3& Vector3::operator+=(const Vector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}


Vector3& Vector3::operator-=(const Vector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
    os << "Vector3(" << v.x << ", " << v.y << ", "  << v.z << ")" << std::endl;
    return os;
}
