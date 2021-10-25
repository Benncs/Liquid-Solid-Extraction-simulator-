//
// Created by CASALE Benjamin on 06/04/2021.
//

#ifndef MATRIX_MATRIXMETHODS_HPP
#define MATRIX_MATRIXMETHODS_HPP


#include "Matrix.hpp"

namespace LinearAlgebra {
    template<class T>
    Matrix<T>::Matrix() {
        m_Row = 1;
        m_Col = 1;
        m_nElement = 1;
        m_Matrix_Data = new T[m_nElement];
        m_Matrix_Data[0] = 0.0;
    }

    template<class T>
    Matrix<T>::Matrix(unsigned int Row, unsigned int Col) {
        m_Row = Row;
        m_Col = Col;
        m_nElement = m_Row * m_Col;
        m_Matrix_Data = new T[m_nElement];
        for (unsigned i = 0; i < m_nElement; i++) { m_Matrix_Data[i] = 0.0; }

    }

    template<class T>
    Matrix<T>::Matrix(unsigned int Row, unsigned int Col, const T *inputdata) {
        m_Row = Row;
        m_Col = Col;
        m_nElement = m_Row * m_Col;
        m_Matrix_Data = new T[m_nElement];
        for (unsigned i = 0; i < m_nElement; i++) {
            m_Matrix_Data[i] = inputdata[i];
        }
    }

    template<class T>
    Matrix<T>::~Matrix() {
//        if (m_Matrix_Data) delete m_Matrix_Data;
//        m_Matrix_Data = nullptr;
        delete m_Matrix_Data;
    }

    template<class T>
    void Matrix<T>::resize(const unsigned int &Row, const unsigned int &Col) {

        /*Actually is only delete the existing data and create a new Row * Col zero matrix*/
        m_Row = Row;
        m_Col = Col;
        m_nElement = m_Row * m_Col;
        delete[] m_Matrix_Data;
        m_Matrix_Data = new T[m_nElement];
        if (m_Matrix_Data != nullptr) {
            for (unsigned i = 0; i < m_nElement; i++) m_Matrix_Data[i] = 0.0;
        }
    }

    template<class T>
    T Matrix<T>::GetElement(const unsigned int Row, const unsigned int Col) const {
        int Index = Sub2Ind(Row, Col);
        if (Index >= 0) return m_Matrix_Data[Index];
        else return 0.0;
    }

    template<class T>
    void Matrix<T>::SetElement(const unsigned int Row, const unsigned int Col, const T Value) {
        int Index = Sub2Ind(Row, Col);
        if (Index >= 0) {
            m_Matrix_Data[Index] = Value;
        }
    }

    template<class T>
    inline unsigned int Matrix<T>::GetNumRow() const { return m_Row; }

    template<class T>
    inline unsigned int Matrix<T>::GetNumcol() const { return m_Col; }

    template<class T>
    bool Matrix<T>::operator==(const Matrix <T> &RHS) {
        if ((this->m_Row != RHS.m_Row) && (this->m_Col != RHS.m_Col)) {
            return false;
        }
        bool flag = true;
        for (unsigned i = 0; i < this->m_nElement; ++i) {
            //if (this->m_Matrix_Data[i] != RHS.m_Matrix_Data[i]){
            if (!CloseEnough(this->m_Matrix_Data[i], RHS.m_Matrix_Data[i])) {
                flag = false;
            }
        }
        return flag;
    }

    template<class U>
    Matrix <U> operator+(const Matrix <U> &LHS, const Matrix <U> &RHS) {
        int numRow = LHS.m_Row;
        int numCol = LHS.m_Col;
        int numElement = LHS.m_nElement;
        U *temp = new U[numElement];
        for (auto i = 0; i < numElement; i++) temp[i] = LHS.m_Matrix_Data[i] + RHS.m_Matrix_Data[i];
        Matrix<U> Res(numRow, numCol, temp);
        delete[] temp;
        return Res;
    }

    template<class U>
    Matrix <U> operator+(const Matrix <U> &LHS, const U &RHS) {
        int numRow = LHS.m_Row;
        int numCol = LHS.m_Col;
        int numElement = LHS.m_nElement;
        U *temp = new U[numElement];
        for (auto i = 0; i < numElement; i++) temp[i] = LHS.m_Matrix_Data[i] + RHS;
        Matrix<U> Res(numRow, numCol, temp);
        delete[] temp;
        return Res;
    }

