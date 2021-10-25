//
// Created by Benjamin on 05/08/2021.
//

#ifndef MATH_EIGENVECTOR_HPP
#define MATH_EIGENVECTOR_HPP

#include "Matrix.hpp"
#include <random>

namespace LinearAlgebra {


    /** To compute Eigen Vector with the inverse iteration method
     * @param eigenValue: An eigenValue of the matrix
     * @param EigenVector: As a result, the eigenvector
     * @return SOLUTION: To treat exception, status ... **/
    template<class T>SOLUTIONS Matrix<T>::EigenVectorInverse(T eigenValue, Vector<T>& EigenVector) const {

        // Verify that the matrix is square.
        if (!this->IsSquare()) return SOLUTIONS::NOT_SQUARE;

        Matrix<T> A = Matrix<T>(m_Row,m_Col,m_Matrix_Data); // Copy;

        // Setup a random number generator.
        std::random_device myRandomDevice;
        std::mt19937 myRandomGenerator(myRandomDevice());
        std::uniform_int_distribution<int> myDistribution(1.0, 10.0);

        /* The number of eigenvectors and eigenvalues that we will compute will be
            equal to the number of rows in the input matrix. */

        // Create an identity matrix of the same dimensions.
        Matrix<T> identityMatrix(m_Row);
        // Create an initial vector, InitialVector.
        Vector<T> InitialVector(m_Row);
        for (unsigned i = 0; i < m_Row; ++i)
            InitialVector.SetElement(i, static_cast<T>(myDistribution(myRandomGenerator)));

        // Iterate.

        int iterationCount = 0;
        T deltaThreshold = static_cast<T>(1e-9);
        T delta = static_cast<T>(1e6);
        Vector<T> prevVector(m_Row);
        Matrix<T> tempMatrix(m_Row, m_Row);


        tempMatrix = A - (eigenValue * identityMatrix);

        auto res = tempMatrix.Inverse();
        if(res == SOLUTIONS::NO_INVERSE){
//            tempMatrix = A - (eigenValue * identityMatrix);
//            const unsigned col = tempMatrix.GetNumcol();
//
//            tempMatrix.GaussElimination();
//            std::vector<T> VectorComponent;
//            for(auto i  = 0 ; i<tempMatrix.m_Row;++i){
//                auto val = tempMatrix.GetElement(i,col-1);
//
//                VectorComponent.template emplace_back((val==0)?1:-val);
//            }
//            EigenVector = Vector<T>(VectorComponent);
//            return SOLUTIONS::DONE;

            EigenVector = Vector<T>(m_Row);
        }
        else if (res==SOLUTIONS::ERROR1||tempMatrix.GetNumcol() != m_Row || !tempMatrix.IsNonZero()) { return SOLUTIONS::ERROR1; }

        while ((iterationCount < MAXLOOPEIGEN) && (delta > deltaThreshold)) {
            // Store a copy of the current working vector to use for computing delta.
            prevVector = InitialVector;

            InitialVector = tempMatrix * InitialVector;
            InitialVector.NormalizeIt();

            // Compute delta.
            delta = (InitialVector - prevVector).Norm();
            // Increment iteration count.
            ++iterationCount;
        }

        // Return the estimated eigenvector.
        EigenVector = InitialVector;

        // Set the return status accordingly.
        return (iterationCount == MAXLOOPEIGEN) ? SOLUTIONS::MAXITERATION : SOLUTIONS::DONE;

    }


    /** To compute Eigen Vector with the inverse iteration method
     * @param ListEigenVectors: Result : std::vector<vector<T>>
     * @return SOLUTION: To treat exception, status ... **/
    template<class T>
    SOLUTIONS Matrix<T>::EigenVectors(std::vector<Vector<T>>& ListEigenVectors) const{
        std::vector<double> eigenValues;
        this->EigenValueQR(eigenValues);
        for(auto CurrentValue:eigenValues){
            auto Eigen = Vector<T>();
            auto Check = EigenVectorInverse(CurrentValue, Eigen);
            if(Check==SOLUTIONS::DONE || Check == SOLUTIONS::MAXITERATION) ListEigenVectors.emplace_back(Eigen);
            else return Check;
        }
        return SOLUTIONS::DONE;
}
/** To compute Eigen Vector with the inverse iteration method
     * @param ListEigenVectors: Result : std::vector<vector<T>>
     * @return SOLUTION: To treat exception, status ... **/
template<class T>SOLUTIONS Matrix<T>::EigenVectors(const std::vector<double>& eigenValues,std::vector<Vector<T>>& ListEigenVectors) const{
    auto Eigen = Vector<T>();
    for(auto& CurrentValue:eigenValues){
        auto Check = EigenVectorInverse(CurrentValue, Eigen);
        if(Check==SOLUTIONS::DONE || Check == SOLUTIONS::MAXITERATION) ListEigenVectors.emplace_back(Eigen);
        else return Check;
    }
    return SOLUTIONS::DONE;
}


template <typename T>
SOLUTIONS Matrix<T>::EigenVectorPower(T &eigenValue, Vector<T> &eigenVector) const{
    // Make a copy of the input matrix.
    Matrix<T> inputMatrix = Matrix<T>(m_Row,m_Col,m_Matrix_Data);

    // Verify that the input matrix is square.
    if (!inputMatrix.IsSquare()) return SOLUTIONS::NOT_SQUARE;

    // Setup a random number generator.
    std::random_device myRandomDevice;
    std::mt19937 myRandomGenerator(myRandomDevice());
    std::uniform_int_distribution<int> myDistribution(1.0, 10.0);

    /* The number of eigenvectors and eigenvalues that we will compute will be
        equal to the number of rows in the input matrix. */
    unsigned numRows = inputMatrix.GetNumRow();

    // Create an initial vector, v.
    Vector<T> v(numRows);
    for (unsigned i=0; i<numRows; ++i) v.SetElement(i, static_cast<T>(myDistribution(myRandomGenerator)));

    // Loop over the required number of iterations.
    Vector<T> v1(numRows);
    int numIterations = 1000;
    for (int i=0; i<numIterations; ++i)
    {
        v1 = inputMatrix * v;
        v1.NormalizeIt();
        v = v1;
    }

    // Store this eigenvector.
    eigenVector = v1;



    // Compute the cumulative sum.
    T cumulativeSum = static_cast<T>(0.0);
    for (int i=1; i<numRows; ++i)
        cumulativeSum += inputMatrix.GetElement(0,i) * v1.GetElement(i);

    eigenValue = (cumulativeSum / v1.GetElement(0)) + inputMatrix.GetElement(0,0);

    return SOLUTIONS::DONE;
}


}

#endif //MATH_EIGENVECTOR_HPP
