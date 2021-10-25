#include "TernaryPlotcontroller.hpp"
TernaryPlotController::TernaryPlotController(QWidget *parent):QWidget(parent)
{
    Model = new TernaryPlot();
    Drawer = new TernaryDrawer(this);

    DrawTriangle();
    this->connect(Drawer,&TernaryDrawer::CursorPosition,this, &TernaryPlotController::Position);

}

void TernaryPlotController::DrawLine(const Ratios &Ratio1, const Ratios &Ratio2,const QPen& Pen)const
{
    const Points p1 = Model->RatioToPoint(Ratio1);
    const Points p2 = Model->RatioToPoint(Ratio2);
    Drawer->DrawLine(p1,p2,Pen);
}

void TernaryPlotController::DrawIsotherm(const QPen& Pen)const
{
    auto List = Model->GetPointList();
    auto LastPoint = Model->RatioToPoint(Ratios(0,0,1));
    List.emplace_back(LastPoint);
    std::sort(List.begin(),List.end(),Points::CompareX);
    int size = List.size();
    for(auto i = 0;i<size-1;++i){
        Drawer->DrawLine(List[i],List[i+1],Pen);
    }
}

void TernaryPlotController::AddRatioToIsothermList(const QVector<double> &FirstRatiosList, const QVector<double> &SecondRatiosList, bool percentage) const
{
    for(auto i=0;i<FirstRatiosList.size();++i){
        Model->AddRatioToList(Ratios(FirstRatiosList[i]/100,SecondRatiosList[i]/100));
    }
}

void TernaryPlotController::DrawPoint(const Ratios &Ratio1)const
{
    const Points Point = Model->RatioToPoint(Ratio1);
    Drawer->DrawPoint(Point);
}

void TernaryPlotController::AddConodalToList(const QVector<double> &FirstRatiosList, const QVector<double> &SecondRatiosList,bool percentage) const
{
    int coeff =  (percentage)?100:1;
    for(auto j =0;j<FirstRatiosList.size();++j){
        auto R1 = Ratios(1-FirstRatiosList[j]/coeff,FirstRatiosList[j]/coeff,0);
        auto R2 = Ratios(0,SecondRatiosList[j]/coeff,1-SecondRatiosList[j]/coeff);
        Model->AddConodalsToList(R1,R2);
    }

}

void TernaryPlotController::DrawConodals(const QPen& Pen)const
{
    auto size = Model->GetConodalsListSize();
    Model->SortConodals();

    for(auto index =0;index<size;++index){
        auto Pair = Model->GetConodalsCoordinatesFromList(index);
        Drawer->DrawLine(Pair.I1(),Pair.I2(),Pen);
    }
}

void TernaryPlotController::ConodalsInterpolation(const Ratios &Ratio) const
{
    const auto P1 = Model->RatioToPoint(Ratio);
    Model->SortConodals();
    Model->ConodalInterpolation(P1);

}



void TernaryPlotController::Position(const Points& point){
    QString StringRatio;
    try{
        const Ratios ratio = Model->PointToRatio(point);
        StringRatio = QString("a = %1  \nb = %2  \ns = %3").arg(ratio.A(),0,'f',4).arg(ratio.C(),0,'f',4).arg(ratio.B(),0,'f',4);
        Drawer->SetCursorPosition(StringRatio);
    }
    catch(std::invalid_argument& e){
        StringRatio = QString("a = None  \nb = None  \nc = None");
        Drawer->SetCursorPosition(StringRatio);
    }

}


