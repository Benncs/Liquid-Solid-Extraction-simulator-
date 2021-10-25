//
// Created by CASALE Benjamin on 07/10/2021.
//

#ifndef GEOMETRY_CIRCLE_HPP
#define GEOMETRY_CIRCLE_HPP

#include "../Objects/Points.hpp"
#include "cmath"
#include "Shape.hpp"
#include "Segment2D.hpp"

namespace Geometry {

    using Chords = std::vector<Segment2D>;

    class Circle : public Shape {
    public:
        Circle(const Points &P, double rad);
        void AddChord(const Segment2D& S);

        [[nodiscard]] bool OnSurface(const Points &P) const;
        [[nodiscard]] bool Contains(const Points &P) const override;


        [[nodiscard]] double getRadius() const;
        [[nodiscard]] const Points &getCenter() const;
        void GetPointsThroughX(double x, Points& P1, Points& P2)const;
        void GetPointsThroughY(double y, Points& P1, Points& P2)const;
        [[nodiscard]] const Chords &getChords() const;

    private:
        Points center;
        double radius;
        Chords chords;
    };

}
#endif //GEOMETRY_CIRCLE_HPP