    template<class U>
    Matrix <U> operator+(const U &LHS, const Matrix <U> &RHS) {
        int numRow = LHS.m_Row;
        int numCol = LHS.m_Col;
        int numElement = LHS.m_nElement;
        U *temp = new U[numElement];
        for (auto i = 0; i < numElement; i++) temp[i] = LHS + RHS.m_Matrix_Data[i];
        Matrix<U> Res(numRow, numCol, temp);
        delete[] temp;
        return Res;
    }

    template<class U>
    Matrix <U> operator-(const Matrix <U> &LHS, const Matrix <U> &RHS) {
        int numRow = LHS.m_Row;
        int numCol = LHS.m_Col;
        int numElement = LHS.m_nElement;
        U *temp = new U[numElement];
        for (auto i = 0; i < numElement; i++) temp[i] = LHS.m_Matrix_Data[i] - RHS.m_Matrix_Data[i];
        Matrix<U> Res(numRow, numCol, temp);
        delete[] temp;
        return Res;
    }

    template<class U>
    Matrix <U> operator-(const U &LHS, const Matrix <U> &RHS) {
        int numRow = LHS.m_Row;
        int numCol = LHS.m_Col;
        int numElement = LHS.m_nElement;
        U *temp = new U[numElement];
        for (auto i = 0; i < numElement; i++) temp[i] = LHS - RHS.m_Matrix_Data[i];
        Matrix<U> Res(numRow, numCol, temp);
        delete[] temp;
        return Res;
    }

    template<class U>
    Matrix <U> operator*(const Matrix <U> &LHS, const Matrix <U> &RHS) {
        int r_Row = RHS.m_Row;
        int r_Col = RHS.m_Col;
        int l_Row = LHS.m_Row;
        int l_Col = LHS.m_Col;
        if (l_Col == r_Row) {
            U *temp = new U[l_Row * r_Col];
            for (auto i = 0; i < l_Row; i++) {
                for (auto j = 0; j < r_Col; j++) {
                    U E_Res = 0.0;
                    for (auto k = 0; k < l_Col; k++) {
                        int lhsIndex = (i * l_Col) + k;
                        int rhsIndex = (k * r_Col) + j;
                        E_Res += (LHS.m_Matrix_Data[lhsIndex] * RHS.m_Matrix_Data[rhsIndex]);
                    }
                    int ResIndex = (i * r_Col) + j;
                    temp[ResIndex] = E_Res;
                }

            }
            Matrix<U> Res(l_Row, r_Col, temp);
            delete[] temp;
            return Res;
        } else {
            Matrix<U> Res((U) 1, (U) 1);
            return Res;
        }
    }

    template<class U>
    Matrix <U> operator-(const Matrix <U> &LHS, const U &RHS) {
        int numRow = LHS.m_Row;
        int numCol = LHS.m_Col;
        int numElement = LHS.m_nElement;
        U *temp = new U[numElement];
        for (auto i = 0; i < numElement; i++) temp[i] = LHS.m_Matrix_Data[i] - RHS;
        Matrix<U> Res(numRow, numCol, temp);
        delete[] temp;
        return Res;
    }

    template<class U>
    Matrix <U> operator*(const U &LHS, const Matrix <U> &RHS) {
        int numRow = RHS.m_Row;
        int numCol = RHS.m_Col;
        int numElement = numCol * numRow;
        U *temp = new U[numElement];
        for (auto i = 0; i < numElement; i++) temp[i] = LHS * RHS.m_Matrix_Data[i];
        Matrix Res(numRow, numCol, temp);
        delete[] temp;
        return Res;

    }

    template<class U>
    Matrix <U> operator*(const Matrix <U> &LHS, const U &RHS) {
        int numRow = RHS.m_Row;
        int numCol = RHS.m_Col;
        int numElement = numCol * numRow;
        U *temp = new U[numElement];
        for (auto i = 0; i < numElement; i++) temp[i] = LHS.m_Matrix_Data[i] * RHS;
        Matrix Res(numRow, numCol, temp);
        delete[] temp;
        return Res;
    }

    template<class T>
    Matrix<T>::Matrix(const Matrix <T> &Input) {
        m_Row = Input.m_Row;
        m_Col = Input.m_Col;
        m_nElement = Input.m_nElement;
        m_Matrix_Data = new T[m_nElement];
        for (unsigned i = 0; i < m_nElement; i++) m_Matrix_Data[i] = Input.m_Matrix_Data[i];

    }

