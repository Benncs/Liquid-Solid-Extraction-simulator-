//
// Created by Benjamin on 04/08/2021.
//

#include "Maths/Sequence.hpp"


//template<unsigned N>
//double recur(const double& u0,const double& u1){
//    return (double)5*recur<N-2>(u0,u1)+recur<N-1>(u0,u1);
//}
//
//template<>
//double recur<1>(const double& u0,const double& u1){
//    return u1;
//}
//
//template<>
//double recur<0>(const double& u0,const double& u1){
//    return u0;
//}


// template<typename T,typename F,typename J>static constexpr double Recur2order(const RecurSequence<T,F,J>& Sequence, const  unsigned& count = 10);

//template<typename T,typename F,typename J>
//constexpr double Sequence::Recur2order(const RecurSequence<T,F,J>& Sequence, const  unsigned& count ){
//    if(0==count) return Sequence.U0;
//    if(1==count) return Sequence.U1;
//    else
//        return (double)Sequence.functor_un(count) * Recur2order(Sequence, count - 2) + Sequence.functor_un1(count) *Recur2order(Sequence,count - 1) + Sequence.cst;
//}

//template<class T,class F,class J>static constexpr double DoubleRecur(const RecurSequence<T,F,J>& Sequence,const unsigned int & n,const unsigned int& init = 0,const T& cst = 0);

//template<class T, class F, class J>
//constexpr double Sequence::DoubleRecur(const RecurSequence<T, F,J> &Sequence,const unsigned int & n, const unsigned int &init, const T &cst) {
//    auto un=static_cast<double>(Sequence.U0);
//    auto un1=static_cast<double>(Sequence.U1);
//    double un2;
//    double temp;
//    for (unsigned int i = init; i < n-1; ++i) {
//        un2= Sequence.functor_un(i) * un1 + Sequence.functor_un1(i) * un + cst;
//        temp=un2;
//        un=un1;
//        un1=temp;
//    }
//    return un2;
//}