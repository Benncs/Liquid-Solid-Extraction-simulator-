//
// Created by Benjamin on 06/08/2021.
//

#ifndef MATH_DIAGONALIZE_HPP
#define MATH_DIAGONALIZE_HPP
#include "Matrix.hpp"

namespace LinearAlgebra {


    /** @brief To Diagonalize Matrix, doesn't modify the matrix, matrix has to be square of dim=n and symmetric
     * @param Diag matrix as a resul
     * @param P Transition Matrix for the associated matrix, dim n*n and invertible **/
    template<typename T>
    SOLUTIONS Matrix<T>::Diagonalize(Matrix <T> &Diag, Matrix <T> &P) const {
        if(!this->IsSquare()) return SOLUTIONS::NOT_SQUARE;
        if(!this->IsSymmetric()) return SOLUTIONS::NOT_SYMETRIC;


        //Get EigenVectors and Eigenvalues of the matrix
        std::vector<Vector<T>> ListEigenVectors;
        std::vector<T> EigenValue;
        this->EigenValueQR(EigenValue);

        auto Check = this->EigenVectors(EigenValue,ListEigenVectors);
        if(Check!=SOLUTIONS::DONE) return Check;

        if (ListEigenVectors.size()!=m_Row) {return SOLUTIONS::NON_DIAG;}

        Matrix<T> Res(m_Row,m_Row); //Initalized result matrix

        //Loop to put every eigenvalue on the diagonal of the result matrix
        for (unsigned int row = 0; row < m_Row ; ++row) for (unsigned int col = 0; col < m_Row ; ++col) {
                if (row==col) Res.SetElement(row,col,EigenValue[row]);
                else Res.SetElement(row,col,static_cast<T>(0.0));
            }


        P.resize(m_Row,1); //Rezize matrix P (column matrix)
        // Put the first eigenvector in the first columns of the P matrix
        for (int row = 0; row < m_Row; ++row) P.SetElement(row,0,ListEigenVectors[0].GetElement(row));
        //Add the other eigenvector to the P matrix.
        for (auto i =1;i<ListEigenVectors.size();++i) {
            if(ListEigenVectors[i].IsNull()) return SOLUTIONS::ERROR1;
            P.Join(Matrix<T>(ListEigenVectors[i]));
        }

        Diag = Res;

        return SOLUTIONS::DONE;

    }

}


#endif //MATH_DIAGONALIZE_HPP
