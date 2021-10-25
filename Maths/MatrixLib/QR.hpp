//
// Created by CASALE Benjamin on 06/04/2021.
//

#ifndef MATRIX_QR_HPP
#define MATRIX_QR_HPP

#include "Matrix.hpp"

namespace LinearAlgebra {


    /** Make the QR decomposition that is to say A = Q*R
    Where Q is an orthogonal matrix (QT*Q=I) and R is upper triangular
     @param Q Result Matrix Q
     @param R Result Matrix R **/
    template<class T>SOLUTIONS Matrix<T>::QR_Decomposition(Matrix <T> &Q, Matrix <T> &R) const {


        Matrix<T> Input = Matrix<T>(m_Row,m_Col,m_Matrix_Data); //Copy
        Matrix<T> Copy = Input;
        if (!Input.IsSquare()) return SOLUTIONS::NOT_SQUARE; //It works only for square matrix

        const unsigned int Col = Input.GetNumcol();

        std::vector<Matrix<T>> PList; //Contains Matrix computed for each columns

        for (unsigned int i = 0; i < Col - 1; ++i) {
            Vector<T> a1(Col - i); //Columns of A
            Vector<T> b1(Col - i);
            for (unsigned int j = i; j < Col; ++j) {
                a1.SetElement(j - i, Input.GetElement(j, i));
                b1.SetElement(j - i, static_cast<T>(0.0));
            }
            b1.SetElement(0, static_cast<T>(1.0));

            T NormA1 = a1.Norm();

            int sign = -1;
            if (a1.GetElement(0) < static_cast<T>(0.0)) sign = 1;

            Vector<T> U = a1 - (sign * NormA1 * b1);
            Vector<T> N = U.Normalize();

            //Convert N to Matrix in order to transpose it
            Matrix<T> nMat(Col - i, 1);
            for (unsigned int k = 0; k < Col - i; ++k) nMat.SetElement(k, 0, N.GetElement(k));

            Matrix<T> nMatT = nMat.Transposed();
            Matrix<T> I(Col - i, Col - i);
            I.Set_To_Identiy();
            Matrix<T> Ptemp = I - static_cast<T>(2.0) * nMat * nMatT;

            Matrix<T> P(Col, Col);
            P.Set_To_Identiy();

            for (unsigned int row = i; row < Col; ++row) {
                for (unsigned int col = i; col < Col; ++col) {
                    P.SetElement(row, col, Ptemp.GetElement(row - i, col - i));
                }
            }

            PList.emplace_back(P);

            Input = P * Input;
        }

        //Compute the Q Matrix
        Matrix<T> QMat = PList.at(0);
        for (unsigned int l = 1; l < Col - 1; ++l) QMat = QMat * PList.at(l).Transposed();

        Q = QMat;

        //Compute the R Matrix
        int NumElement = PList.size();
        Matrix<T> Rmat = PList.at(NumElement - 1);
        for (int m = NumElement - 2; m >= 0; --m) {
            Rmat = Rmat * PList.at(m);
        }
        Rmat = Rmat * Copy;

        R = Rmat;

        return SOLUTIONS::DONE;

    }
}
#endif //${Filename}
