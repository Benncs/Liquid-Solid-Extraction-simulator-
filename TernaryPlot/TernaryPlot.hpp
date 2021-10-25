//
// Created by CASALE Benjamin on 17/09/2021.
//

#ifndef TERNARYPLOT_TERNARYPLOT_HPP
#define TERNARYPLOT_TERNARYPLOT_HPP
#include "Triangles/Triangle.hpp"
#include "Triangles/TriangleFabric.hpp"

#include <vector>
//#include "Interfaces/Pair.hpp"
#include "Interfaces/Ratios.hpp"
#include "Interfaces/Tuples.hpp"
#include <exception>
#include <algorithm>
#include "Maths/MatrixLib/LinSolve.hpp"


using PointPair = Tuples<Points>;


class TernaryPlot {
public:
    TernaryPlot(const TriangleType& Type = TriangleType::RECTANGLE);

    [[nodiscard]] Ratios PointToRatio(const Points& point) const;
    [[nodiscard]] Points RatioToPoint(const Ratios& Ratio) const;

    [[nodiscard]] std::vector<Points> PointsList()const{return PointList;}

    bool AddRatioToList(const Ratios& ratio);
    bool AddConodalsToList(const Ratios& ratio1,const Ratios& ratio2);

    int GetConodalsListSize()const{return Conodals.size();};

    std::shared_ptr<Triangle> GetTriangle()const{return MainTriangle;};


    std::vector<Points> GetPointList()const{return PointList;};


    std::vector<Tuples<Points>> GetConodalsPairsOfPoint()const{return Conodals;};

    Points FindIntercept(const Points& Point,bool reverse=false);

    PointPair GetConodalsCoordinatesFromList(int index);
    void ConodalInterpolation(const Points& point);


    void SortConodals();


private:
    std::shared_ptr<Triangle> MainTriangle;
    Points offset;
    const double lenght = 1;
    std::vector<Points> PointList;
    std::vector<PointPair> Conodals;
    bool ShownIsotherm = false;
    static Tuples<double> LinearInterpolation(const Tuples<Points>& Frame);

    //LinearAlgebra::Matrix<double> VertexMatrix;

    [[nodiscard]] Tuples<Points> FindFrame(const Points& Point,bool reverse=false)const;
    [[nodiscard]] Tuples<Tuples<Points>> ConodalsFraming(const Points& Point) const ;
    [[nodiscard]] double FindR(const Points& Point,const Tuples<PointPair>& Pairs)const;
};


#endif //TERNARYPLOT_TERNARYPLOT_HPP