    template<class T>
    constexpr unsigned int Matrix<T>::Sub2Ind(const unsigned int &Row, const unsigned int &Col) const {
        if ((Row < m_Row) && (Row >= 0) && (Col < m_Col) && (Col >= 0)) return (Row * m_Col) + Col;
        else return -1;
    }


    template<class T>
    void Matrix<T>::Set_To_Identiy() {

        if (!IsSquare()) throw std::invalid_argument("Matrix is not square"); //Identity is always squre
        for (unsigned row = 0; row < m_Row; ++row)
            for (unsigned col = 0; col < m_Col; ++col) {
                if (col == row) m_Matrix_Data[Sub2Ind(row, col)] = 1.0; //If we are on the diagonal, put 1
                else m_Matrix_Data[Sub2Ind(row, col)] = 0; // else put 0
            }
    }

    template<class T>
    constexpr bool Matrix<T>::compare(const Matrix <T> &mat1, const double &tol) const {
        unsigned numRow = mat1.m_Row;
        unsigned numCol = mat1.m_Col;
        if ((numRow != m_Row) || (numCol != m_Col)) return false;

        double CumSum = 0.0;
        for (unsigned i = 0; i < m_nElement; ++i) {
            T element1 = mat1.m_Matrix_Data[i];
            T element2 = m_Matrix_Data[i];
            CumSum += ((element1 - element2) * (element1 - element2));
        }

        double Res = sqrt(CumSum / ((numRow * numCol) - 1));
        return Res < tol;
    }

    template<class T>
    void Matrix<T>::Separate(Matrix <T>& Mat1, Matrix <T>& Mat2, const unsigned int &Colnum) const {
        //Divide the matrix in 2 SubMatrix with the number of rows

        /*Matrix passed by ref, are supposed to be only instantiated with no important
         * Resize in the size wanted */
        Mat1.resize(m_Row, Colnum);
        Mat2.resize(m_Row, Colnum);

        for (unsigned row = 0; row < m_Row; ++row)
            for (unsigned col = 0; col < m_Col; ++col) {
                //The first matrix is filled
                if (col < Colnum) Mat1.SetElement(row, col, this->GetElement(row, col));
                    //When the columns is superior to the first matrix's number of columns we flled the second one
                else Mat2.SetElement(row, col - Colnum, this->GetElement(row, col));
            }
    }


    template<class T>
    constexpr inline bool Matrix<T>::CloseEnough(T f1, T f2) { return fabs(f1 - f2) < 1e-9; }


    template<class T>
    void Matrix<T>::Join(const Matrix <T> &matrix) {
        //Make an augmented Matrix (to the left), works in place thus it modifies the existing matrix.


        const unsigned numRow1 = m_Row;
        const unsigned numRow2 = matrix.m_Row;
        const unsigned numCol1 = m_Col;
        const unsigned numCol2 = matrix.m_Col;

        //We change only he number of columns of the augmented matrix, the number of rows is the same
        const unsigned newnumCol = numCol1 + numCol2;

        if (numRow1 != numRow2) throw std::invalid_argument("Join : Different rows");
        T *newmat = new T[numRow1 * newnumCol]; //New matrix data, we'll replace the old by it at the end
        unsigned int Index, Resindex; //Used to compute the linear indexes

        for (unsigned i = 0; i < numRow1; ++i) {
            for (unsigned j = 0; j < newnumCol; ++j) {
                Resindex = (i * newnumCol) + j;
                if (j < numCol1) {
                    Index = (i * numCol1) + j;
                    newmat[Resindex] = m_Matrix_Data[Index];
                } else {
                    Index = (i * numCol2) + (j - numCol1);
                    newmat[Resindex] = matrix.m_Matrix_Data[Index];
                }
            }
        }
        //Create the new matrix
        m_Col = newnumCol;
        m_nElement = m_Row * newnumCol;
        delete[] m_Matrix_Data;
        m_Matrix_Data = new T[m_nElement];
        for (unsigned k = 0; k < m_nElement; ++k) m_Matrix_Data[k] = newmat[k];
        delete[] newmat;
    }

