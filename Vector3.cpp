#include <string> 

#include "Vector3.hpp"


Vector3::Vector3(const Matrix<float>& matrix)
{
    if(matrix.getHeight() != 1 || matrix.getWidth() != 3)
        throw std::invalid_argument("Vector3 cannot be copied by this matrix (height = " + \
                            std::to_string(matrix.getHeight()) + ", width = " + std::to_string(matrix.getWidth()) + ")\n");
    x = matrix[0][0];
    y = matrix[0][1];
    z = matrix[0][2];
}


Vector3 Vector3::Reflect(const Vector3& ToReflect, const Vector3& v)
{
    Vector3 res = ToReflect;
    float m = v.getLength();
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

Vector3 Vector3::getNormalized() const
{
    float l = getLength();
    return Vector3{x / l, y / l, z / l};
}

Vector3& Vector3::normalize()
{
    float l = getLength();
    x /= l, y /= l, z /= l;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
    os << "Vector3(" << v.x << ", " << v.y << ", "  << v.z << ")" << std::endl;
    return os;
}
