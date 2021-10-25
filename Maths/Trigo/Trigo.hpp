//
// Created by Benjamin on 03/08/2021.
//

#ifndef MATH_TRIGO_HPP
#define MATH_TRIGO_HPP

#include "../Calculus/calculus.hpp"
#include "Pi.hpp"

#define LOOP 50
#define LOOP_EXP 100
#define LOOP_LOG_N 1000
#define LOOP_LOG 1000000
#define PI pi<10>::value()


namespace Trigo {

    enum class ANGLE{
        RAD,
        DEG
    };

    constexpr double cos(const double x) {

        unsigned int a = 2;
        unsigned int b = 1;
        double iterm = 1;
        double res = iterm;
        for (int i = 1; i < LOOP + 1; ++i) {
            iterm *= -(x * x) / (a * b);
            a += 2;
            b += 2;
            res += iterm;
        }
        return res;
    }

    constexpr double sin(const double x) {
        unsigned int a = 1;
        unsigned int b = 0;
        double iterm = x;
        double res = iterm;

        for (int i = 1; i < LOOP + 1; ++i) {
            a += 2;
            b += 2;
            iterm *= -(x * x) / (a * b);
            res += iterm;
        }
        return res;

    }

    constexpr double tan(const double x) {

        unsigned int k = 2;

        double icos = 1; // divided by 0!;
        double isin = x; // divided by 1!;

        double rescos = icos;
        double ressin = isin;

        double temp = 0;
        while (k < 2 * LOOP) {

            temp = -(x * x) / k;

            icos *= temp / (k - 1);

            isin *= temp / (k + 1);

            k += 2;

            rescos += icos;
            ressin += isin;

        }
        return ressin / rescos;
    }

    constexpr double exp(const double x) {
        double temp = 1;
        double res = 1;
        for (unsigned int i = 1; i < LOOP_EXP; ++i) {
            temp *= x / i;
            res += temp;
        }
        return res;
    }

    template<unsigned int x>
    constexpr double logn() {
        const auto diff = static_cast<double>(x - 1) / LOOP_LOG_N;

        double Res = ((double) x + 1) / (2 * x);
        for (unsigned int i = 1; i < LOOP_LOG_N; ++i) {
            Res += 1 / (1 + i * diff);
        }
        return Res * (diff);

    }

    constexpr double log(const double x) {
        if(x<=0) throw std::invalid_argument("Logarithm is not defined for x<=0");
        const auto diff = static_cast<double>(x - 1) / LOOP_LOG;

        double Res = ((double) x + 1) / (2 * x);
        for (int i = 1; i < LOOP_LOG; ++i) {
            Res += 1 / (1 + i * diff);
        }
        return Res * (diff);

    }

    constexpr inline double Deg_To_Rad(const double& angle_deg){
        return PI*angle_deg/180;
    }

    constexpr inline double Rad_To_Deg(const double& angle_rad){
        return 180*angle_rad/PI;
    }

#define ln10 Trigo::logn<10>()
#define ln2 Trigo::logn<2>()

}


#endif //MATH_TRIGO_HPP
