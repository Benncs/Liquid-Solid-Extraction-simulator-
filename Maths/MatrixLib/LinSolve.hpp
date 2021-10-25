//
// Created by CASALE Benjamin on 06/04/2021.
//

#ifndef MATRIX_LINSOLVE_HPP
#define MATRIX_LINSOLVE_HPP

#include "Matrix.hpp"
#include <exception>


namespace LinearAlgebra {
/** To solve linear system of the form : AX=B
 * @param Matrix_A : Matrix that represents unknows's coefficients
 * @param Vector_X : Vector that represents result
 * @param Vector_B : Vector that represents the constants **/
    template<class T>
    SOLUTIONS LinSolve(const Matrix <T> &Matrix_A, const Vector <T> &Vector_B, Vector <T> &Vector_X) {
        Matrix<T> Input = Matrix_A; // Because mat1 is const qualified

        const unsigned int FirstRank = Input.Rank();

        const unsigned int NumDim = Vector_B.GetDim();

        std::vector<T> VInput;
        for (unsigned int i = 0; i < NumDim; ++i) {
            VInput.emplace_back(Vector_B.GetElement(i));
        }

        Matrix<T> BMat(NumDim, 1, VInput);
        Input.Join(BMat);
        Matrix<T> MatEchelon = Input;
        MatEchelon.GaussElimination();

        unsigned int RankAugmented;
        try { RankAugmented = MatEchelon.Rank(); }
        catch (std::invalid_argument &e) { RankAugmented = 7; }

        //unsigned RankAugmented = MatEchelon.Rank();
        if ((FirstRank == RankAugmented) && (FirstRank < Input.GetNumRow())) return SOLUTIONS::NO_UNIQUE;

        else if (FirstRank < RankAugmented) return SOLUTIONS::NO_SOL;

        else {
            Vector<T> Res(VInput);
            int Row = MatEchelon.GetNumRow();
            unsigned Col = MatEchelon.GetNumcol();
            int StartRow = Row - 1;
            for (int j = StartRow; j >= 0; --j) {
                T CRes = MatEchelon.GetElement(j, Col - 1);
                T CumSum = static_cast<T>(0.0);
                for (int k = j + 1; k < Row; ++k) {
                    CumSum += (MatEchelon.GetElement(j, k) * Res.GetElement(k));
                }
                T Ans = (CRes - CumSum) / MatEchelon.GetElement(j, j);

                Res.SetElement(j, Ans);
            }

            Vector_X = Res;
            return SOLUTIONS::ONE_SOL;
        }
    }

    /** To solve a linear system of the form AX=B
     * @param A Matrix that represents unknowns' coefficients, square matrix n*n
     * @param B Vector  that represents constant, n*1 vector
     * @param X Vector result
     * @return SOLUTION useful to know if computing has achieved, treat exception ...**/
    template<class T>
    SOLUTIONS LinSolveQR(const Matrix <T> &A, const Vector <T> &B, Vector <T> &X) {

        Matrix<T> Q, R;
        const unsigned Row = A.GetNumRow();
        const unsigned Col = A.GetNumcol();
        if (!A.IsSquare()) return SOLUTIONS::NOT_SQUARE;
        A.QR_Decomposition(Q, R);
        for (auto RowIndex = 0; RowIndex < Row; ++RowIndex) {
            for (auto ColIndex = 0; ColIndex < Col; ++ColIndex) {
                if (RowIndex == ColIndex && (abs(R.GetElement(RowIndex, ColIndex))) < 1e-9) return SOLUTIONS::NO_SOL;
            }
        }

        if (R.Inverse() == SOLUTIONS::NO_INVERSE) return SOLUTIONS::NO_SOL;
        const auto TransposedMatrix = Q.Transposed();
        X = R * TransposedMatrix * B;
        return SOLUTIONS::DONE;
    }


}
#endif //MATRIX_LINSOLVE_HPP
