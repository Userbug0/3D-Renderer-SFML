#include "Vector4.h"


//          CONSTRUCTORS  
/////////////////////////////////////////////////
Vector4::Vector4()
    : x(0), y(0), z(0), w(0)
{

}


Vector4::Vector4(float X, float Y, float Z, float W)
    : x(X), y(Y), z(Z), w(W)
{

}
   

//          PUBLIC FUNCTIONS
/////////////////////////////////////////////////
Vector4& Vector4::Normalize()
{
    float l = GetLength();
    x /= l, y /= l, z /= l, w /= l;
    return *this;
}


Vector4 Vector4::GetNormalized() const
{
    float l = GetLength();
    return Vector4(x / l, y / l, z / l, w / l);
}


float Vector4::GetLength() const
{
    return std::sqrt(x * x + y * y + z * z + w * w);
}


float Vector4::GetSqrLength() const
{
    return (x * x + y * y + z * z + w * w);
}


//          STATIC FUNCTIONS
/////////////////////////////////////////////////
float Vector4::DotProduct(const Vector4& v1, const Vector4& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}


float Vector4::Distance(const Vector4& v1, const Vector4& v2)
{
    return (v1 - v2).GetLength();
}


//            OPERATORS
/////////////////////////////////////////////////
Vector4& Vector4::operator+=(float k)
{
    x += k; y += k; z += k; w += k;
    return *this;
}


Vector4& Vector4::operator-=(float k)
{
    x -= k; y -= k; z -= k; w -= k;
    return *this;
}


Vector4& Vector4::operator*=(float k)
{
    x *= k; y *= k; z *= k; w *= k;
    return *this;
}


Vector4& Vector4::operator/=(float k)
{
    x /= k; y /= k; z /= k; w /= k;
    return *this;
}


Vector4& Vector4::operator+=(const Vector4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}


Vector4& Vector4::operator-=(const Vector4& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}


Vector4 Vector4::operator+(const Vector4& other) const
{
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}


Vector4 Vector4::operator-(const Vector4& other) const
{
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}


Vector4 Vector4::operator+(float k) const
{
    return Vector4(x + k, y + k, z + k, w + k);
}


Vector4 Vector4::operator-(float k) const
{
    return Vector4(x - k, y - k, z - k, w - k);
}


Vector4 Vector4::operator*(float k) const
{
    return Vector4(x * k, y * k, z * k, w * k);
}


Vector4 Vector4::operator/(float k) const
{
    return Vector4(x / k, y / k, z / k, w / k);
}


Vector4 Vector4::operator-()
{
    return Vector4(-x, -y, -z, -w);
}


bool Vector4::operator ==(const Vector4& other) const
{
    return x == other.x && y == other.y && z == other.z && w == other.w;
}


bool Vector4::operator !=(const Vector4& other) const
{
    return x != other.x || y != other.y || z != other.z || w != other.w;
}


//            FRIEND FUNCTIONS
/////////////////////////////////////////////////
Vector4 operator+(float k, const Vector4& v)
{
    return Vector4(v.x + k, v.y + k, v.z + k, v.w + k);
}


Vector4 operator*(float k, const Vector4& v)
{
    return Vector4(v.x / k, v.y / k, v.z / k, v.w / k);
}


std::ostream& operator<<(std::ostream& os, const Vector4& v)
{
    os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl;
    return os;
}
