//
// Created by Benjamin on 03/08/2021.
//

#ifndef MATH_CALCULUS_HPP
#define MATH_CALCULUS_HPP
#define DX 0.0001

namespace Calculus {

    /** @brief Numerical derivative of a real function
     * @tparam T X with wich We want to compute the derivative F'(X)
     * @tparam F Lambda function that takes as arg a Type ans return T**/
    template<typename T, typename F>
    T derivative(const F &func, const T &Value) {
        return (func(Value + DX) - func(Value - DX)) / (2 * DX);
    }

    /** Computes an numeric integral in [a,b] with trapez method of a real function
     * @param a inf born
     * @param b sup born
     * @param Func Lambda function
     * @tparam F Lambda function that take one arg of J or T type (Cast has to be possible ) and return double**/
    template<typename T, typename J, typename F>
    constexpr double integral(const F &Func, const J &a, const T &b) {
        double min;
        double max;
        if (a < b) {
            min = a;
            max = b;
        } else {
            min = b;
            max = a;
        }
        auto diff = static_cast<double>(max - min);
        const int N = static_cast<int>((1 + diff) / DX);
        auto factor = diff / N;

        double Res = (Func(a) + Func(b)) / 2;
        for (int i = 1; i < N; ++i) {
            Res += Func(min + i * factor);
        }
        return Res * factor;

    }

    /** @brief Newton method to solve f(x)=0 for a real function
     * @param func lambda function, take as arg a double and return double**/
    template<typename F>
    constexpr double Newton(const F &func, const double &init = DX) {
        double res = init;
        double x1;
        double diff = 2 * DX;
        int n = 0;
        while (diff > DX && n < 1000) {
            x1 = res - func(res) / derivative(func, res);
            diff = (x1 < res) ? res - x1 : x1 - res;
            res = x1;
            ++n;
        }
        return res;
    }


}

#endif //MATH_CALCULUS_HPP
