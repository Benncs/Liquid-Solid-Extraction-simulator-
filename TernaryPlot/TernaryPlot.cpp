//
// Created by CASALE Benjamin on 17/09/2021.
//

#include "TernaryPlot.hpp"

TernaryPlot::TernaryPlot(const TriangleType& Type) {
    MainTriangle = TriangleFactory::GetTriangle(Type,&lenght);
    offset = Points(-MainTriangle->Width()/2,-MainTriangle->Height()/2);
    auto FirstRatio = RatioToPoint(Ratios(1,0,0));
    PointList.emplace_back(FirstRatio);
//    VertexMatrix = LinearAlgebra::Matrix<double>(3,3,{MainTriangle->A().x(),MainTriangle->B().x(),MainTriangle->C().x(),
//                                                      MainTriangle->A().y(),MainTriangle->B().y(),MainTriangle->C().y(),
//                                                      1,1,1});
}
#include "QDebug"

#include "Maths/MatrixLib/LinSolve.hpp"

Ratios TernaryPlot::PointToRatio(const Points& point) const {

//    auto B = LinearAlgebra::Vector<double>({point.x(),point.y(),1});

//    auto X = LinearAlgebra::Vector<double>();

//    LinearAlgebra::LinSolve(VertexMatrix,B,X);
//    double a = X.GetElement(0);
//    double b = X.GetElement(1);
//    double c = X.GetElement(2);
//    if(a>0 && b>0&& c>0)
//        return(Ratios(X.GetElement(0),X.GetElement(1),X.GetElement(2)));


    //Manual linear system resolution to avoid using gaussian elination method from MatrixLib
    double a,b,c;

    //Rename variables to have a better code lisibility, it doesn't provide any perfomance loss
    const double Xa = MainTriangle->A().x();
    const double Xb = MainTriangle->B().x();
    const double Xc = MainTriangle->C().x();

    const double Ya = MainTriangle->A().y();
    const double Yb = MainTriangle->B().y();
    const double Yc = MainTriangle->C().y();


    const double NoZero = Xa*(Yc-Yb)+Xb*(Ya-Yc)+Xc*(Yb-Ya);
    if(NoZero!=0){
        a = (Xb*(point.y()-Yc) + Xc*(Yb-point.y()) + point.x()*(Yc-Yb) ) / NoZero;
        b = -(Xa*(point.y()-Yc) + Xc*(Ya-point.y()) + point.x()*(Yc-Ya)) / NoZero;
        c = 1-a-b;
        if(0<=a && 0<=b && 0<=c)
            return Ratios(a,b,c);
    }


    throw std::invalid_argument("Point must be in the triangle");
}

Points TernaryPlot::RatioToPoint(const Ratios &Ratio) const {
    double x2 = MainTriangle->A().x() * Ratio.A() + MainTriangle->B().x()*Ratio.B() + MainTriangle->C().x()*Ratio.C();
    double y2 = MainTriangle->A().y() * Ratio.A() + MainTriangle->B().y()*Ratio.B() + MainTriangle->C().y()*Ratio.C();

    //Assuming a+b+c =1, else formula is x = xB*(2*c+b)/(a+b+c) and y = yB*b
//    double x2 = MainTriangle->B().x()*(2*Ratio.C()+Ratio.B());
//    double y2 = MainTriangle->B().y()*Ratio.B();

    return Points(x2,y2);
}

bool TernaryPlot::AddRatioToList(const Ratios &ratio) {
    try{
        auto ToList = RatioToPoint(ratio);
        this->PointList.emplace_back(ToList);
        return true;
    }
    catch(std::invalid_argument& ){
        return false;
    }
}

bool TernaryPlot::AddConodalsToList(const Ratios &ratio1, const Ratios &ratio2) {
    auto P1 = RatioToPoint(ratio1);
    auto P2 = RatioToPoint(ratio2);
    Conodals.emplace_back(Tuples<Points>(P1,P2));
    return true;
}