    template<class T>
    SOLUTIONS Matrix<T>::Inverse() {

        /*Compute the inverse Matrix if it exists, if not, returns a zeros matrix and SOLUTION::NO_INVERSE
         * It works in place thus it modifies the existing matrix */

        if (!IsSquare()) throw std::invalid_argument("Matrix has to be square");

        //Make identity in order to compare the Left side of the augmented matrix at the end
        Matrix<T> Identity(m_Row, m_Col);
        Identity.Set_To_Identiy();

        unsigned int First_NumCol = m_Col;

        /*Make the augmented matrix to perform the GaussElimination
         * At the beginning the right side is identity and the left is the matrix to invert
         * At the end (if it has an inverse) it's the opposite */
        this->Join(Identity);

        unsigned int count = 0; //Count to avoid infinite loop

        unsigned int MaxIndex;


        //Gauss elimination on the augmented matrix
        while (count < MAXLOOP) {
            for (unsigned int diag = 0; diag < m_Row; ++diag) {

                MaxIndex = FindRowWithMax(diag, diag); //Look after the pivot

                if (MaxIndex != diag) SwapRow(diag, MaxIndex);

                //Pivot pivot isn't equal to 1 -> operation on the row to put a 1
                if (m_Matrix_Data[Sub2Ind(diag, diag)] != 1.0) {
                    T fact = 1.0 / m_Matrix_Data[Sub2Ind(diag, diag)];
                    MultRow(diag, fact);
                }

                for (unsigned int rowIndex = diag + 1; rowIndex < m_Row; ++rowIndex) {

                    //If it isn't equal to 0,
                    if (!CloseEnough(m_Matrix_Data[Sub2Ind(rowIndex, diag)], 0.0)) {

                        unsigned int RowOneIndex = diag;
                        T currentValue = m_Matrix_Data[Sub2Ind(rowIndex, diag)];
                        T RowOneValue = m_Matrix_Data[Sub2Ind(RowOneIndex, diag)]; //Value of the pivot

                        if (!CloseEnough(RowOneValue, 0.0)) {
                            T CorrectFactor = -(currentValue / RowOneValue);
                            MultAdd(rowIndex, RowOneIndex, CorrectFactor);
                        }
                    }
                }

                for (unsigned int colIndex = diag + 1; colIndex < First_NumCol; ++colIndex) {
                    if (!CloseEnough(m_Matrix_Data[Sub2Ind(diag, colIndex)], 0.0)) {
                        unsigned int RowOneIndex = colIndex;

                        T currentValue = m_Matrix_Data[Sub2Ind(diag, colIndex)];
                        T RowOneValue = m_Matrix_Data[Sub2Ind(RowOneIndex, colIndex)];

                        if (!CloseEnough(RowOneValue, 0.0)) {
                            T CorrectFactor = -(currentValue / RowOneValue);
                            MultAdd(diag, RowOneIndex, CorrectFactor);
                        }
                    }
                }
            }

            Matrix<T> leftHalf;
            Matrix<T> righHalf;
            this->Separate(leftHalf, righHalf, First_NumCol);

            //If it's true, Elimination is finished
            if (leftHalf == Identity) {
                //Create a the new inverse matrix in order
                m_Col = First_NumCol;
                m_nElement = m_Row * m_Col;
                delete[] m_Matrix_Data;
                m_Matrix_Data = new T[m_nElement];
                for (unsigned int k = 0; k < m_nElement; ++k) m_Matrix_Data[k] = righHalf.m_Matrix_Data[k];
                return SOLUTIONS::DONE;
            }
            count++;
        }


        m_Row = First_NumCol;
        m_Col = First_NumCol;
        m_nElement=m_Row*m_Row;
        delete[] m_Matrix_Data;
        m_Matrix_Data = new T[m_nElement];
        for (unsigned i = 0; i < m_nElement; ++i)
            m_Matrix_Data[i] = static_cast<T>(0.0); //This avoids to have a NaN Matrix
        return SOLUTIONS::NO_INVERSE;
    }

    template<class T>
    constexpr inline bool Matrix<T>::IsSquare() const { return m_Col == m_Row; }

    template<class T>
    void Matrix<T>::SwapRow(const unsigned int i, const unsigned int j) {
        T *temprow = new T[m_Col];
        for (unsigned int k = 0; k < m_Col; ++k) temprow[k] = m_Matrix_Data[Sub2Ind(i, k)];
        for (unsigned int l = 0; l < m_Col; ++l) m_Matrix_Data[Sub2Ind(i, l)] = m_Matrix_Data[Sub2Ind(j, l)];
        for (unsigned int m = 0; m < m_Col; ++m) m_Matrix_Data[Sub2Ind(j, m)] = temprow[m];

        delete[] temprow;

    }

