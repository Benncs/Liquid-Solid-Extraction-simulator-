//
// Created by CASALE Benjamin on 17/09/2021.
//

#ifndef TERNARYPLOT_POINTS_HPP
#define TERNARYPLOT_POINTS_HPP

#include <ostream>
#include <iostream>

class Points{
    /*!
     * \brief Represents a point in a 2 dimensional context.
    */
public:

    /*!
     * \brief Constructor
     * \param x,y : point's coordinates
    */
    Points(const double x,const double y):Coordx(x),Coordy(y){
    }
    /*!
     * \brief Copy Constructor
     * \param Point to copy
    */
    Points(const Points& Point):Coordx(Point.Coordx),Coordy(Point.Coordy){

    }

    /*!
     * \brief Default constructor
     * \param Nothing
    */
    Points():Coordx(0),Coordy(0){
    }

    /*!
     * \brief x coordinate's getter
     * \return x coordinate
    */
    [[nodiscard]] inline double x() const{return this->Coordx;}

    /*!
     * \brief y coordinate's getter
     * \param y coordinate
    */
    [[nodiscard]] inline double y() const{return this->Coordy;}

    /*!
     * \brief Overload of std operator <<, used with iostrem
    */
    friend std::ostream& operator<<(std::ostream& os,const Points& point) {
        os <<"(" << point.Coordx <<", "<<point.Coordy<<")";
        return os;
    };

    /*!
     * \brief Assign operator overload
     * \param Point to copy
    */
    void operator= (const Points& point){
        Coordx = point.Coordx;
        Coordy = point.Coordy;
    }

    //bool operator<(const Points& b) { return Coordx < b.x(); }

    /*!
     * \brief static function to compare x coordinates of two point
     * \param a,b : Points to compare
    */
    static bool CompareX(const Points&a,const Points& b){ return a.x() < b.x(); }

private:
    double Coordx;
    double Coordy;
};


#endif //TERNARYPLOT_POINTS_HPP
