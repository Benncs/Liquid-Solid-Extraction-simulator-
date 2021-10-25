//
// Created by CASALE Benjamin on 06/10/2021.
//

#include "Points.hpp"

namespace Geometry {

    Points::Points() : coordX(0), coordY(0), coordZ(0) {
        //Default assignation
    }

    Points::Points(double X, double Y, double Z) : coordX(X), coordY(Y), coordZ(Z) {
        //Default assignation
    }

//    Points::Points(Points &Point) {
//        this->coordX = Point.x();
//        this->coordY = Point.y();
//        this->coordZ = Point.z();
//    }

    Points::Points(const Points &points) {
        //Copy elements
        this->coordX = points.x();
        this->coordY = points.y();
        this->coordZ = points.z();
    }

    double Points::Distance(const Points &P2) const {
        //By pythagoras theorem, d=sqrt((x-xo)^2+(y-yo)&^2+(z-z0)^2))
        auto x = std::pow(coordX - P2.x(), 2);
        auto y = std::pow(coordY - P2.y(), 2);
        auto z = std::pow(coordZ - P2.z(), 2);
        return std::sqrt(x + y + z);
    }

    bool Points::Align(const Points &P2, const Points &P3) const {
        /*For (x,y) in R3 not null, <x,y>=||x||*||y||*cos(alpha)
         If <x,y>/(||x||*||y||) = 1 => cos(alpha)=1 => alpha = 0 + 2k*pi
        Therefore there is no angle between vector thus they are aligned*/

        //Create Vectors
        auto V1 = LinearAlgebra::Vector<double>({P2.coordX - coordX, P2.coordY - coordY, P2.coordZ - coordZ});
        auto V2 = LinearAlgebra::Vector<double>({P3.coordX - coordX, P3.coordY - coordY, P3.coordZ - coordZ});

        auto scalar = LinearAlgebra::Vector<double>::dot(V1, V2); //<x,y>
        auto Q = scalar / (V1.Norm() * V2.Norm()); //Cos(alpha)
        return CloseEnough(std::abs(Q), 1);
    }

    bool Points::Aligned(const Points &P1, const Points &P2, const Points &P3) {
//        auto V1 = Math::Vector<double>({P2.coordX - P1.coordX, P2.coordY - P1.coordY, P2.coordZ - P1.coordZ});
//        auto V2 = Math::Vector<double>({P3.coordX - P1.coordX, P3.coordY - P1.coordY, P3.coordZ - P1.coordZ});
//        auto scalar = Math::Vector<double>::dot(V1, V2);
//        auto Q = scalar / (V1.Norm() * V2.Norm());
//        return CloseEnough(std::abs(Q), 1);
         return P1.Align(P2,P3);
    }

    double Points::Distance(const Points &P1, const Points &P2) {
//        auto x = std::pow(P1.coordX - P2.coordX, 2);
//        auto y = std::pow(P1.coordY - P2.coordY, 2);
//        auto z = std::pow(P2.coordZ - P2.coordZ, 2);
//        return std::sqrt(x + y + z);
    return P1.Distance(P2);
    }

    bool Points::operator==(const Points &rhs) const {
        //Check 3 coordinates
        return CloseEnough(coordX, rhs.coordX) &&
               CloseEnough(coordY, rhs.coordY) &&
               CloseEnough(coordZ, rhs.coordZ);
    }

    bool Points::operator!=(const Points &rhs) const {
        return !(rhs == *this);
    }

    Points::Points(int a) {
        coordZ = a;
        coordY = a;
        coordX = a;

    }

    std::ostream &operator<<(std::ostream &os, const Points &point) {
        os << "(" << point.coordX << ", " << point.coordY << ", " << point.coordZ << ")";
        return os;
    };

}

