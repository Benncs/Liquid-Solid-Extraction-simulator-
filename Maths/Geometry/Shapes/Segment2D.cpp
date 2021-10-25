//
// Created by CASALE Benjamin on 07/10/2021.
//

#include "Segment2D.hpp"

namespace Geometry {
    Segment2D::Segment2D(const Points &P1, const Points &P2) {
        Borns = Tuple<Points>(P1, P2);
        Lenght = std::sqrt(std::pow(P1.x() - P2.x(), 2) + std::pow(P1.y() - P2.y(), 2));
    }

    Segment2D::Segment2D(const Points &P1, const LinearAlgebra::Vector<double> &V, double lenght) {
        auto Vn = V;
        Vn.NormalizeIt();
        auto P2x = P1.x() + lenght * Vn.GetElement(0);
        auto P2y = P1.y() + lenght * Vn.GetElement(1);
        Borns = Tuple<Points>(P1, Points(P2x, P2y));
        Lenght = lenght;

    }

    double Segment2D::getLenght() const {
        return Lenght;
    }

    const Tuple<Points> &Segment2D::getBorns() const {
        return Borns;
    }

    bool Segment2D::Contains(const Points &points) const {

        auto V2 = Make2PointVec(Borns.First(), points);
        auto V1 = Make2PointVec(Borns.First(), Borns.Second());
        auto scalar = LinearAlgebra::Vector<double>::dot(V1, V2);
        auto Align = Borns.First().Align(Borns.Second(), points);
        if(points==Borns.First()||points==Borns.Second()) return true;
        if (!Align || V2.Norm() > Lenght) return false;
        else return true;


    }

    Line2D Segment2D::ToLine() const {
        auto V = Make2PointVec(Borns.First(), Borns.Second());
        V.NormalizeIt();
        return Line2D(Borns.First(), V);
    }

    bool Segment2D::Intersection(const Segment2D &S, Points &P) const {
        const auto L1 = this->ToLine();
        const auto L2 = S.ToLine();
        auto Res = L1.Intersection(L2);
        if (this->Contains(Res)) {
            P = Res;
            return true;
        } else return false;
    }


}
