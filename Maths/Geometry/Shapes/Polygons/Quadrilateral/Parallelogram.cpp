//
// Created by CASALE Benjamin on 09/10/2021.
//

#include "Parallelogram.hpp"

Geometry::Parallelogram::Parallelogram(const Points &P1, const Points &P2, const Points &P3, const Points &P4) :
Polygon(P1,P2,P3,P4) {


    /*
     * Firstly, check if every points are differents
     * */
    for(auto i = 0 ;i<Dim;++i){
        for(auto j = 0 ;j<Dim;++j){
            if(Vertices[i]==Vertices[j] && i!=j) throw std::invalid_argument("Points must be distincts");
        }
    }

    /*
     * Secondly, a quadrilateral ABCD is a parallelogram if vector AB= DC
     * However we don't know a priori if points are given in a specific order of note, thus we check the points 2 by 2
     * THere is 3 cases
     * 1: if we have ab=dc -> fine
     * 2 : if ab=-dc -> a permutation of point a and b and we have case 1
     * 3 : ab!=dc or ab != dc, a permutation of a and c and we have either case 1 either 2
     * We put this in a condition loop while case 1 is not achieved.
     * With 24 points there are 24 permutations thus if loop iteration exceed 24 : it cannot be a paralelogram.
     * */

    auto V1 = Make2PointVec(Vertices[0], Vertices[1]); //Vector ab
    auto V2 = Make2PointVec(Vertices[3], Vertices[2]); //Vector cd
    bool flag = V1 == V2; // Check case 1
    unsigned it = 0; //Loop iteration
    // if not case 1
    while (!flag) {
        //Check case 2
        if (V1 == -1. * V2) {
            Vertices = {P2, P1, P3, P4}; //Permutation
            break;
        } else {
            //Case 3
            Vertices = {P1, P3, P2, P4}; //Permutation
        }
        //Update vector
        V1 = Make2PointVec(Vertices[0], Vertices[1]);
        V2 = Make2PointVec(Vertices[3], Vertices[2]);
        it++;
        if(it>24) throw std::invalid_argument("Not a parallelogram");
        flag = V1 == V2; //Check case 1
    }
    //Width or lenght can be inverted
    Width = Points::Distance(Vertices[0], Vertices[1]);
    Lenght = Points::Distance(Vertices[3], Vertices[0]);
    Perimeter = 2 * (Width + Lenght);
    V1 = Make2PointVec(Vertices[0], Vertices[1]);
    V2 = Make2PointVec(Vertices[0], Vertices[3]);
    //Area of a parallelogram is AB^AC where AB and AC are two vectors
    Area = (LinearAlgebra::Vector<double>::cross(V1, V2)).Norm();
    Height = Area/Lenght; //Area = height*lenght

}

bool Geometry::Parallelogram::Check(const std::vector<Points> &Vertexes) {
    /*
     * Firstly, check if every points are differents, cf constructor
     * */
    for(auto i = 0 ;i<Vertexes.size();++i){
        for(auto j = 0 ;j<Vertexes.size();++j){
            if(Vertexes[i]==Vertexes[j] && i!=j) return false;
        }
    }

    auto V1 = Make2PointVec(Vertexes[0], Vertexes[1]);
    auto V2 = Make2PointVec(Vertexes[3], Vertexes[2]);
    return V1==V2;

}





