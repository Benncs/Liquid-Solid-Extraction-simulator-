//
// Created by CASALE Benjamin on 06/10/2021.
//

#ifndef GEOMETRY_POINTS_HPP
#define GEOMETRY_POINTS_HPP

#include "ostream"
#include "../../MatrixLib/Vector.hpp"
#include <cmath>

namespace Geometry {

    class Points {
        /**
         * Class that represents a point in R3 with 3 coordinates
         */
    public:

        //Constructors
        /**
         * Default Constructor, init coord with 0
         */
        Points();

        /**
         * Constructor
         * @param X Coordinate X
         * @param Y Coordinate Y
         * @param Z Coordinate Z (Default is 0)
         */
        Points(double X, double Y, double Z = 0);
        /**
         * Copy Constructor
         * @param Point Point to Copy
         */
        //Points(Points &Point);
        /**
         * Constructor 2, init coords with the same value
         * @param a coordinates value
         */
        explicit Points(int a);

        /**
         * Copy Constructor
         * @param points
         */
        Points(const Points &points);

        //Getters
        /**
         * Coord x getter
         * @return X Coordinates
         */
        [[nodiscard]] inline double x() const { return this->coordX; }

        /**
         * Coord y getter
         * @return Y Coordinates
         */
        [[nodiscard]] inline double y() const { return this->coordY; }

        /**
         * Coord z getter
         * @return Z Coordinates
         */
        [[nodiscard]] inline double z() const { return this->coordZ; }

        //Tool
        /**
         * Test if 2 points are aligned with this point
         * @param P2 Second point
         * @param P3 Third point
         * @return True if 3 points are aligned, else false
         */
        [[nodiscard]] bool Align(const Points &P2, const Points &P3) const;

        /**
         * Get the distance between this point and another point
         * @param P2 The other point
         * @return Distance between points
         */
        [[nodiscard]] double Distance(const Points &P2) const;

        //Statics
        /**
         * Static method to get distance between two points
         * @param P1 First Point
         * @param P2 Second Point
         * @return Distance between points
         */
        static double Distance(const Points &P1, const Points &P2);

        /**
         * Static method to check if 3 points are aligned
         * @param P1 First Point
         * @param P2 Second Point
         * @param P3 Third Point
         * @return True if they are aligned else false
         */
        static bool Aligned(const Points &P1, const Points &P2, const Points &P3);
        //Overload

        /**
         * Overload of assigment statement (=)
         * @param RHS Right-Hand side Point
         * @return Point
         */
        Points &operator=(const Points &RHS) = default;

        /**
         * Overload of equality condition (==)
         * @param rhs Righ-Hand Side Point
         * @return True if Point are the same
         */
        bool operator==(const Points &rhs) const;

        /**
         * Overload of non equality condition (!=)
         * @param rhs Righ-Hand Side Point
         * @return if Point are different
         */
        bool operator!=(const Points &rhs) const;

        /**
         * Overload of stream statement (<<), use with std::cout
         * @param os steam
         * @param point Point to put in steam
         * @return stream with point informations
         */
        friend std::ostream &operator<<(std::ostream &os, const Points &point);

    private:
        /**
         * Coordinates
         */
        double coordX, coordY, coordZ;

        /**
         * Static method to check equality between double to avoid decimal approximation
         * @param x first decimal point
         * @param y Second decimal point
         * @param precision Approximation precision
         * @return true if they point are equal
         */
        static bool CloseEnough(double x, double y, double precision = 1e-4) { return std::abs(x - y) < precision; };

    };
}


#endif //GEOMETRY_POINTS_HPP
