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
    /**
     * @class TernaryPlot
     * Represent a ternary diagram
     * Contains every useful method to add information to a ternary plot
     */
public:
    TernaryPlot(const TriangleType& Type = TriangleType::RECTANGLE);


    /**
     * @brief Convert a point in cartesian coordinates  into a ratio (trilinear coordinates)
     * @param point to convert
     * @return Ratios
     */
    [[nodiscard]] Ratios PointToRatio(const Points& point) const;

    /**
     * @brief onvert a ratio (trilinear coordinates) into a point in cartesian coordinates
     * @param Ratio to convert
     * @return Point
     */
    [[nodiscard]] Points RatioToPoint(const Ratios& Ratio) const;


    /**
     * @brief PointsList's const getter
     * @return PointsList
     */
    [[nodiscard]] std::vector<Points> PointsList()const{return PointList;}


    /**
     * @brief AddRatioToList
     * @param ratio ratio to add
     * @return true if ratios correctly added
     */
    bool AddRatioToList(const Ratios& ratio);

    /**
     * @brief AddConodalsToList
     * @param ratio1 first conodal point to add
     * @param ratio2 second  conodal point to add
     * @return true if ratios correctly added
     */
    bool AddConodalsToList(const Ratios& ratio1,const Ratios& ratio2);


    /**
     * @brief Conodals list's size const getter
     * @return size of conodals list
     */
    int GetConodalsListSize()const{return Conodals.size();};


    /**
     * @brief Triangle's const getter
     * @return Main triangle of the ternary plot
     */
    std::shared_ptr<Triangle> GetTriangle()const{return MainTriangle;};


    /**
     * @brief Point list's const getter
     * @return Point list
     */
    std::vector<Points> GetPointList()const{return PointList;};

    /**
     * @brief GetConodalsPairsOfPoint const getter
     * @return Conodals
     */
    std::vector<Tuples<Points>> GetConodalsPairsOfPoint()const{return Conodals;};


    /**
     * @brief FindIntercept between 2 line represent as discontinute points in the points list
     * @param Point absissa of point
     * @param reverse (start at the end of the point list )
     * @return interpolated point
     */
    Points FindIntercept(const Points& Point,bool reverse=false);

    /**
     * @brief GetConodalsCoordinatesFromList
     * @param index
     * @return
     */
    PointPair GetConodalsCoordinatesFromList(int index);

    /**
     * @brief ConodalInterpolation
     * @param point
     */
    void ConodalInterpolation(const Points& point);


    /**
     * @brief SortConodals
     */
    void SortConodals();


private:
    std::shared_ptr<Triangle> MainTriangle;
    Points offset;
    const double lenght = 1;
    std::vector<Points> PointList;
    std::vector<PointPair> Conodals;
    bool ShownIsotherm = false;
    /**
     * @brief LinearInterpolation
     * @param Frame, tuple of point between which the point is located
     * @return
     */
    static Tuples<double> LinearInterpolation(const Tuples<Points>& Frame);

    //LinearAlgebra::Matrix<double> VertexMatrix;

    [[nodiscard]] Tuples<Points> FindFrame(const Points& Point,bool reverse=false)const;
    [[nodiscard]] Tuples<Tuples<Points>> ConodalsFraming(const Points& Point) const ;
    [[nodiscard]] double FindR(const Points& Point,const Tuples<PointPair>& Pairs)const;
};


#endif //TERNARYPLOT_TERNARYPLOT_HPP
