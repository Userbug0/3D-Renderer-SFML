//          CONSTRUCTORS
//////////////////////////////////////////////////////////
template <typename T>
Matrix<T>::Matrix(size_t height, size_t width, const T& value):
    m_height{height}, m_width{width}
{
    for(size_t i = 0; i < m_height; i++){
        Array.push_back({});
        for(size_t j = 0; j < m_width; j++){
            Array[i].push_back(value);
        }
    }
}


template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& list):
    m_height{list.size()}
{
    int i = 0;
    int j = 1;
    int last_width = 0;
    for(auto& nested: list){
        j = 0;
        Array.push_back({});
        for(auto& elem: nested){
            Array[i].push_back(elem);
            j++;
        }
        if(i != 0 && last_width != j)
            throw std::invalid_argument("Invalid Initialization matrix with initializer list");
        last_width = j;
        i++;
    }
    m_width = last_width;
}

//////////////////////////////////////////////////////////



//          PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////

template <typename T>
Matrix<T>& Matrix<T>::Apply(T (*func)(T))
{
    for(size_t i = 0; i < m_height; i++){
        for(size_t j = 0; j < m_width; j++){
            Array[i][j] = func(Array[i][j]);
        }
    }
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::Resize(int new_height, int new_width)
{
    m_height = new_height;
    m_width = new_width;
    Array.resize(m_height);
    for(auto& nested: Array)
        nested.resize(m_width);
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::Transpose()
{
    Matrix<T> newMat(m_width, m_height);
    for(size_t i = 0; i < m_height; i++){
        for(size_t j = 0; j < m_width; j++){
            newMat[j][i] = Array[i][j];
        }
    }
    Resize(m_width, m_height);
    for(size_t i = 0; i < m_height; i++){
        for(size_t j = 0; j < m_width; j++){
            Array[i][j] = newMat[i][j];
        }
    }
    return *this;
}

//////////////////////////////////////////////////////////



//          HELPER FUNCTIONS FOR OPERATORS
//////////////////////////////////////////////////////////

template <typename T>
Matrix<T>& Matrix<T>::apply(const Matrix<T>& m1, const Matrix<T>& m2, T (*func)(T, T))
{
    if(m1.GetHeight() != m_height || m1.GetWidth() != m_width)
        throw InvalidMatrixSizeException(m_height, m_width, m1.GetHeight(), m1.GetWidth(), "Operation Failed");

    if(m2.GetHeight() != m_height || m2.GetWidth() != m_width)
        throw InvalidMatrixSizeException(m_height, m_width, m2.GetHeight(), m2.GetWidth(), "Operation Failed");

    for(size_t i = 0; i < m_height; i++){
        for(size_t j = 0; j < m_width; j++){
            Array[i][j] = func(m1[i][j], m2[i][j]);
        }
    }
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::apply(const Matrix<T>& m, T k, T (*func)(T, T))
{
    if(m.GetHeight() != m_height || m.GetWidth() != m_width)
        throw InvalidMatrixSizeException(m_height, m_width, m.GetHeight(), m.GetWidth(), "Operation Failed");

    for(size_t i = 0; i < m_height; i++){
        for(size_t j = 0; j < m_width; j++){
            Array[i][j] = func(m[i][j], k);
        }
    }
    return *this;
}



template <typename T>
T Matrix<T>::dotProduct(const std::vector<T>& row, const std::vector<T>& column)
{
    T sum = 0;
    for(size_t i = 0; i < row.size(); i++){
        sum += row[i] * column[i];
    }
    return sum;
}
//////////////////////////////////////////////////////////



//               OPERATORS
//////////////////////////////////////////////////////////

template <typename T>
Matrix<T> Matrix<T>::operator/(T k)
{
    Matrix<T> newMat{ m_height, m_width };
    newMat.apply(*this, k, [](T a, T k) -> T {return a / k; });
    return newMat;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(T k)
{
    Matrix<T> newMat{ m_height, m_width };
    newMat.apply(*this, k, [](T a, T k) -> T {return a * k; });
    return newMat;
}


template <typename T>
Matrix<T>& Matrix<T>::operator*=(T k)
{
    return apply(*this, k, [](T a, T k) -> T {return a *= k; });
}


template <typename T>
Matrix<T>& Matrix<T>::operator/=(T k)
{
    return apply(*this, k, [](T a, T k) -> T {return a /= k; });
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
{
    if (other.GetHeight() != m_width)
        throw InvalidMatrixSizeException(m_height, m_width, other.GetHeight(), other.GetWidth(), "Operation multiply matrices Failed");

    size_t new_height = m_height;
    size_t new_width = other.GetWidth();
    Matrix<T> newMat{ new_height, new_width };

    Matrix<T> transposed = other;
    transposed.Transpose();

    for (size_t i = 0; i < new_height; i++) {
        for (size_t j = 0; j < new_width; j++) {
            newMat[i][j] = dotProduct(Array[i], transposed[j]);
        }
    }
    return newMat;
}


template <typename T>
Matrix<T> Matrix<T>::operator+(T k)
{
    Matrix<T> newMat{ m_height, m_width };
    newMat.apply(*this, k, [](T a, T k) -> T {return a + k; });
    return newMat;
}


template <typename T>
Matrix<T>& Matrix<T>::operator+=(T k)
{
    return apply(*this, k, [](T a, T k) -> T {return a += k; });
}


template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other)
{
    Matrix<T> newMat{ m_height, m_width };
    newMat.apply(*this, other, [](T a, T b) -> T {return a + b; });
    return newMat;
}


template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{
    return apply(*this, other, [](T a, T b) -> T {return a + b; });
}


template <typename T>
Matrix<T> Matrix<T>::operator-(T k)
{
    Matrix<T> newMat{ m_height, m_width };
    newMat.apply(*this, k, [](T a, T k) -> T {return a - k; });
    return newMat;
}


template <typename T>
Matrix<T>& Matrix<T>::operator-=(T k)
{
    return apply(*this, k, [](T a, T k) -> T {return a -= k; });
}


template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other)
{
    Matrix<T> newMat{ m_height, m_width };
    newMat.apply(*this, other, [](T a, T k) -> T {return a - k; });
    return newMat;
}


template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
{
    return apply(*this, other, [](T a, T b) -> T {return a - b; });
}


//      This function does not member of class
template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix)
{
    out << "Matrix(";
    size_t width = matrix.GetWidth();
    size_t height = matrix.GetHeight();
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            out << matrix[i][j];
            if (i != height - 1 || j != width - 1)
                out << ", ";
        }
        if (i == height - 1)
            out << ", " << "height = " << height << ", " << "width = " << width << ")\n";
        else
            out << "\n       ";
    }
    out << "\n";
    return out;
}
