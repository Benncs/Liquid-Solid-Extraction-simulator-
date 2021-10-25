//
// Created by Benjamin on 04/08/2021.
//

#ifndef MATH_SEQUENCE_HPP
#define MATH_SEQUENCE_HPP


/** @brief Namespace to group functions that compute sequences**/
namespace Sequence {


    template<typename T, typename J, typename F>

    struct RecurSequence {
        /** @brief Interface to easily pass 2n order sequences to fonction,
     * Repesent two sequences of the form of : Un+2=F(N)*Un+1+J(N)*Un+cst_val
     * @tparam F First lambda  function that take an unsigned int which represents the index n, must return T type
     * @tparam J Second lambda function that take an unsigned int which represents the index n, must return T type
     * @tparam T type of U0 and U1 as well as the constant
     *   **/
        RecurSequence(const F &func, const J &func2, const T &u0, const T &u1, const T &cst_val = 0) :
                functor_un(func), functor_un1(func2), U0(u0), U1(u1), cst(cst_val) {};

        F functor_un;
        J functor_un1;
        T U0;
        T U1;
        T cst;
    };

    /**@brief computes a first order sequence as Un+1=F(N)*Un+cst
     * @tparam T type of Result, U0 and return type of F
     * @tparam F Lambda  function that take an unsigned int which represents the index n, must return T type**/
    template<class T, class F>
    constexpr static inline T
    Recur(const T &u0, const F &func, unsigned int count = 10, const T &cst = 0){
        if (count == 0) return u0;
        else return func(count) * Recur(u0, func, count - 1, cst) + cst;

    };

    /**@brief computes a Second order sequence as Un+2=F(N)*Un+1+J(N)*Un+cst_val
     * @tparam T type of Result, U0 and return type of F
     * @tparam F First lambda  function that take an unsigned int which represents the index n, must return T type
     * @tparam J Second lambda function that take an unsigned int which represents the index n, must return T type
     * @tparam n Index N to compute **/
    template<unsigned n, typename F, typename J, typename T>
    constexpr static inline double SecondOrderRecur(const RecurSequence<F, J, T> &Sequence){
        double Vec[n + 2];
        unsigned int i;
        Vec[0] = Sequence.U0;
        Vec[1] = Sequence.U1;
        for (i = 2; i <= n; i++) {
            Vec[i] = Sequence.functor_un1(i) * Vec[i - 1] + Sequence.functor_un(i) * Vec[i - 2];
        }
        return Vec[n];
    }


}

#endif //MATH_SEQUENCE_HPP
