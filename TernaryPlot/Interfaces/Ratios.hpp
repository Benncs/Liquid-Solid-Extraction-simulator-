//
// Created by CASALE Benjamin on 17/09/2021.
//

#ifndef TERNARYPLOT_RATIOS_HPP
#define TERNARYPLOT_RATIOS_HPP
#include "ThreeTuple.hpp"

class Ratios: public ThreeTuple{
    /*!
     * \brief Derived class from THreeTuple, use in chemical context for constituant's fraction.
     * Therefore sum of all the 3  ratio's componenent is equal to 1
    */
public:
    /*!
     * \brief Constructor
     * \param a,b,c the three ratio component are optionals, mimum 2 fractions are needed
    */
    explicit Ratios(double a= -1,double b= -1,double c= -1);

    bool operator== (const Ratios& R)const;

private:
    static inline bool CloseEnough(double x, double y,double tol=1e-4){
        return std::abs(x-y)<tol;
    }

};




#endif //TERNARYPLOT_RATIOS_HPP
