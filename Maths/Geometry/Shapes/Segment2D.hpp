//
// Created by CASALE Benjamin on 07/10/2021.
//

#ifndef GEOMETRY_SEGMENT2D_HPP
#define GEOMETRY_SEGMENT2D_HPP


#include "Shape.hpp"
#include "Line2D.hpp"
#include "../Tools.hpp"
namespace Geometry {

    class Segment2D : public Shape {
        /**
         * Class that reprensents a segment in 2D with its two borns
         */
    public:
        /**
         * Constructor : Segment between two points
         * @param P1 First End point
         * @param P2 Second End point
         */
        Segment2D(const Points& P1,const Points& P2);

        /**
         * Constructor : Segment from starting point, direction vector and its lenght
         * @param P1 Start point
         * @param V Direction Vector
         * @param lenght Segmenet's lenght
         */
        Segment2D(const Points& P1,const LinearAlgebra::Vector<double>& V, double lenght);

        /**
         * Lenght's getter
         * @return Segment's lenght
         */
        [[nodiscard]] double getLenght() const;

        /**
         * Borns' getter
         * @return Segment's borns
         */
        [[nodiscard]] const Tuple<Points> &getBorns() const;

        /**
         * Check if a point is in the segmenet
         * @param points Point to check
         * @return True if point is inside
         */
        [[nodiscard]] bool Contains(const Points& points) const override;

        /**
         * Give point of intersection between two segments
         * @param S Segment to intersect
         * @param P Point passed as reference => Result
         * @return True if point exists
         */
        [[nodiscard]] bool Intersection(const Segment2D& S, Points& P) const;

        /**
         * Static version of intersection function : Give point of intersection between two segments
         * @param S1 First Segment to intersect
         * @param S2 Second Segment to intersect
         * @param P P Point passed as reference => Result
         * @return True if point exists
         */
        static bool Intersection(const Segment2D& S1,const Segment2D& S2, Points& P){return S1.Intersection(S2,P);};

        /**
         * Convert Segment into line, it's basically an extraction of its direction vector
         * @return Line
         */
        [[nodiscard]] Line2D ToLine()const ;

    private:
        double Lenght;
        Tuple<Points> Borns = Tuple<Points>();
    };

}


#endif //GEOMETRY_SEGMENT2D_HPP
