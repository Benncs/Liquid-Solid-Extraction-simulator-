//
// Created by CASALE Benjamin on 17/09/2021.
//

#ifndef TERNARYPLOT_EQUILATERAL_HPP
#define TERNARYPLOT_EQUILATERAL_HPP

#include "Triangle.hpp"
#include <cmath>

class Equilateral : public Triangle{
    /*!
     * \brief Derived class from triangle, represent a equilateral triangle
    */
public:
    /*!
     * \brief Constructor
     * \param Triangle's side lenght
    */
    explicit Equilateral(double lenght): Triangle(){
        //Coordinates are represents in a cartesian axis where A is at the origin, B the triangle's peak and C is the other base point
        //Therefore, each coordinates of the triangle are positive and it can be easily transposed in other coordinates system
        this->VertexA = Points(0,0);
        this->VertexB = Points(lenght/2,lenght*std::sqrt(3)/2);
        this->VertexC = Points(lenght,0);
        this->height = std::sqrt(3)/2*lenght;
        this->width = lenght;
        Type = TriangleType::EQUILATERAL;

    }
};

#endif //TERNARYPLOT_EQUILATERAL_HPP