Points TernaryPlot::FindIntercept(const Points &Point, bool reverse)
{
    auto Frame = FindFrame(Point,reverse);
    auto Interpolation = LinearInterpolation(Frame);
    return Points((Point.y()-Interpolation.I2())/Interpolation.I1(),Point.y());
}

Tuples<Points> TernaryPlot::GetConodalsCoordinatesFromList(int index)
{
    auto P1 =  FindIntercept(Conodals[index].I1(),false);
    auto P2 = FindIntercept(Conodals[index].I2(),true);

    return Tuples<Points>(P1,P2);
}



#include <algorithm>


void TernaryPlot::SortConodals()
{
    auto sortlambda = [](const PointPair& Pair1,const PointPair& Pair2){
        return Pair1.I1().y()<Pair2.I1().y();};

    std::sort(Conodals.begin(),Conodals.end(),sortlambda);
}



Tuples<double> TernaryPlot::LinearInterpolation(const Tuples<Points> &Frame) {
    double slope,intercept;
    slope = (Frame.I1().y()-Frame.I2().y())/(Frame.I1().x()-Frame.I2().x());
    intercept = (Frame.I1().x() * Frame.I2().y() - Frame.I1().y() * Frame.I2().x()) / (Frame.I1().x() - Frame.I2().x());
    return Tuples<double>(slope,intercept);
}

#include <QVector>

Tuples<Points> TernaryPlot::FindFrame(const Points &Point, bool reverse) const{
    const auto size = PointList.size();
    const double y = Point.y();
    auto Copy = PointList;

    if(!reverse){
        std::sort(Copy.begin(),Copy.end(),Points::CompareX);
    }
    else {
        std::sort(Copy.rbegin(),Copy.rend(),Points::CompareX);

    }

    unsigned index = 0;
    while(index<size){
        if(Copy[index].y()>y){
            return Tuples<Points>(Copy[index-1],Copy[index]);
        }
        index++;
    }
    throw std::runtime_error("Frame not found");

}




Tuples<Tuples<Points>> TernaryPlot::ConodalsFraming(const Points &Point)const {
    const auto size = PointList.size();
    unsigned index = 0;
    while(index<size){
        if(Conodals[index].I2().y()>Point.y()){
            auto P1 = Conodals[index];
            auto P2 = Conodals[index+1];
            return Tuples<PointPair>(P1,P2);
        }
        index++;
    }
    throw std::runtime_error("Frame not found");
}


double TernaryPlot::FindR(const Points &Point, const Tuples<PointPair> &Pairs)const {
    auto FirstLine = LinearInterpolation(Pairs.I1());
    auto SecondLine = LinearInterpolation(Pairs.I2());
    const double y1 = FirstLine.I1()*Point.x()+FirstLine.I2();
    const double y2 = SecondLine.I1()*Point.x()+SecondLine.I2();
    return std::sqrt(std::pow(y1-Point.y(),2)/std::pow(y2-Point.y(),2));
}

void TernaryPlot::ConodalInterpolation(const Points &point)
{
    const Tuples<PointPair> Frame = ConodalsFraming(point);
    const double R = FindR(point,Frame);
    const Points A = Points(Frame.I1().I1().y(),Frame.I1().I2().y());
    const Points B = Points(Frame.I2().I1().y(),Frame.I2().I2().y());

    const auto Xz = R*(B.x()-A.x())+A.x();
    const auto Yz = R*(B.y()-A.y())+A.y();
    const Points Zx = Points(Xz,Yz);
    const Points Zy = Points(Yz,Xz);

    auto InterpolatedConodal1 = FindIntercept(Zy,false);

    auto InterpolatedConodal2 = FindIntercept(Zx,true);

    Conodals.emplace_back(PointPair(InterpolatedConodal1,InterpolatedConodal2));


}
