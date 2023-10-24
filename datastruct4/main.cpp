#include<iostream>

using namespace std;

template<typename DataType>
class Matrix {
private:
    int row;
    int column;
    DataType *array;
public:
    Matrix();

    Matrix(int row, int column);

    Matrix(int row, int column, DataType a[]);

    ~Matrix();

    void printMatrix();

    friend ostream &operator<<(ostream &os, const Matrix<DataType> &matrix);

    Matrix<DataType> operator*(const Matrix<DataType> &a);  // Modified function declaration

    DataType operator()(int row, int column) const;

    int getRow() const;

    int getColumn() const;
};

template<typename DataType>
DataType Matrix<DataType>::operator()(int row, int column) const {
    return array[row * this->column + column];
}


template<typename DataType>
Matrix<DataType>::Matrix() {
    row = 0;
    column = 0;
    array = nullptr;
}

template<typename DataType>
Matrix<DataType>::Matrix(int row, int column) {
    this->row = row;
    this->column = column;
    array = new DataType[row * column];
}

template<typename DataType>
Matrix<DataType>::Matrix(int row, int column, DataType a[]) {
    this->row = row;
    this->column = column;
    array = new DataType[row * column];
    for (int i = 0; i < row * column; i++) {
        array[i] = a[i];
    }
}

template<typename DataType>
Matrix<DataType>::~Matrix() {
    delete[] array;
}

template<typename DataType>
ostream &operator<<(ostream &os, const Matrix<DataType> &matrix) {
    for (int i = 0; i < matrix.row; i++) {
        for (int j = 0; j < matrix.column; j++) {
            os << matrix.array[i * matrix.column + j] << "\t";
        }
        os << endl;
    }
    return os;
}


template<typename DataType>
void Matrix<DataType>::printMatrix() {
    int i, j;
    cout << "row: " << row << "\t" << "column: " << column << endl;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            cout << array[i * column + j] << "\t";
        }
        cout << endl;
    }
}

template<typename DataType>
Matrix<DataType> Matrix<DataType>::operator*(const Matrix<DataType> &a) {
    // Create a matrix to store the result
    Matrix<DataType> result(row, a.column);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < a.column; j++) {
            // Initialize each element to 0
            result.array[i * result.column + j] = 0;
            for (int k = 0; k < column; k++) {
                result.array[i * result.column + j] += array[i * column + k] * a.array[k * a.column + j];
            }
        }
    }
    return result;
}

template<typename DataType>
int Matrix<DataType>::getRow() const {
    return row;
}

template<typename DataType>
int Matrix<DataType>::getColumn() const {
    return column;
}

// Function to compare two matrices
template<typename DataType>
bool compareMatrices(const Matrix<DataType>& matrix1, const Matrix<DataType>& matrix2) {
    if (matrix1.getRow() != matrix2.getRow() || matrix1.getColumn() != matrix2.getColumn())
        return false;

    for (int i = 0; i < matrix1.getRow(); i++) {
        for (int j = 0; j < matrix1.getColumn(); j++) {
            if (abs(matrix1(i, j) - matrix2(i, j))>0.0000001)
                return false;
        }
    }

    return true;
}

// Test case for matrix multiplication
void testMatrixMultiplication() {
    float a[] = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    Matrix<float> ma(2, 4, a);
    Matrix<float> mb(4, 2, a);
    Matrix<float> expected(2, 2, new float[4]{60.0, 70.0, 132.0, 158.0});

    Matrix<float> result = ma * mb;

    std::cout << "-----a.matrix-----" << std::endl;
    ma.printMatrix();
    std::cout << "-----b.matrix-----" << std::endl;
    mb.printMatrix();
    std::cout << "-----expected-----" << std::endl;
    expected.printMatrix();
    std::cout << "-----result-------" << std::endl;
    result.printMatrix();

    if (compareMatrices(result, expected)) {
        std::cout << "Matrix multiplication test passed." << std::endl;
    } else {
        std::cout << "Matrix multiplication test failed." << std::endl;
    }
}

int main() {
    testMatrixMultiplication();
    return 0;
    float a[] = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    Matrix<float> ma(2, 4, a);
    Matrix<float> mb(4, 2, a);
    Matrix<float> mc;

    cout << "-------------------" << endl;
    mc = ma * mb;  // Perform matrix multiplication
    cout << "-----b.matrix-------" << endl;
    mb.printMatrix();
    cout << "-----a.matrix-------" << endl;
    ma.printMatrix();
    cout << "-----c.matrix-------" << endl;
    mc.printMatrix();
    cout << "---end---" << endl;
    return 0;
}
