#include "current.hpp"
#include <memory>

Current::Current(double Flow,const Ratios& Ratios):ratios(Ratios),Flow(Flow)
{
    //Flow has to be positive
    if(Flow<=0){
        throw std::invalid_argument("Flow value is not correct");
    }
}

Current Current::Mix(const Current &F2) const
{
    //Basically a mass balance : Res = this + F2
    double C = this->Flow+F2.Flow;
    double a = (Flow*ratios.A()+F2.Flow*F2.ratios.A())/C;
    double b = (Flow*ratios.B()+F2.Flow*F2.ratios.B())/C;
    return Current(C,Ratios(a,b));
}

const std::shared_ptr<Current> Current::Mix(const std::shared_ptr<Current> F2) const
{
    //Basically a mass balance : Res = this + F2
    double C = this->Flow+F2->Flow;
    double a = (Flow*ratios.A()+F2->Flow*F2->ratios.A())/C;
    double b = (Flow*ratios.B()+F2->Flow*F2->ratios.B())/C;
    return std::make_shared<Current>(C,Ratios(a,b));
}

Current::Current()
{
    Flow = 0;
    ratios = Ratios(); //Default ratio : xa=xb=xc=-1
}

Current::Current(const Current &ToCopy)
{
    this->Flow = ToCopy.Flow;
    this->ratios = ToCopy.ratios;
}

Current::Current(const std::shared_ptr<Current> &ToCopy)
{
    this->Flow = ToCopy->Flow;
    this->ratios = ToCopy->ratios;
}

void Current::operator=(const Current &C)
{
    ratios = C.ratios;
    Flow = C.Flow;
}

bool Current::operator== (const std::shared_ptr<Current>& C)const{
    bool boolFlow = CloseEnough(Flow,C->Flow);
    bool boolRatios = ratios==C->ratios;
    return boolFlow && boolRatios;
}

bool Current::operator==(const Current &C)const
{
    bool boolFlow = CloseEnough(Flow,C.Flow);
    bool boolRatios = ratios==C.ratios;
    return boolFlow && boolRatios;
}

bool Current::operator!=(const Current &C) const
{
    return !(C==*this);
}

const Ratios &Current::getRatios() const
{
    return ratios;
}

double Current::getFlow() const
{
    return Flow;
}

QTextStream &operator <<(QTextStream &outStream, const Current&  current){
    outStream<<","<<current.getFlow();
    outStream<<","<<current.getRatios();
    return outStream;
}

