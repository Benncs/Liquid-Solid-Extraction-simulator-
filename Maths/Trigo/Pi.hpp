//
// Created by Benjamin on 03/08/2021.
//

#ifndef MATH_PI_HPP
#define MATH_PI_HPP


template<int I, int J>
struct pi_calc
{
    inline static double value ()
    {
        return (pi_calc<I-1, J>::value () + pi_calc<I-1, J+1>::value ()) / 2.0;
    }
};

template<int J>
struct pi_calc<0, J>
{
    inline static double value ()
    {
        int sign = (J%2==0)?1:-1;
        return ( sign* 4.0) / (2.0 * J + 1.0) + pi_calc<0, J-1>::value ();
    }
};


template<>
struct pi_calc<0, 0>
{
    inline static double value ()
    {
        return 4.0;
    }
};

template<int I>
struct pi
{
    constexpr inline static double value ()
    {
        return pi_calc<I, I>::value ();
    }
};

#endif //MATH_PI_HPP
