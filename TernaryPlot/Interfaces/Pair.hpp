//
// Created by CASALE Benjamin on 17/09/2021.
//

#ifndef TERNARYPLOT_PAIR_HPP
#define TERNARYPLOT_PAIR_HPP
#include "Points.hpp"
class Pair{
public:
    Pair(const Points& point1,const Points& point2 ){
        Point1 = point1;
        Point2 = point2;
    }

    [[nodiscard]] inline Points P1() const {return this->Point1;}
    [[nodiscard]] inline Points P2() const {return this->Point2;}

    friend std::ostream& operator<<(std::ostream& os,const Pair& pair){
        os <<"(" << pair.Point1 <<", "<<pair.Point2<<")"<<std::endl;
        return os;
    };


private:
    Points Point1;
    Points Point2;
};


#endif //TERNARYPLOT_PAIR_HPP
