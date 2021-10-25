//
// Created by CASALE Benjamin on 09/10/2021.
//

#include "Rectangle.hpp"

Geometry::Rectangle::Rectangle(const Points &P1, const Points &P2, const Points &P3, const Points &P4)
:Polygon(P1,P2,P3,P4), Parallelogram(P1,P2,P3,P4){
    /*Parallelogram constructor is called therefore it's already a parallelogram
     * A rectangle is a parallelogram with 4 right angles */
    bool flag = CheckRightAngles(Vertices);
    if(!flag) throw std::invalid_argument("Square must have 4 right-angles");
    Width = Points::Distance(Vertices[0],Vertices[1]);
    Lenght = Points::Distance(Vertices[1],Vertices[2]);

}

bool Geometry::Rectangle::CheckRightAngles(const std::vector<Points> &Vertexes) {
    //If opposite angles are right => there are 4 angles
    const double Angle = PI/2;
    auto Angle2 = AngleBetween(Vertexes[0],Vertexes[3],Vertexes[1]);
    if(CloseEnough(Angle,Angle2)){
        auto Angle3 = AngleBetween(Vertexes[2],Vertexes[1],Vertexes[3]);
        if(!CloseEnough(Angle3,Angle)){
            return false;
        }
        return true;
    }
    else return false;
}

bool Geometry::Rectangle::IsRectangle(const std::shared_ptr<Polygon>& P) {
    return CheckRightAngles(P->getVertices());
}

