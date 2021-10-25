//
// Created by Benjamin on 06/08/2021.
//

#ifndef MATH_GAUSSELIMINATION_HPP
#define MATH_GAUSSELIMINATION_HPP
#include "Matrix.hpp"

namespace LinearAlgebra {

    /** Perform a gaussian Elimination,
     * Modifies matrix **/
    template<typename T>
    SOLUTIONS Matrix<T>::GaussElimination() {

        unsigned int count = 0; //Count to avoid infinite loop

        unsigned int MaxIndex;

        while (count < MAXLOOP) {
            count++;

            for (unsigned int diag = 0; diag < m_Row-1; ++diag) {
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


                        //To reduce coefficient to 1
                        if (!CloseEnough(RowOneValue, 0.0)) {
                            T CorrectFactor = -(currentValue / RowOneValue);
                            MultAdd(rowIndex, RowOneIndex, CorrectFactor);
                        }
                    }
                }

                for (unsigned int colIndex = diag + 1; colIndex < m_Col-1; ++colIndex) {
                    if (!CloseEnough(m_Matrix_Data[Sub2Ind(diag, colIndex)], 0.0)) {
                        unsigned int RowOneIndex = colIndex;

                        T currentValue = m_Matrix_Data[Sub2Ind(diag, colIndex)];
                        T RowOneValue = m_Matrix_Data[Sub2Ind(RowOneIndex, colIndex)];


                        //To reduce coefficient to 1
                        if (!CloseEnough(RowOneValue, 0.0)) {
                            T CorrectFactor = -(currentValue / RowOneValue);
                            MultAdd(diag, RowOneIndex, CorrectFactor);
                        }
                    }
                }
            }
        }

        return SOLUTIONS::DONE;
    }
}

#endif //MATH_GAUSSELIMINATION_HPP
