//
// Created by CASALE Benjamin on 17/09/2021.
//

#include "Triangle.hpp"

bool Triangle::Contains(const Points &points) const {

    double side1 = (points.x() - VertexB.x()) * (VertexA.y() - VertexB.y()) -
                   (VertexA.x() - VertexB.x()) * (points.y() - VertexB.y());
    double side2 = (points.x() - VertexC.x()) * (VertexB.y() - VertexC.y()) -
                   (VertexB.x() - VertexC.x()) * (points.y() - VertexC.y());
    double side3 = (points.x() - VertexA.x()) * (VertexC.y() - VertexA.y()) -
                   (VertexC.x() - VertexA.x()) * (points.y() - VertexA.y());
    return (((side1 > 0.0) == (side2 > 0.0)) == (side3 > 0.0));


//    double amx = points.x()-VertexA.x();
//    double amy = points.y()-VertexA.y();

//    double abx = VertexB.x()-VertexA.x();
//    double aby = VertexB.y()-VertexA.y();

//    double acx = VertexC.x()-VertexA.x();
//    double acy = VertexC.y()-VertexA.y();

//    double p1 =(amx*acy)-(acx*amy)/(abx*acy-acx*aby);

    return true ;
}

TriangleType Triangle::getType() const
{
    return Type;
};