    template<class T>
    inline void Matrix<T>::MultAdd(const unsigned int i, const unsigned int j, T factor) {
        for (unsigned k = 0; k < m_Col; ++k) m_Matrix_Data[Sub2Ind(i, k)] += (m_Matrix_Data[Sub2Ind(j, k)] * factor);
    }

    template<class T>
    constexpr unsigned int Matrix<T>::FindRowWithMax(const unsigned int &Col, const unsigned int &RowStart) const {
        T temp = m_Matrix_Data[Sub2Ind(RowStart, Col)];
        unsigned int RowIndex = RowStart;

        for (auto i = RowStart + 1; i < m_Row; ++i) {
            if (fabs(m_Matrix_Data[Sub2Ind(i, Col)]) > fabs(temp)) {
                RowIndex = i;
                temp = m_Matrix_Data[Sub2Ind(i, Col)];
            }
        }
        return RowIndex;
    }

    template<class T>
    inline void Matrix<T>::MultRow(const unsigned int i, T factor) {
        for (unsigned k = 0; k < m_Col; ++k) m_Matrix_Data[Sub2Ind(i, k)] *= factor;
    }

    template<class T>
    constexpr T Matrix<T>::Determinant() const {

        /*Compute the Determinant of the Matrix, return a T type.
         * Recursive function which divides the matrix into sub matrix until the sub matrix is a 2*2 matrix
         * There whe can easily compute the determinant */


        if (!IsSquare()) throw std::invalid_argument("Determinant : Has to be square"); //Non square matrix don't have a determinant

        T Determinant;
        if (m_Row == 2) {
            Determinant = (m_Matrix_Data[0] * m_Matrix_Data[3]) - (m_Matrix_Data[1] * m_Matrix_Data[2]);
        } else {
            T CumSum = 0.0;
            T Sign = 1.0;
            for (unsigned int i = 0; i < m_Col; ++i) {
                Matrix <T> SubMat = this->FindSubMatrix(0, i);
                CumSum += this->GetElement(0, i) * SubMat.Determinant() * Sign;
                Sign = -Sign;
            }
            Determinant = CumSum;
        }

        return Determinant;
    }

    template<class T>
    Matrix <T> Matrix<T>::FindSubMatrix(unsigned int Row, unsigned int Col) const {
        Matrix<T> SubMatrix(m_Row - 1, m_Col - 1);
        unsigned int count = 0;
        for (unsigned int i = 0; i < m_Row; ++i) {
            for (unsigned int j = 0; j < m_Col; ++j) {
                if ((i != Row) && (j != Col)) {
                    SubMatrix.m_Matrix_Data[count] = this->GetElement(i, j);
                    count++;
                }
            }
        }

        return SubMatrix;
    }

    template<class T>
    Vector <T> operator*(const Matrix <T> &LHS, const Vector <T> &RHS) {
        if (LHS.m_Col != RHS.GetDim()) throw std::invalid_argument("In Matrix.hpp Not the same dimensions");

        //Vector<T> VRes = RHS;
        Vector<T> VRes(LHS.m_Row);
        for (unsigned int row = 0; row < LHS.m_Row; ++row) {
            T CumSum = static_cast<T>(0.0);
            for (unsigned int col = 0; col < LHS.m_Col; ++col) {
                CumSum += (LHS.GetElement(row, col)) * RHS.GetElement(col);
            }
            VRes.SetElement(row, CumSum);
        }
        return VRes;
    }

    /** Verifying if the matrix is an echelon matrix**/
    template<class T>bool Matrix<T>::IsEchelon() const {
        T CumSum = static_cast<T>(0.0);

        for (unsigned i = 0; i < m_Row; ++i) {
            for (unsigned j = 0; j < i; ++j) {
                CumSum += m_Matrix_Data[Sub2Ind(i, j)];
            }
        }
        return CloseEnough(CumSum, 0.0);
    }


