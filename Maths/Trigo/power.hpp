//
// Created by Benjamin on 04/08/2021.
//

#ifndef MATH_POWER_HPP
#define MATH_POWER_HPP

#include "Trigo.hpp"

namespace Algebra {
    template<typename T>
    constexpr double pow(const double x, const T &a) {
        return Trigo::exp(a * Trigo::log(x));
    }

    template<>
    constexpr double pow<int>(const double x, const int &a) {
        if (x < 0) {
            const int sign = (a % 2 == 0) ? 1 : -1;
            return sign * Trigo::exp(a * Trigo::log(-x));
        } else return Trigo::exp(a * Trigo::log(x));
    }

    template<>
    constexpr double pow<double>(const double x, const double &a) {
        if (x < 0) throw std::invalid_argument("Power function is not defined for x<0 and alpha a real number");
        else return Trigo::exp(a * Trigo::log(x));
    }

}
#endif //MATH_POWER_HPP
