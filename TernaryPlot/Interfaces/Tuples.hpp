//
// Created by CASALE Benjamin on 17/09/2021.
//

#ifndef TERNARYPLOT_TUPLES_HPP
#define TERNARYPLOT_TUPLES_HPP

#include "iostream"

template<typename T>
class Tuples {
    /*!
    @brief : Template class to store 2 object in a pair
    */

public:
    /*!
     * \brief Constructor
     * \param FirstItem Pair's first element
     * \param SecondItem Pair's second element
    */
    Tuples(const T& FirstItem,const T& SecondItem):Item1(FirstItem),Item2(SecondItem){

    }
    /*!
     * \brief First element getter
     * \return template T type
    */
    inline T I1()const {return Item1;}


    /*!
     * \brief Second element getter
     * \return template T type
    */
    inline T I2()const{return Item2;}


    /*!
     * \brief Overload of std operator <<, used with iostrem
    */
    template<typename S>
    friend std::ostream& operator<<(std::ostream& os,const Tuples<S>& tuple);

private:
    T Item1;
    T Item2;
};

template<typename S>
std::ostream &operator<<(std::ostream &os, const Tuples<S> &tuple) {
    // If << is available for template type
    try{
        os <<"(" << tuple.Item1 <<", "<<tuple.Item2<<")"<<std::endl;
        return os;
    }
    // If not just show class' name
    catch(...){
        os << "Tuples";//"Tuple of "<< typeid(S).name();
        return os;
    }
};


#endif //TERNARYPLOT_TUPLES_HPP