    /** Return the  echelon matrix
    Works in place but doesn't modifies the matrix  **/
    template<class T>Matrix <T> Matrix<T>::Echelon() {

        //if (m_Col < m_Row) throw std::invalid_argument("Not Diamond");

        //Copy to store the matrix data, we'll replace it at the end
        T *Temp = new T[m_nElement];
        for (unsigned i = 0; i < m_nElement; ++i) Temp[i] = m_Matrix_Data[i];


        unsigned count = 0; //Avoids a infinite loop
        bool complete = false; //Loop variant of the while loop
        //Gaus Elimination without the return
        while ((!complete) && (count < MAXLOOP)) {

            for (unsigned diag = 0; diag < m_Row; ++diag) {

                for (unsigned rowindex = diag + 1; rowindex < m_Row; ++rowindex) {

                    if (!CloseEnough(m_Matrix_Data[Sub2Ind(rowindex, diag)], 0.0)) {

                        unsigned RowOneIndex = diag;
                        T CurrentValue = m_Matrix_Data[Sub2Ind(rowindex, diag)];
                        T RowOneValue = m_Matrix_Data[Sub2Ind(RowOneIndex, diag)];
                        if (!CloseEnough(RowOneValue, 0.0)) {

                            T Correct = -(CurrentValue / RowOneValue);
                            MultAdd(rowindex, RowOneIndex, Correct);

                        }
                    }
                }
            }

            complete = this->IsEchelon();
            count++;

        }
        Matrix<T> Res(m_Row, m_Col, m_Matrix_Data);

        for (unsigned j = 0; j < m_nElement; ++j) {
            m_Matrix_Data[j] = Temp[j];
        }
        delete[] Temp;
        return Res;
    }

    template<class T>
    Matrix<T>::Matrix(unsigned int Row, unsigned int Col, const std::vector<T> &Input) {
        m_Row = Row;
        m_Col = Col;
        m_nElement = Row * Col;
        m_Matrix_Data = new T[m_nElement];
        for (unsigned i = 0; i < m_nElement; ++i) {
            m_Matrix_Data[i] = Input.at(i);
        }
    }

    template<class T>
    unsigned int Matrix<T>::Rank() {

        /* Computes rank watching after an empty row in the matrix,
         * To test it, we computes the determinant if there's a submatrix with a det =0 then the row is empty*/
        Matrix<T> Copy = this->Echelon();
        unsigned int NonZerosRow = 0;

        if (!Copy.IsEchelon()) {
            std::vector<Matrix<T>> VecSubMatrix;
            VecSubMatrix.emplace_back(*this);
            bool complete = false;
            unsigned int SubMatCount = 0;
            while ((SubMatCount < VecSubMatrix.size() && (!complete))) {

                Matrix<T> CurrentMat = VecSubMatrix[SubMatCount];

                SubMatCount++;
                if (CurrentMat.IsNonZero()) {
                    T CurrentDet = CurrentMat.Determinant();
                    if (!CloseEnough(CurrentDet, 0.0)) {
                        complete = true;
                        NonZerosRow = CurrentMat.GetNumRow();
                    } else {
                        if ((CurrentMat.GetNumRow() > 2) && (CurrentMat.GetNumcol() > 2)) {
                            for (unsigned i = 0; i < CurrentMat.GetNumRow(); ++i) {
                                for (unsigned j = 0; j < CurrentMat.GetNumcol(); ++j) {
                                    VecSubMatrix.emplace_back(CurrentMat.FindSubMatrix(i, j));
                                }
                            }
                        }
                    }
                }
            }
        } else {
            auto Row = Copy.GetNumRow();
            auto Col = Copy.GetNumcol();
            for (unsigned i = 0; i < Row; ++i) {
                unsigned ColSum = 0;
                for (unsigned j = 0; j < Col; ++j) {
                    if (!CloseEnough(Copy.GetElement(i, j), 0.0))ColSum++;
                }
                if (ColSum > 0) NonZerosRow++;
            }
        }
        return NonZerosRow;
    }

    template<class T>
    constexpr bool Matrix<T>::IsNonZero() const {
        unsigned int NonZeros =0;
        for (unsigned int i = 0; i < m_nElement; ++i) {
            if (!CloseEnough(m_Matrix_Data[i], 0.0)) NonZeros++;
        }
        return (NonZeros != 0);
    }

    template<class T>
    Matrix <T> &Matrix<T>::operator=(const Matrix<T>& RHS) {
        if (this != &RHS) {
            m_Row = RHS.m_Row;
            m_Col = RHS.m_Col;
            m_nElement = RHS.m_nElement;
            if (m_Matrix_Data) delete[] m_Matrix_Data;
            m_Matrix_Data = new T[m_nElement];
            for (unsigned int i = 0; i < m_nElement; ++i) {
                m_Matrix_Data[i] = RHS.m_Matrix_Data[i];
            }
            return *this;
        } else return *this;
    }


