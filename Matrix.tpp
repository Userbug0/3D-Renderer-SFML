
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
    int last_width;
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


template <typename T>
Matrix<T>& Matrix<T>::apply(T (*func)(T))
{
    for(size_t i = 0; i < m_height; i++){
        for(size_t j = 0; j < m_width; j++){
            Array[i][j] = func(Array[i][j]);
        }
    }
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::resize(int new_height, int new_width)
{
    m_height = new_height;
    m_width = new_width;
    Array.resize(m_height);
    for(auto& nested: Array)
        nested.resize(m_width);
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::transpose()
{
    Matrix<T> newMat(m_width, m_height);
    for(size_t i = 0; i < m_height; i++){
        for(size_t j = 0; j < m_width; j++){
            newMat[j][i] = Array[i][j];
        }
    }
    resize(m_width, m_height);
    for(size_t i = 0; i < m_height; i++){
        for(size_t j = 0; j < m_width; j++){
            Array[i][j] = newMat[i][j];
        }
    }
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::apply(const Matrix<T>& m1, const Matrix<T> m2, T (*func)(const T&, const T&))
{
    if(m1.getHeight() != m_height || m1.getWidth() != m_width)
        throw InvalidMatrixSizeException(m_height, m_width, m1.getHeight(), m1.getWidth(), MatrixErrors::OPERATORS_FAILED);

    if(m2.getHeight() != m_height || m2.getWidth() != m_width)
        throw InvalidMatrixSizeException(m_height, m_width, m2.getHeight(), m2.getWidth(), MatrixErrors::OPERATORS_FAILED);

    for(size_t i = 0; i < m_height; i++){
        for(size_t j = 0; j < m_width; j++){
            Array[i][j] = func(m1[i][j], m2[i][j]);
        }
    }
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::apply(const Matrix<T>& m, const T& k, T (*func)(const T&, const T&))
{
    if(m.getHeight() != m_height || m.getWidth() != m_width)
        throw InvalidMatrixSizeException(m_height, m_width, m.getHeight(), m.getWidth(), MatrixErrors::OPERATORS_FAILED);

    for(size_t i = 0; i < m_height; i++){
        for(size_t j = 0; j < m_width; j++){
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

