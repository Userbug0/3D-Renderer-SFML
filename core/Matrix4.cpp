#include "Matrix4.h"


//          CONSTRUCTORS  
/////////////////////////////////////////////////
Matrix4::Matrix4(float value)
{
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            m_array[i][j] = value;
        }
    }
}


Matrix4::Matrix4(const std::initializer_list<Vector4>& list)
{
    if(list.size() != 4)
        throw std::invalid_argument("Invalid initialization Matrix4 with initializer list");

    size_t i = 0;
    for (auto& vec : list)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            m_array[i][j] = vec[j];
        }
        ++i;
    }
}


//          PUBLIC FUNCTIONS
/////////////////////////////////////////////////
Matrix4& Matrix4::Apply(float (*func)(float))
{
    for (auto& vec : m_array)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            vec[i] = func(vec[i]);
        }
    }
    return *this;
}


Matrix4& Matrix4::Transpose()
{
    auto tmp = m_array;
    for (size_t i = 0; i < 4; i++) 
    {
        for (size_t j = 0; j < 4; j++) 
        {
            m_array[j][i] = tmp[i][j];
        }
    }
    return *this;
}


Vector4 Matrix4::GetColumn(size_t index) const
{
    Vector4 res;
    for (size_t i = 0; i < 4; ++i)
        res[i] = m_array[i][index];
    return res;
}


//          STATIC FUNCTIONS
/////////////////////////////////////////////////
void Matrix4::ApplyMultiplication(Vector4& vec, const Matrix4& mat)
{
    Vector4 tmp = vec;

    for (size_t i = 0; i < 4; ++i)
        vec[i] = mat[0][i] * tmp[0] + mat[1][i] * tmp[1] + mat[2][i] * tmp[2] + mat[3][i] * tmp[3];
}


void Matrix4::ApplyMultiplication(Vector3& vec, const Matrix4& mat)
{
    Vector3 tmp = vec;
    float w;

    vec.x = mat[0][0] * tmp.x + mat[1][0] * tmp.y + mat[2][0] * tmp.z + mat[3][0];
    vec.y = mat[0][1] * tmp.x + mat[1][1] * tmp.y + mat[2][1] * tmp.z + mat[3][1];
    vec.z = mat[0][2] * tmp.x + mat[1][2] * tmp.y + mat[2][2] * tmp.z + mat[3][2];
    w = mat[0][3] * tmp.x + mat[1][3] * tmp.y + mat[2][3] * tmp.z + mat[3][3];

    if (w != 0)
        vec /= w;
}


//          OPERATORS
/////////////////////////////////////////////////
Matrix4& Matrix4::operator+=(const Matrix4& other)
{
    for (size_t i = 0; i < 4; ++i)
        m_array[i] += other[i];

    return *this;
}


Matrix4& Matrix4::operator-=(const Matrix4& other)
{
    for (size_t i = 0; i < 4; ++i)
        m_array[i] -= other[i];

    return *this;
}


Matrix4& Matrix4::operator+=(float k)
{
    for (size_t i = 0; i < 4; ++i)
        m_array[i] += k;

    return *this;
}


Matrix4& Matrix4::operator-=(float k)
{
    for (size_t i = 0; i < 4; ++i)
        m_array[i] -= k;

    return *this;
}


Matrix4& Matrix4::operator*=(float k)
{
    for (size_t i = 0; i < 4; ++i)
        m_array[i] *= k;

    return *this;
}


Matrix4& Matrix4::operator/=(float k)
{
    for (size_t i = 0; i < 4; ++i)
        m_array[i] /= k;

    return *this;
}


Matrix4 Matrix4::operator+(const Matrix4& other) const
{
    Matrix4 mat = *this;
    mat += other;
    return mat;
}


Matrix4 Matrix4::operator-(const Matrix4& other) const
{
    Matrix4 mat = *this;
    mat -= other;
    return mat;
}


Matrix4 Matrix4::operator-(float k) const
{
    Matrix4 mat = *this;
    mat -= k;
    return mat;
}


Matrix4 Matrix4::operator+(float k) const
{
    Matrix4 mat = *this;
    mat += k;
    return mat;
}


Matrix4 Matrix4::operator/(float k) const
{
    Matrix4 mat = *this;
    mat /= k;
    return mat;
}


Matrix4 Matrix4::operator*(float k) const
{
    Matrix4 mat = *this;
    mat *= k;
    return mat;
}


Matrix4 Matrix4::operator*(const Matrix4& other) const
{
    Matrix4 mat;

    Matrix4 transposed = other;
    transposed.Transpose();

    for (size_t i = 0; i < 4; i++) 
    {
        for (size_t j = 0; j < 4; j++) 
        {
            mat[i][j] = Vector4::DotProduct(m_array[i], transposed[j]);
        }
    }

    return mat;
}


//          FRIEND FUNCTIONS
/////////////////////////////////////////////////
Matrix4 operator+(float k, const Matrix4& mat)
{
    Matrix4 res = mat;
    res += k;
    return res;
}


Matrix4 operator*(float k, const Matrix4& mat)
{
    Matrix4 res = mat;
    res *= k;
    return res;
}


std::ostream& operator<<(std::ostream& out, const Matrix4& mat)
{
    out << "Matrix4(";
    for (size_t i = 0; i < 4; i++) 
    {
        for (size_t j = 0; j < 4; j++) 
        {
            out << mat[i][j];
            if (i != 4 - 1 || j != 4 - 1)
                out << ", ";
        }
        if (i == 3)
            out << ", " << "height = " << 4 << ", " << "width = " << 4 << ")\n";
        else
            out << "\n       ";
    }
    out << "\n";
    return out;
}

