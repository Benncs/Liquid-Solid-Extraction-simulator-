//
// Created by CASALE Benjamin on 08/10/2021.
//

#include "Diamond.hpp"
#include <iostream>
Geometry::Diamond::Diamond(const Points &P1, const Points &P2, const Points &P3, const Points &P4)
: Polygon(P1, P2, P3, P4), Parallelogram(P1,P2,P3,P4) {
    /*A diamond is a parallelogram with its 4 edges of the same lenght */
    if(!CheckDistance(Vertices)) throw std::invalid_argument("Segments must have the same lenght");
    SideLenght = Points::Distance(Vertices[3],Vertices[0]);;
//    Perimeter = 4*Points::Distance(Vertices[3],Vertices[0]);;
//    auto Angle = Geometry::AngleBetween(Vertices[0],Vertices[1],Vertices[Dim-1],Math::ANGLE::RAD);
//    Area = std::pow(SideLenght,2)*std::sin(Angle);
}

bool Geometry::Diamond::CheckDistance(const std::vector<Points>& Vertexes){
    //Loop thought every edges
    const auto D1 =Points::Distance(Vertexes[3],Vertexes[0]);
    for(auto i = 0;i<Vertexes.size()-1;++i){
        auto D2 = Points::Distance(Vertexes[i],Vertexes[i+1]);
        if(!CloseEnough(D1,D2)){
            return false;
        }
    }
    return true;
}

bool Geometry::Diamond::IsDiamond(const std::shared_ptr<Polygon>& P) {
    return CheckDistance(P->getVertices());
}