    /** Computes the Matrix transpose, doesn't modify the matrix
     * @return Matrix<T> Transposed  **/
    template<class T>Matrix <T> Matrix<T>::Transposed() {
        //t's basically a swap of rows and columss */
        Matrix<T> Res(m_Col, m_Row); //Create a new matrix which will be returned (fixed size)
        for (unsigned int i = 0; i < m_Row; ++i) {
            for (unsigned int j = 0; j < m_Col; ++j) {
                Res.SetElement(j, i, this->GetElement(i, j));
            }
        }
        return Res;
    }

    template<class T>
    constexpr bool Matrix<T>::IsSymmetric() const {
        if (!IsSquare()) return false;

        T currentRowElement = static_cast<T>(0.0);
        T currentColElement = static_cast<T>(0.0);
        bool returnFlag = true;
        unsigned diagIndex = 0;

        while ((diagIndex < m_Col) && returnFlag) {
            unsigned rowIndex = diagIndex + 1;
            while ((rowIndex < m_Row) && returnFlag) {
                currentRowElement = GetElement(rowIndex, diagIndex);
                currentColElement = GetElement(diagIndex, rowIndex);

                // Compare the row and column elements.
                if (!CloseEnough(currentRowElement, currentColElement))
                    returnFlag = false;

                // Increment row index.
                rowIndex++;
            }

            // Increment diagIndex.
            diagIndex++;

        }

        return returnFlag;
    }

    template<class T>
    Matrix<T>::Matrix(const Vector <T> &Input) {
        m_Row = Input.GetDim();
        m_Col = 1;
        m_nElement = m_Row;
        m_Matrix_Data = new T[m_nElement];
        for (unsigned int i = 0; i < m_Row; ++i) m_Matrix_Data[i] = Input.GetElement(i);
    }



    template<class T>
    Matrix <T> Matrix<T>::operator^(const unsigned Pow) {

        //if (!IsDiag() && Pow > 100) std::cout << "Warning : Too much operation for a non diag matrix" << std::endl;
        Matrix<T> Tamp(m_Row, m_Col, m_Matrix_Data);
        Matrix<T> Res(m_Row, m_Row, m_Matrix_Data);
        if (!IsDiag()) {
            for (unsigned i = 1; i < Pow; ++i) {
                Res = Res * Tamp;
            }
            return Res;
        } else {

            T *Tampdata = new T[m_nElement];
            for (unsigned i = 0; i < m_nElement; ++i) Tampdata[i] = m_Matrix_Data[i];
            unsigned int Index;
            for (unsigned int i = 0; i < m_Row; ++i) {
                for (unsigned int j = 0; j < m_Col; ++j) {
                    if (i == j) {
                        Index = (i * m_Col) + j;
                        Tampdata[Index] = std::pow(Tampdata[Index], Pow);
                    }
                }
            }

            Matrix<T> ResDiag(m_Row, m_Col, Tampdata);
            delete[] Tampdata;
            return ResDiag;
        }

    }

    template<class T>
    constexpr bool Matrix<T>::IsDiag() const {
        unsigned Index =0;
        if (!IsSquare()) return false;
        else {
            for (unsigned i = 0; i < m_Row; ++i)
                for (unsigned int j = 0; j < m_Col; ++j) {
                    Index = (i * m_Col) + j;
                    if ((i != j) && !CloseEnough(m_Matrix_Data[Index], static_cast<T>(0.0))) return false;
                }
            return true;
        }
    }

    template<class T>
    Matrix<T>::Matrix(unsigned int dim) {
        m_Row = dim;
        m_Col = dim;
        m_nElement = dim * dim;
        m_Matrix_Data = new T[m_nElement];
        for (unsigned row = 0; row < dim; ++row)
            for (unsigned col = 0; col < dim; ++col) {
                if (col == row) m_Matrix_Data[Sub2Ind(row, col)] = 1.0; //If we are on the diagonal, put 1
                else m_Matrix_Data[Sub2Ind(row, col)] = 0; // else put 0
            }
    }

}


#include "EigenValues.hpp"
#include "QR.hpp"
#include "EigenVector.hpp"
#include "GaussElimination.hpp"
#include "LinSolve.hpp"
#include "Diagonalize.hpp"

#endif //MATRIX_MATRIXMETHODS_HPP
