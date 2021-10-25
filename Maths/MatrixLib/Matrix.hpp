//
// Created by CASALE Benjamin on 05/04/2021.
//

#ifndef MATRIX_MATRIX_HPP
#define MATRIX_MATRIX_HPP

#include <cmath>

#include "./Vector.hpp"
#include "Exceptions.hpp"
#include <exception>

#define MAXLOOPEIGEN 1000

#define MAXLOOP 1000


namespace LinearAlgebra {


    enum class SOLUTIONS {
        NO_UNIQUE,
        NO_SOL,
        ONE_SOL,
        NO_INVERSE,
        DONE,
        NOT_SQUARE,
        NOT_SYMETRIC,
        ERROR1,
        MAXITERATION,
        NON_DIAG,
    };

    template<class T>

    class Matrix {
    public:

        //Constructors-Destructor
        Matrix(); //1 by 1 matrix, Value = 0
        Matrix(unsigned int Row, unsigned int Col); //Empty Fixed Size
        Matrix(unsigned int Row, unsigned int Col, const T *inputdata);

        explicit Matrix(unsigned int dim); //Identity matrix


        Matrix(const Matrix<T> &Input); //Copy constructor
        Matrix(unsigned int Row, unsigned int Col, const std::vector<T> &Input); //With existing value
        explicit Matrix(const Vector<T> &Input);

        ~Matrix();

        //Methods

        //Getters
        [[nodiscard]] inline unsigned int GetNumRow() const;

        [[nodiscard]] inline unsigned int GetNumcol() const;

        T GetElement(unsigned int Row, unsigned int Col) const;

        //Setters
        void SetElement(unsigned int Row, unsigned int Col, T Value);

        //Modifying Matrix
        void resize(const unsigned int &Row, const unsigned int &Col);

        void Set_To_Identiy();

        SOLUTIONS GaussElimination();

        void Separate(Matrix<T>& Mat1, Matrix<T>& Mat2, const unsigned int &Colnum) const;

        void Join(const Matrix<T> &matrix);

        SOLUTIONS Inverse();

        //Others methods
        [[nodiscard]] constexpr T Determinant() const;

        [[nodiscard]] bool IsEchelon() const;

        [[nodiscard]] constexpr bool compare(const Matrix<T> &mat1, const double &tol) const;

        Matrix<T> Echelon();

        Matrix<T> Transposed();

        unsigned int Rank();

        [[nodiscard]] constexpr bool IsNonZero() const;

        [[nodiscard]] constexpr bool IsSymmetric() const;

        [[nodiscard]] constexpr bool IsDiag() const;

        SOLUTIONS QR_Decomposition(Matrix<T> &Q, Matrix<T> &R)const;

        [[nodiscard]] constexpr inline bool IsSquare() const;

        SOLUTIONS EigenValueQR(std::vector<T> &eigenValues) const;

        SOLUTIONS Diagonalize(Matrix<T>& Diag,Matrix<T>& P) const;


        //Overload
        inline bool operator==(const Matrix<T> &RHS);

        Matrix<T> &operator=(const Matrix<T>& RHS);

        Matrix<T> operator^(unsigned pow);

        template<class U>
         friend Matrix<U> operator+(const Matrix<U> &LHS, const Matrix<U> &RHS);

        template<class U>
         friend Matrix<U> operator+(const U &LHS, const Matrix<U> &RHS);

        template<class U>
         friend Matrix<U> operator+(const Matrix<U> &LHS, const U &RHS);

        template<class U>
         friend Matrix<U> operator-(const Matrix<U> &LHS, const Matrix<U> &RHS);

        template<class U>
         friend Matrix<U> operator-(const U &LHS, const Matrix<U> &RHS);

        template<class U>
        friend Matrix<U> operator-(const Matrix<U> &LHS, const U &RHS);

        template<class U>
        friend Matrix<U> operator*(const Matrix<U> &LHS, const Matrix<U> &RHS);

        template<class U>friend Matrix<U> operator*(const U &LHS, const Matrix<U> &RHS);

        template<class U>friend Matrix<U> operator*(const Matrix<U> &LHS, const U &RHS);

        template<class U>friend Vector<U> operator*(const Matrix<U> &LHS, const Vector<U> &RHS);

        SOLUTIONS EigenVectors(std::vector<Vector<T>>& ListEigenVectors) const;

        SOLUTIONS EigenVectors(const std::vector<double>& eigenValues,std::vector<Vector<T>>& ListEigenVectors) const;

        SOLUTIONS EigenVectorPower(T &eigenValue, Vector<T> &eigenVector)const;


    protected:


        SOLUTIONS EigenVectorInverse(T eigenValue, Vector<T>& EigenVector) const;

        [[nodiscard]] constexpr unsigned int Sub2Ind(const unsigned int &Row, const unsigned int &Col) const;

        //While computing double, the value aren't exact
        // Thus we verify that the difference between two values is small enough to be considerated as null
        constexpr static inline bool CloseEnough(T f1, T f2);

        [[nodiscard]] Matrix<T> FindSubMatrix(unsigned int Row, unsigned int Col) const;

        //Modifying Matrix
        void SwapRow(unsigned int i, unsigned int j);

        inline void MultAdd(unsigned int i, unsigned int j, T factor);

        inline void MultRow(unsigned int i, T factor);

        [[nodiscard]] constexpr unsigned int FindRowWithMax(const unsigned int &Col, const unsigned int &RowStart) const;


        T *m_Matrix_Data;
        unsigned int m_Row, m_Col, m_nElement;
        //unsigned int MaxLoop = 100;

    };


}
#include "MatrixMethods.hpp"
#endif //MATRIX_MATRIX_HPP
