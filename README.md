# CPP_Matrix
Implementation of the matrix_oop.h library in C++ programming language using the object-oriented approach

## Description

This project is an extension of my [C_Matrix](https://github.com/igorgrichanov/C_matrix) project

## Important notes

- The library has been developed in C++ language of C++17 standard using gcc compiler;
- Library code follows the Google style;
- Full coverage of library functions code has been prepared with unit-tests using the GTest library;

## Matrix operations

Below is a brief description of the matrix operations that has been implemented in the development library

| Operation | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const S21Matrix& other)` | Checks matrices for equality with each other. |  |
| `void SumMatrix(const S21Matrix& other)` | Adds the second matrix to the current one | different matrix dimensions. |
| `void SubMatrix(const S21Matrix& other)` | Subtracts another matrix from the current one | different matrix dimensions. |
| `void MulNumber(const double num) ` | Multiplies the current matrix by a number. |  |
| `void MulMatrix(const S21Matrix& other)` | Multiplies the current matrix by the second matrix. | The number of columns of the first matrix is not equal to the number of rows of the second matrix. |
| `S21Matrix Transpose()` | Creates a new transposed matrix from the current one and returns it. |  |
| `S21Matrix CalcComplements()` | Calculates the algebraic addition matrix of the current one and returns it. | The matrix is not square. |
| `double Determinant()` | Calculates and returns the determinant of the current matrix. | The matrix is not square. |
| `S21Matrix InverseMatrix()` | Calculates and returns the inverse matrix. | Matrix determinant is 0. |

Apart from those operations, these constructors and destructors are implemented:

| Method | Description |
| ----------- | ----------- |
| `S21Matrix()` | A basic constructor that initialises a matrix of some predefined dimension. |  
| `S21Matrix(int rows, int cols) ` | Parametrized constructor with number of rows and columns. |
| `S21Matrix(const S21Matrix& other)` | Copy constructor. |
| `S21Matrix(S21Matrix&& other)` | Move constructor. |
| `~S21Matrix()` | Destructor. |

The following operators are overloaded, partly corresponding to the operations above:

| Operator | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `+`      | Addition of two matrices. | Different matrix dimensions. |
| `-`   | Subtraction of one matrix from another. | Different matrix dimensions. |
| `*`  | Matrix multiplication and matrix multiplication by a number. | The number of columns of the first matrix does not equal the number of rows of the second matrix. |
| `==`  | Checks for matrices equality (`EqMatrix`). | |
| `=`  | Assignment of values from one matrix to another one. | |
| `+=`  | Addition assignment (`SumMatrix`) | different matrix dimensions. |
| `-=`  | Difference assignment (`SubMatrix`) | different matrix dimensions. |
| `*=`  | Multiplication assignment (`MulMatrix`/`MulNumber`). | The number of columns of the first matrix does not equal the number of rows of the second matrix. |
| `(int i, int j)`  | Indexation by matrix elements (row, column). | Index is outside the matrix. |

