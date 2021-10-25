//
// Created by CASALE Benjamin on 07/10/2021.
//

#ifndef MATH2_SHAPE_HPP
#define MATH2_SHAPE_HPP

#include "../Objects/Points.hpp"
#include <memory>


namespace Geometry {

    class Shape {
        /**
         * Abstract class that represents a geometrical object as line/circle/polygons ecc
         */
    protected:
        /**
         * Constructor
         */
        constexpr Shape() = default;

        /**
         * Static method needed by every subclass to check equality between double to avoid decimal approximation
         * @param x first decimal point
         * @param y Second decimal point
         * @param precision Approximation precision
         * @return true if they point are equal
         */
        static bool CloseEnough(double x, double y, double precision = 1e-4) { return std::abs(x - y) < precision; };

        /**
         * Virtual function to check if a point is inside a shape
         * @param P Point to check
         * @return true if point is inside
         */
        [[nodiscard]] virtual bool Contains(const Points &P) const = 0;
    };

}


#endif //MATH2_SHAPE_HPP
