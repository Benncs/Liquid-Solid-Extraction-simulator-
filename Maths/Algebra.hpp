//
// Created by Benjamin on 03/08/2021.
//

#ifndef MATH_ALGEBRA_HPP
#define MATH_ALGEBRA_HPP

#include "Trigo/Trigo.hpp"
#include "exception"
#include "Trigo/power.hpp"


namespace Algebra{

    template<int value,unsigned int N>
    struct Pow{
        constexpr static const double Res = value*Pow<value,N-1>::Res;
    };

    template<int value>
    struct Pow<value,1>{
        constexpr static const double Res = value;
    };

    constexpr double sqrt(const double& value){
        if(value<0) throw std::invalid_argument("Diamond root is not defined for x<0");
        double res = DX;
        double temp =0 ;
        double diff = 2*DX;
        while (diff > DX){
            temp = 0.5*(res + value / res);
            diff = (temp < res) ? res - temp : temp - res;
            res = temp;
        }
        return res;
    }

    template<typename T>
    constexpr inline T abs(const T& val){
        return static_cast<T>(sqrt(pow(val,2.0)));
    }

}
#endif //MATH_ALGEBRA_HPP
