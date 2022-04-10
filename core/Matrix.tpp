//          CONSTRUCTORS
//////////////////////////////////////////////////////////
template <typename T>
Matrix<T>::Matrix(size_t height, size_t width, const T& value):
    height_{height}, width_{width}
{
    for(size_t i = 0; i < height_; i++){
        Array.push_back({});
        for(size_t j = 0; j < width_; j++){
            Array[i].push_back(value);
        }
    }
}


template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& list):
    height_{list.size()}
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
    width_ = last_width;
}

//////////////////////////////////////////////////////////



//          PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////

template <typename T>
Matrix<T>& Matrix<T>::apply(T (*func)(T))
{
    for(size_t i = 0; i < height_; i++){
        for(size_t j = 0; j < width_; j++){
            Array[i][j] = func(Array[i][j]);
        }
    }
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::resize(int new_height, int new_width)
{
    height_ = new_height;
    width_ = new_width;
    Array.resize(height_);
    for(auto& nested: Array)
        nested.resize(width_);
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::transpose()
{
    Matrix<T> newMat(width_, height_);
    for(size_t i = 0; i < height_; i++){
        for(size_t j = 0; j < width_; j++){
            newMat[j][i] = Array[i][j];
        }
    }
    resize(width_, height_);
    for(size_t i = 0; i < height_; i++){
        for(size_t j = 0; j < width_; j++){
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
    if(m1.getHeight() != height_ || m1.getWidth() != width_)
        throw InvalidMatrixSizeException(height_, width_, m1.getHeight(), m1.getWidth(), "Operation Failed");

    if(m2.getHeight() != height_ || m2.getWidth() != width_)
        throw InvalidMatrixSizeException(height_, width_, m2.getHeight(), m2.getWidth(), "Operation Failed");

    for(size_t i = 0; i < height_; i++){
        for(size_t j = 0; j < width_; j++){
            Array[i][j] = func(m1[i][j], m2[i][j]);
        }
    }
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::apply(const Matrix<T>& m, T k, T (*func)(T, T))
{
    if(m.getHeight() != height_ || m.getWidth() != width_)
        throw InvalidMatrixSizeException(height_, width_, m.getHeight(), m.getWidth(), "Operation Failed");

    for(size_t i = 0; i < height_; i++){
        for(size_t j = 0; j < width_; j++){
            Array[i][j] = func(m[i][j], k);
        }
    }
    return *this;
}



template <typename T>
T Matrix<T>::DotProduct(const std::vector<T>& row, const std::vector<T>& column)
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
    Matrix<T> newMat{ height_, width_ };
    newMat.apply(*this, k, [](T a, T k) -> T {return a / k; });
    return newMat;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(T k)
{
    Matrix<T> newMat{ height_, width_ };
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
    if (other.getHeight() != width_)
        throw InvalidMatrixSizeException(height_, width_, other.getHeight(), other.getWidth(), "Operation multiply matrices Failed");

    size_t new_height = height_;
    size_t new_width = other.getWidth();
    Matrix<T> newMat{ new_height, new_width };

    Matrix<T> transposed = other;
    transposed.transpose();

    for (size_t i = 0; i < new_height; i++) {
        for (size_t j = 0; j < new_width; j++) {
            newMat[i][j] = DotProduct(Array[i], transposed[j]);
        }
    }
    return newMat;
}


template <typename T>
Matrix<T> Matrix<T>::operator+(T k)
{
    Matrix<T> newMat{ height_, width_ };
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
    Matrix<T> newMat{ height_, width_ };
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
    Matrix<T> newMat{ height_, width_ };
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
    Matrix<T> newMat{ height_, width_ };
    newMat.apply(*this, other, [](T a, T k) -> T {return a - k; });
    return newMat;
}


template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
{
    return apply(*this, other, [](T a, T b) -> T {return a - b; });
}


//      This function Does not memeber of class
template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix)
{
    out << "Matrix(";
    size_t width = matrix.getWidth();
    size_t height = matrix.getHeight();
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
