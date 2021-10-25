#ifndef THEORICALTRAY_HPP
#define THEORICALTRAY_HPP
#include "current.hpp"
#include<cmath>
#include "Maths/Calculus/NewtonN.hpp"
#include "functional"
#include <memory>



struct TrayOutput{
    TrayOutput(const std::shared_ptr<Current>& OF,const std::shared_ptr<Current>& UF,const std::shared_ptr<Current>& M):OperatingPoint(M),Overflow(OF),Underflow(UF){
    }
    TrayOutput()= default;

    void operator= (const TrayOutput& C){
        OperatingPoint = C.OperatingPoint;
        Overflow = C.Overflow;
        Underflow = C.Underflow;
    };

    void operator= (const std::shared_ptr<TrayOutput>& C){
        OperatingPoint = C->OperatingPoint;
        Overflow = C->Overflow;
        Underflow = C->Underflow;
    };

    std::shared_ptr<Current> OperatingPoint;
    std::shared_ptr<Current> Overflow;
    std::shared_ptr<Current> Underflow;
};

class TheoricalTray
{
public:
    TheoricalTray(const std::shared_ptr<Current>& Feed, const std::shared_ptr<Current>& Output);
    TrayOutput Compute();
private:
    const std::shared_ptr<Current> Feed;
    const std::shared_ptr<Current> Output;
    std::shared_ptr<Current> OperatingPoint;
    double SlopeOM;
    Ratios OverFlowRatios;
    Ratios UnderFlowRatios;

    void ComputeOverFlowRatios();
    static inline double UnderFlowFunction(double x){
        return 2.9767*std::pow(x,3)-2.0481*std::pow(x,2)+0.2202*x+0.1711;
    }



};

#endif // THEORICALTRAY_HPP
