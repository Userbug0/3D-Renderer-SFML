#include <string> 

#include "Vector3.h"


//          CONSTRUCTORS  
/////////////////////////////////////////////////
Vector3::Vector3()
    : x(0), y(0), z(0)
{

}


Vector3::Vector3(float X, float Y, float Z)
    : x(X), y(Y), z(Z)
{

}


//          PUBLIC FUNCTIONS  
/////////////////////////////////////////////////
Vector3& Vector3::Normalize()
{
    float l = GetLength();
    x /= l, y /= l, z /= l;
    return *this;
}


Vector3 Vector3::GetNormalized() const
{
    float l = GetLength();
    return Vector3{ x / l, y / l, z / l };
}


float Vector3::GetLength() const
{
    return std::sqrt(x * x + y * y + z * z);
}


float Vector3::GetSqrLength() const
{
    return x * x + y * y + z * z;
}


//          STATIC FUNCTIONS  
/////////////////////////////////////////////////
float Vector3::DotProduct(const Vector3& v1, const Vector3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


Vector3 Vector3::CrossProduct(const Vector3& v1, const Vector3& v2)
{
    Vector3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = -v1.x * v2.z + v1.z * v2.x;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}



Vector3 Vector3::Reflect(const Vector3& ToReflect, const Vector3& v)
{
    Vector3 res = ToReflect;

    float m = v.GetLength();
    float temp = Vector3::DotProduct(res, v) / (m * m);

    res -= 2 * temp * v;
    return res;
}


float Vector3::Distance(const Vector3& v1, const Vector3& v2)
{
    return (v1 - v2).GetLength();
}


//            OPERATORS
/////////////////////////////////////////////////
float Vector3::operator[](size_t index) const
{
    if (index == 0)
        return x;
    if (index == 1)
        return y;
    if (index == 2)
        return z;

    throw std::out_of_range("Vector3: Failed to get element by index: " + std::to_string(index) + "\n");
}


float& Vector3::operator[](size_t index)
{
    if (index == 0)
        return x;
    if (index == 1)
        return y;
    if (index == 2)
        return z;

    throw std::out_of_range("Vector3: Failed to get element by index: " + std::to_string(index) + "\n");
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


Vector3& Vector3::operator+=(float k)
{
    x += k; y += k; z += k;
    return *this;
}


Vector3& Vector3::operator-=(float k)
{
    x -= k; y -= k; z -= k;
    return *this;
}


Vector3& Vector3::operator*=(float k)
{
    x *= k; y *= k; z *= k;
    return *this;
}


Vector3& Vector3::operator/=(float k)
{
    x /= k; y /= k; z /= k;
    return *this;
}


Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}


Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}


Vector3 Vector3::operator+(float k) const
{
    return Vector3(x + k, y + k, z + k);
}


Vector3 Vector3::operator-(float k) const
{
    return Vector3(x - k, y - k, z - k);
}


Vector3 Vector3::operator*(float k) const
{
    return Vector3(x * k, y * k, z * k);
}


Vector3 Vector3::operator/(float k) const
{
    return Vector3(x / k, y / k, z / k);
}


Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}


bool Vector3::operator==(const Vector3& other) const
{
    return x == other.x && y == other.y && z == other.z;
}


bool Vector3::operator !=(const Vector3& other) const
{
    return x != other.x || y != other.y || z != other.z;
}



//            FRIEND FUNCTIONS
/////////////////////////////////////////////////
Vector3 operator+(float k, const Vector3& v)
{
    return Vector3(v.x + k, v.y + k, v.z + k);
}


Vector3 operator*(float k, const Vector3& v)
{
    return Vector3(v.x * k, v.y * k, v.z * k);
}


std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
    out << "Vector3(" << v.x << ", " << v.y << ", "  << v.z << ")" << std::endl;
    return out;
}
