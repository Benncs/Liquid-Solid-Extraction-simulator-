//
// Created by CASALE Benjamin on 08/10/2021.
//

#include "Square.hpp"

Geometry::Square::Square(const Points &P1, const Points &P2, const Points &P3, const Points &P4) :
Polygon(P1,P2,P3,P4),Parallelogram(P1,P2,P3,P4) ,Rectangle(P1, P2, P3,P4),Diamond(P1, P2, P3,P4){
    //If polygon is a the time a rectangle and a diamond = > it's a square
}

bool Geometry::Square::IsSquare(const std::shared_ptr<Polygon>& D) {
    //Check if it's a diamond ( check distance ) and a rectangle (right angles)
    const auto& Vertexes = D->getVertices();
    if(CheckDistance(Vertexes)) {
        if (CheckRightAngles(Vertexes)) {
            return true;
        } else return false;
    }
    else return false;

}



//bool Geometry::Square::IsSquare(const Geometry::Diamond &D) {
//    return CheckRightAngles(D.getVertices());
//}



