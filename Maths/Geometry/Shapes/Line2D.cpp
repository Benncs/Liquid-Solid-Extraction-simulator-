//
// Created by CASALE Benjamin on 06/10/2021.
//

#include "Line2D.hpp"

namespace Geometry {

    Line2D::Line2D(const Tuple3<double> &Coeffs) {
        this->Coeff = Coeffs;
    }

    Line2D::Line2D() {
        this->Coeff = Tuple3<double>();
    }

    Line2D::Line2D(const Points &point, const LinearAlgebra::Vector<double> &Vec) {
        auto b = -Vec.GetElement(0);
        auto a = Vec.GetElement(1);
        auto c = -(a * point.x() + b * point.y());
        this->Coeff = Tuple3<double>(a, b, c);
    }

    Line2D::Line2D(double a, double b, double c) {
        this->Coeff = Tuple3<double>(a, b, c);
    }

    Line2D::Line2D(double m, double p) {
        this->Coeff = Tuple3<double>(m, -1, p);
    }

    bool Line2D::Contains(const Points &points) const {
        const auto RHS = Coeff.First() * points.x() + Coeff.Second() * points.y() + Coeff.Third();
        return CloseEnough(RHS, 0);
    }

//bool Line2D::CloseEnough(double x, double y, double precision) {
//    return std::abs(x - y) < precision;
//}

    Line2D::Line2D(const Line2D &ToCopy) {

    }

    Points Line2D::Intersection(const Line2D &line) const {
        const auto &CoeffLine2 = line.ToCartesian();

        const double Det = Coeff.First() * CoeffLine2.Second() - Coeff.Second() * CoeffLine2.First();
        if (!CloseEnough(Det, 0)) {
            const double x = (-Coeff.Third() * CoeffLine2.Second() + Coeff.Second() * CoeffLine2.Third()) / Det;
            const double y = (-Coeff.First() * CoeffLine2.Third() + Coeff.Third() * CoeffLine2.First()) / Det;
            return Points(x, y);
        }
        throw std::invalid_argument("No Solution");
    }

    Tuple<double> Line2D::ToLinearForm() const {
        const double m = -Coeff.First() / Coeff.Second();
        const double p = -Coeff.Third() / Coeff.Second();
        return Tuple(m, p);
    }

    LinearAlgebra::Vector<double> Line2D::ToVecAndPoint(Points &point) const {
        point = Points(0, -Coeff.Third() / Coeff.Second());
        return LinearAlgebra::Vector<double>({-Coeff.Second(), Coeff.First()});
    }

    Line2D Line2D::Perpendicular() const {
        auto O = Points(0, -Coeff.Third() / Coeff.Second());
        return Line2D(O, this->Normal());
    }
}

