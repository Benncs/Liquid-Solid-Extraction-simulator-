//
// Created by CASALE Benjamin on 06/10/2021.
//

#ifndef GEOMETRY_LINE2D_HPP
#define GEOMETRY_LINE2D_HPP


#include "Shape.hpp"
#include "../Objects/Tuple.hpp"
#include "../Objects/ThreeTuple.hpp"
namespace Geometry {
    class Shape;

    class Line2D : public Shape {
    public:
        Line2D();

        Line2D(const Line2D &ToCopy);

        Line2D(const Points &point, const LinearAlgebra::Vector<double> &Vec);

        Line2D(double m, double p);

        Line2D(double a, double b, double c);

        explicit Line2D(const Tuple3<double> &Coeffs);

        [[nodiscard]] bool Contains(const Points &points) const override;

        [[nodiscard]] const Tuple3<double> &ToCartesian() const { return Coeff; };

        [[nodiscard]] Points Intersection(const Line2D &line) const;

        [[nodiscard]] Tuple<double> ToLinearForm() const;

        LinearAlgebra::Vector<double> ToVecAndPoint(Points &point) const;

        [[nodiscard]] LinearAlgebra::Vector<double> Normal() const {
            return LinearAlgebra::Vector<double>({Coeff.First(), Coeff.Second()});
        };

        [[nodiscard]] Line2D Perpendicular() const;


    private:
        Tuple3<double> Coeff;
    };

}
#endif //GEOMETRY_LINE2D_HPP
