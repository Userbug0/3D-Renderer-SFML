
template <typename T>
Matrix<T> Matrix<T>::operator/(const T& k)
{
    Matrix<T> newMat{m_height, m_width};
    newMat.apply(*this, k, [](const T& a, const T& k) -> T {return a / k;});
    return newMat;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const T& k)
{
    Matrix<T> newMat{m_height, m_width};
    newMat.apply(*this, k, [](const T& a, const T& k) -> T {return a * k;});
    return newMat;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
{
    if(other.getHeight() != m_width)
        throw InvalidMatrixSizeException(m_height, m_width, other.getHeight(), other.getWidth(), MatrixErrors::OPERATORS_FAILED);

    size_t new_height = m_height;
    size_t new_width = other.getWidth();
    Matrix<T> newMat{new_height, new_width};

    Matrix<T> transposed = other;
    transposed.transpose();

    for(size_t i = 0; i < new_height; i++){
        for(size_t j = 0; j < new_width; j++){
            newMat[i][j] = DotProduct(Array[i], transposed[j]);
        }
    }
    return newMat;
}


template <typename T>
Matrix<T> Matrix<T>::operator+(const T& k)
{
    Matrix<T> newMat{m_height, m_width};
    newMat.apply(*this, k, [](const T& a, const T& k) -> T {return a + k;});
    return newMat;
}


template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other)
{
    Matrix<T> newMat{m_height, m_width};
    newMat.apply(*this, other, [](const T& a, const T& b) -> T {return a + b;});
    return newMat;
}


template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{
    return apply(*this, other, [](const T& a, const T& b) -> T {return a + b;});
}


template <typename T>
Matrix<T> Matrix<T>::operator-(const T& k)
{
    Matrix<T> newMat{m_height, m_width};
    newMat.apply(*this, k, [](const T& a, const T& k) -> T {return a - k;});
    return newMat;
}


template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other)
{
    Matrix<T> newMat{m_height, m_width};
    newMat.apply(*this, other, [](const T& a, const T& k) -> T {return a - k;});
    return newMat;
}


template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
{
    return apply(*this, other, [](const T& a, const T& b) -> T {return a - b;});
}


//      This function Does not memeber of class
template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix)
{
    out << "Matrix(";
    size_t width = matrix.getWidth();
    size_t height = matrix.getHeight();
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            out << matrix[i][j];
            if(i != height - 1 || j != width - 1)
                out << ", ";
        }
        if(i == height - 1)
            out << ", " << "height = " << height << ", " << "width = " << width << ")\n";
        else
            out << "\n       ";
    }
    out << "\n";
    return out;
}
