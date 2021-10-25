#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Triangle.hpp"
#include <cmath>

class Rectangle : public Triangle{
    /*!
     * \brief Derived class from triangle, represent a equilateral triangle
    */
public:
    /*!
     * \brief Constructor
     * \param Triangle's side lenght
    */
    explicit Rectangle(double lenght): Triangle(){
        //Coordinates are represents in a cartesian axis where A is at the origin, B the triangle's peak and C is the other base point
        //Therefore, each coordinates of the triangle are positive and it can be easily transposed in other coordinates system
        this->VertexA = Points(0,0);
        this->VertexC = Points(0,lenght);
        this->VertexB = Points(lenght,0);
        this->height = lenght;
        this->width = lenght;
        Type = TriangleType::RECTANGLE;

    }
};


#endif // RECTANGLE_HPP
