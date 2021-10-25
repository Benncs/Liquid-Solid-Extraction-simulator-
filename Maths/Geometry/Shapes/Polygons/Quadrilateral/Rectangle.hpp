//
// Created by CASALE Benjamin on 09/10/2021.
//

#ifndef MATHS2_RECTANGLE_HPP
#define MATHS2_RECTANGLE_HPP
#include "../Polygon.hpp"
#include "../../../Tools.hpp"
#include "Parallelogram.hpp"
namespace Geometry {
    /**
     * Class derived from Polygon and parallelogram (Virtual) that represents a rectangle
     */
    class Rectangle : public virtual Polygon ,public virtual Parallelogram{
    public:
        /**
         * Constructor from 4 points
         * @param P1 First point
         * @param P2 Second Point
         * @param P3 Third Point
         * @param P4 Fourth Point
         */
        Rectangle(const Points& P1, const Points& P2, const Points& P3, const Points& P4);

        /**
         * Static Method to check if a polygon is a Rectangle, note that subclass of rectangle are considered as rectangles
         * @param P Polygon to check
         * @return True if polygon is a rectangle
         */
        static bool IsRectangle(const std::shared_ptr<Polygon>& P);

    protected:
        /**
         * Static method to check if the 4 angles are right angles
         * @param Vertexes Polygon's vertexes
         * @return true if there are 4 right angles
         */
        static bool CheckRightAngles(const std::vector<Points>& Vertexes);
    };
}


#endif //MATHS2_RECTANGLE_HPP
