//
// Created by CASALE Benjamin on 07/10/2021.
//

#include "Circle.hpp"

namespace Geometry{

Circle::Circle(const Points &P, double rad) : center(P), radius(rad), Shape() {

}

bool Circle::OnSurface(const Points &P) const {
    auto x = std::pow(P.x() - center.x(), 2) + std::pow(P.y() - center.y(), 2) - std::pow(radius, 2);
    return CloseEnough(x, 0);
}

bool Circle::Contains(const Points &P) const {
    auto x = std::pow(P.x() - center.x(), 2) + std::pow(P.y() - center.y(), 2) - std::pow(radius, 2);
    return x <= 0;
}

const Points &Circle::getCenter() const {
    return center;
}

double Circle::getRadius() const {
    return radius;
}

void Circle::AddChord(const Segment2D &S) {
    const auto& Born = S.getBorns();
    if (!this->Contains(Born.Second())|| (!this->Contains(Born.First()))){
        throw std::invalid_argument("Segment borns is not on the circle");
    }
    else{
        chords.emplace_back(S);
    }
}

    const Chords &Circle::getChords() const {
        return chords;
    }

       void Circle::GetPointsThroughX(double x, Points& P1, Points& P2) const{
        if(center.x()-radius>x || x>center.x()+radius){
//        if(std::abs(center.x()+radius)<std::abs(x)){
            throw std::invalid_argument("No point on the circle with this x");
        }
        auto dx = std::pow(this->center.x()-x,2);
        auto sqrt = std::sqrt(std::pow(radius,2)-dx);
        auto y = center.y()-sqrt;
        auto y2 = center.y()+sqrt;
        P1 = {x,y};
        P2 = {x,y2};
    }
    void Circle::GetPointsThroughY(double y, Points &P1, Points &P2) const {
        if(center.y()-radius>y || y>center.y()+radius){
            throw std::invalid_argument("No point on the circle with this y");
        }
        auto dx = std::pow(this->center.y()-y,2);
        auto sqrt = std::sqrt(std::pow(radius,2)-dx);
        auto x = center.x()-sqrt;
        auto x2 = center.x()+sqrt;
        P1 = {x,y};
        P2 = {x2,y};
    }

}