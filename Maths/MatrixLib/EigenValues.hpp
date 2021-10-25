//
// Created by Benjamin on 05/08/2021.
//

#ifndef MATH_EIGENVALUES_HPP
#define MATH_EIGENVALUES_HPP

#include "Matrix.hpp"

namespace LinearAlgebra {

    template <typename T>
    SOLUTIONS Matrix<T>::EigenValueQR(std::vector<T> &eigenValues) const{
        // Make a copy of the input matrix.
        Matrix<T> A = Matrix<T>(m_Row, m_Col, m_Matrix_Data);

        // Check hypothesis
        if (!A.IsSquare()) return SOLUTIONS::NOT_SQUARE;
        if (!A.IsSymmetric()) return SOLUTIONS::NOT_SYMETRIC;


        // The number of eigenvalues is equal to the number of rows.
        unsigned numRows = A.GetNumRow();


        // Create matrices to store Q and R.
        Matrix<T> Q (numRows, numRows);
        Matrix<T> R (numRows, numRows);

        // Loop through each iteration.
        unsigned iterationCount = 0;

        /* Check if A is now close enough to being upper-triangular.
     We can do this using the IsRowEchelon() function from the
     qbMatrix2 class. */
        while ((iterationCount < MAXLOOPEIGEN) && !(A.IsEchelon()))
        {
            auto returnValue = A.QR_Decomposition(Q,R); //QR(A, Q, R);
            if(returnValue!=SOLUTIONS::DONE) return returnValue;
            A = R * Q;
            iterationCount++;
        }

        // At this point, the eigenvalues should be the diagonal elements of A.
        for (int i=0; i<numRows; ++i) eigenValues.push_back(A.GetElement(i,i));

//        for(unsigned i =0;i<numRows;++i){
//            const auto precision = std::pow(10.0,10);
//            auto val = std::ceil(A.GetElement(i,i) * precision) / precision;
//            eigenValues.push_back(val);
//        }


        return (iterationCount == MAXLOOPEIGEN) ? SOLUTIONS::MAXITERATION : SOLUTIONS::DONE;
    }


}

#endif //MATH_EIGENVALUES_HPP
