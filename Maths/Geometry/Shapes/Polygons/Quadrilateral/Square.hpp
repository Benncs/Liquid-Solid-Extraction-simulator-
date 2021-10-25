//
// Created by CASALE Benjamin on 08/10/2021.
//

#ifndef MATHS2_SQUARE_HPP
#define MATHS2_SQUARE_HPP

#include "Diamond.hpp"
#include "Rectangle.hpp"
namespace Geometry {
    /**
     * Class derived from Polygon (Virtual), diamond and rectangle  that represents a square
     */
    class Square : virtual public Polygon, public Diamond,public Rectangle{
    public:
        /**
         * Constructor, 4 points represented shape's vertexes
         * @param P1 First Point
         * @param P2 Second Point
         * @param P3 Third Point
         * @param P4 Fourth Point
         */
        Square(const Points& P1, const Points& P2, const Points& P3, const Points& P4);

        /**
         * Static Method to check if a polygon is a square, note that subclass of square are considered as squares
         * @param P Polygon to check
         * @return True if polygon is a square
         */
        static bool IsSquare(const std::shared_ptr<Polygon>& D);
    };


}

#endif //MATHS2_SQUARE_HPP
