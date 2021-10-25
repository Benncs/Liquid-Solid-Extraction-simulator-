//
// Created by CASALE Benjamin on 17/09/2021.
//

#ifndef TERNARYPLOT_THREETUPLE_HPP
#define TERNARYPLOT_THREETUPLE_HPP
#include <QTextStream>

class ThreeTuple{
    /*!
     * \brief  Class to store 3 number as a 3-tuple
     *
    */
public:
    /*!
     * \brief  Constructor
     * \param a,b,c : 3-tuple's components
    */
    ThreeTuple(double a,double b,double c){
        this->a = a;
        this->b = b;
        this->c = c;
    }

    /*!
     * \brief First element's getter
     * \return First element
    */
    [[nodiscard]] inline double A()const{return a;}
    /*!
     * \brief  Second element's getter
     * \return  Second element
    */
    [[nodiscard]] inline double B()const{return b;}

    /*!
     * \brief Third element's getter
     * \return  Third element
    */
    [[nodiscard]] inline double C()const{return c;}

    friend std::ostream& operator<<(std::ostream& os,const ThreeTuple& tuple){
        os <<"(" << tuple.a <<", "<<tuple.b<<", "<<tuple.c<<")";
        return os;
    };


    friend QTextStream &operator <<(QTextStream &outStream, const ThreeTuple&  tuple){
        outStream<< tuple.a <<", "<<tuple.b<<", "<<tuple.c;
        return outStream;
    }

protected:
    double a,b,c;
};




#endif //TERNARYPLOT_THREETUPLE_HPP
