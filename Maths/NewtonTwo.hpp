//
// Created by Benjamin on 07/08/2021.
//

#ifndef MATH_NEWTONTWO_HPP
#define MATH_NEWTONTWO_HPP

#define TOL 1e-8
#define LOOPMAX 100
#include "Maths/Calculus/calculus.hpp"
#include "Maths/MatrixLib/Matrix.hpp"

namespace Calculus {

    template<typename F>
    double Derivative2(const F &func, bool fisrtarg) {
        return (fisrtarg) ? (func(DX) - func(-DX)) / (2 * DX) : (func(0, DX) - func(0, -DX)) / (2 * DX);
    }

    template<typename T, typename G>
    auto NewtonMatrix(const T &FirstEquation, const G &SecondEquation, double xinit = 0, double yint = 0) {
        auto *x = new double(xinit), *y = new double(yint);

        auto X = new LinearAlgebra::Vector<double>({*x, *y});


        auto f = [&X, &FirstEquation](double dx = 0, double dy = 0) {
            double x = X->GetElement(0) + dx;
            double y = X->GetElement(1) + dy;
            return FirstEquation(x, y);
        };

        auto g = [&X, &SecondEquation](double dx = 0, double dy = 0) {
            double x = X->GetElement(0) + dx;
            double y = X->GetElement(1) + dy;
            return SecondEquation(x, y);
        };


        std::vector<double> Jacob{
                Derivative2(f, true), Derivative2(f, false),
                Derivative2(g, true), Derivative2(g, false)
        };

        LinearAlgebra::Matrix<double> J(2, 2, Jacob);

        LinearAlgebra::Vector<double> F({1, 1, 1});

        // LinearAlgebra::Vector<double>Dx;

        unsigned count = 0;
        while (count < LOOPMAX && F.Norm() >= TOL) {

            Jacob = {
                    Derivative2(f, true), Derivative2(f, false),
                    Derivative2(g, true), Derivative2(g, false)
            };

            J = LinearAlgebra::Matrix<double>(2, 2, Jacob);
            if (J.Inverse() == LinearAlgebra::SOLUTIONS::NO_INVERSE) throw Exceptions(2, "No Solution", 0);

            F = LinearAlgebra::Vector<double>({-f(), -g()});

//        LinearAlgebra::LinSolveQR(J,F,Dx);
//        *X = *X + Dx;

            *X = *X + J * F;
            ++count;
        }
        auto Res = *X;

        delete x;
        delete y;
        delete X;
        return Res;


    }

    constexpr double fp(double x, double y) {
        return 2 * x + 3 * y + 8;
    };

    constexpr double gp(double x, double y) {
        return x * x * x - 2 * y - 7;
    };

}



#endif //MATH_NEWTONTWO_HPP
