//
// Created by CASALE Benjamin on 08/10/2021.
//

#include "Polygon.hpp"

namespace Geometry{
    Polygon::Polygon(const std::vector<Points> &PointList) {
        if (Vertices.size()<3){
            throw std::invalid_argument("3 Points minimum are needed");
        }
        Vertices = PointList;
        Dim = 2+static_cast<int>(Vertices.size());
    }

    double Polygon::getArea()const {
        return Area;
    }

    double Polygon::getPerimeter()const  {
        return Perimeter ;
    }

    Polygon::Polygon() {
        Dim = 0;
        Vertices = {};
    }

    Polygon::Polygon(const Polygon &p) {
        Dim = p.Dim;
        Vertices = p.Vertices;
    }



    const std::vector<Points> &Polygon::getVertices() const {
        return Vertices;
    }

    bool Polygon::Contains(const Points &P) const {
        //Semi-Line/Segment intersection, check if the result is in the segment
        //If odd number point is inside, otherwise outside
        //Works with any polygon ( convex,conex ...) and with any lines
        std::vector<Segment2D> Edges; //Vector that will store every edges of the polygon
        Edges.reserve(Dim);
        for(auto i=0;i<Dim-1;++i){
            //Pushing every edges made from consecutive points
            Edges.emplace_back(Segment2D(Vertices[i], Vertices[i + 1]));
        }

        Edges.emplace_back(Segment2D(Vertices[Dim - 1], Vertices[0])); //Push last edges to "close" the shape


        unsigned count =0; //Number of intersection
        //Horizontal line that will intersect edges
        const auto line = Line2D(P,LinearAlgebra::Vector<double>({1,0}));
        for(auto& inter: Edges){
            //Try catch to avoid "No solution" case
            try{
                auto InterPoint = line.Intersection(inter.ToLine()); //Compute intersections
                //TO Simulated semi line, only res with abscissa bigger than the point of counted
                if(inter.Contains(InterPoint) && InterPoint.x()>P.x() ) count++;
            }
            catch (...){
            }
        }
        if(count%2==0) return false; //If odd number -> False
        else return true;
    }

    bool Polygon::operator==(const Polygon &rhs) const {
        //Check everything being carefull with double type (CloseEnough function)
        if(Dim!=rhs.Dim || !CloseEnough(rhs.Area,Area) || !CloseEnough(Perimeter,rhs.Perimeter)) return false;
        else {
            for (auto i = 0; i < Dim; ++i) {
                for (auto j = 0; j < Dim; ++i) {
                    if (i != j && Vertices[i] != Vertices[j]) return false;
                }
            }
            return true;
        }
    }

    bool Polygon::operator!=(const Polygon &rhs) const {
        return !(rhs == *this);
    }


}