//
// Created by Benjamin on 08/08/2021.
//

#ifndef MATH_NEWTONN_HPP
#define MATH_NEWTONN_HPP



#define TOL 1e-8
#define LOOPMAX 100

#include "calculus.hpp"
#include "../MatrixLib/Matrix.hpp"
#include <complex>

/** This is an example of how use NewtonN function, to solve system **/

//
//void NewtonComp(){
//    using namespace std::complex_literals;
//
//    auto Init = InitVector(0.+1i,0.+1i,0.+0i);
//
//
//    auto X = new LinearAlgebra::Vector<std::complex<double>>(Init);
//
//    std::function<std::complex<double>()> F = [&X]() {
//        auto x = X->GetElement(0);
//        auto y = X->GetElement(1);
//        auto z = X->GetElement(2);
//        return 2.*x+3.*y+8.;
//    };
//    std::function<std::complex<double>()> G = [&X]() {
//        auto x = X->GetElement(0);
//        auto y = X->GetElement(1);
//        auto z = X->GetElement(2);
//        return x*x*x-2.*y-7.;
//    };
//    std::function<std::complex<double>()> H = [&X]() {
//        auto x = X->GetElement(0);
//        auto y = X->GetElement(1);
//        auto z = X->GetElement(2);
//        return 8.*x+y+z;
//    };
//
//
//    Math::NewtonN(X,std::move(F),std::move(G),std::move(H));
//
//    Show(*X);
//
//    std::cout<<"F: ";
//    Show(F());
//    std::cout<<"G: ";
//    Show(G());
//    std::cout<<"H: ";
//    Show(H());
//
//    delete X;
//}

template<class ...Arg>
std::vector<std::complex<double>> InitVector(const Arg&& ... arg){
    const auto dim = sizeof ...(arg);
    std::vector<std::complex<double>> Res;
    Res.reserve(dim);

    for(auto&& i : {arg...}){
        Res.template emplace_back(i);
    }
    return Res;
}

namespace Calculus {

    template<typename T, class ...FuncArg>
    class NewtonN {
    public:

        explicit NewtonN(LinearAlgebra::Vector<T> *X, FuncArg &&... Funcs);

        LinearAlgebra::Matrix<T> Jacobian(LinearAlgebra::Vector<T> *X, const FuncArg &... funcs);

    private:
        [[nodiscard]] inline std::vector<T> VectorGenerator(unsigned param) const {
            std::vector<T> Res;
            Res.reserve(param);
            for (unsigned i = 0; i < param; ++i) Res.template emplace_back(1);
            return Res;
        }

        template<typename F>
        T DerivativeN(LinearAlgebra::Vector<T> *V, const F &func, unsigned argNumber) const;

        template<class U>
        inline double ComplexModule(std::complex<U> N) const {
            return sqrt(N.real() * N.real() + N.imag() * N.imag());
        }


        template<class U>
        inline double Norm(const LinearAlgebra::Vector<U> &Vector) const {
            return Vector.Norm();
        }

        template<class U>
        inline double Norm(const LinearAlgebra::Vector<std::complex<U>> &Vector) const {
            double CumSum = 0;
            for (auto i = 0; i < Vector.GetDim(); ++i) {
                CumSum += ComplexModule(Vector.GetElement(i)) * ComplexModule(Vector.GetElement(i));
            }
            return sqrt(CumSum);
        }

    };


    template<typename T, class... FuncArg>
    NewtonN<T, FuncArg...>::NewtonN(LinearAlgebra::Vector<T> *X, FuncArg &&... Funcs) {
        const auto dim = sizeof...(Funcs);

        LinearAlgebra::Matrix<T> J;
        LinearAlgebra::Vector<T> F(VectorGenerator(dim));
        //LinearAlgebra::Vector<T>Dx;

        unsigned count = 0;
        while (count < LOOPMAX && Norm(F) >= TOL) {
            std::vector<T> functions;
            functions.reserve(dim);
            for (auto &&fun : {Funcs...}) functions.template emplace_back(-fun());

            J = Jacobian(X, Funcs...);
            if (J.Inverse() == LinearAlgebra::SOLUTIONS::NO_INVERSE) throw Exceptions(2, "No Solution", 0);
            F = LinearAlgebra::Vector<T>(functions);

            //LinearAlgebra::LinSolveQR(J,F,Dx);
            //*X = *X + Dx;

            *X = *X + J * F;
            ++count;
        }
        if (count == LOOPMAX) throw Exceptions(4, "NewtonN :Iteration", 0);

    }


    /** Compute partial derivative for a vectorial function
     * @param V Vector of unknows
     * @param func lambda function that returns and takes T type
     * @param argNumber Select partial derivative that is needed
     * @example : f(x,y,z) -> [&V]f(), y-Derivative : DerivativeN(V,f,1)  **/
    template<typename T, class... FuncArg>
    template<typename F>
    T NewtonN<T, FuncArg...>::DerivativeN(LinearAlgebra::Vector<T> *V, const F &func,
                                          const unsigned int argNumber) const {
        if (argNumber > V->GetDim()) throw std::invalid_argument("DerivativeN : Dim Error ");
        const auto old = V->GetElement(argNumber);
        V->SetElement(argNumber, old + DX);
        const auto FDx = func();
        V->SetElement(argNumber, old - DX);
        const auto mFDx = func();
        V->SetElement(argNumber, old);
        return (FDx - mFDx) / (2 * DX);
    }


    /** Compute Jacobian function for a vectorial function
     * return square matrix with partial derivative of T type
     * @param X vector of unknowns
     * @param funcs Variadic that represent partial function
     * @example for F(f(x,y),g(x,y)) -> [&V]f(),[&V]g() call : Jacobian(V,f,g)**/
    template<typename T, class... FuncArg>
    LinearAlgebra::Matrix<T>
    NewtonN<T, FuncArg...>::Jacobian(LinearAlgebra::Vector<T> *X, const FuncArg &... funcs) {
        const auto Dim = X->GetDim();
        constexpr std::size_t n = sizeof...(funcs);
        if (n != Dim) throw Exceptions(3, "Jacobian : different dim and number of arg");
        std::vector<T> Res;
        Res.reserve(Dim);

        for (auto &&func :{funcs...}) {
            for (unsigned Row = 0; Row < Dim; ++Row) {
                Res.template emplace_back(DerivativeN(X, func, Row));
            }
        }
        return LinearAlgebra::Matrix<T>(Dim, Dim, Res);;
    }
}

#endif //MATH_NEWTONN_HPP
