#ifndef THEORICALTRAY_HPP
#define THEORICALTRAY_HPP
#include "current.hpp"
#include<cmath>
#include "Maths/Calculus/NewtonN.hpp"
#include "functional"
#include <memory>



struct TrayOutput{
    /**
     * @struct Result of one theoretical tray
     * @param OF Tray's Overflow
     * @param UF Tray's Underflow
     * @param M Tray's Operating point
     */
    TrayOutput(const std::shared_ptr<Current>& OF,const std::shared_ptr<Current>& UF,const std::shared_ptr<Current>& M):OperatingPoint(M),Overflow(OF),Underflow(UF){
    }

    /**
     * @brief Default constructor
     */
    TrayOutput()= default;

    /**
     * @brief Asign operator overload
     * @param C Object to asign as ref
     */
    void operator= (const TrayOutput& C){
        OperatingPoint = C.OperatingPoint;
        Overflow = C.Overflow;
        Underflow = C.Underflow;
    };

    /**
     * @brief Asign operator overload
     * @param C Object to asign as share ptr
     */
    void operator= (const std::shared_ptr<TrayOutput>& C){
        OperatingPoint = C->OperatingPoint;
        Overflow = C->Overflow;
        Underflow = C->Underflow;
    };

    //Member
    std::shared_ptr<Current> OperatingPoint;
    std::shared_ptr<Current> Overflow;
    std::shared_ptr<Current> Underflow;
};

class TheoreticalTray
{
    /**
     * @class that represents a theoretical tray of a liquid-solid extraction process (as open system) at counter-current
     */
public:
    /**
     * @brief Main Constructor
     * @param Feed First input (with solid to extract)
     * @param SolventFeed (Solvent)
     */
    TheoreticalTray(const std::shared_ptr<Current>& Feed, const std::shared_ptr<Current>& SolventFeed);

    /**
     * @brief Main method
     * Simulate one process' tray
     * @return
     */
    TrayOutput Compute();

    /**
     * @brief static method
     * Represent Underflow limit's (polymonial regression)
     * @param x represent first current component (Xa)
     * @return double that represent Xb (solid)
     */
    static inline double UnderFlowFunction(double x){
        return 2.9767*std::pow(x,3)-2.0481*std::pow(x,2)+0.2202*x+0.1711;
    }


private:
    const std::shared_ptr<Current> WithSolidFeed;
    const std::shared_ptr<Current> SolventFeed;
    std::shared_ptr<Current> OperatingPoint;
    double SlopeOM;
    Ratios OverFlowRatios;
    Ratios UnderFlowRatios;

    /**
     * @brief Compute Overflow composition
     */
    void ComputeOverFlowRatios();




};

#endif // THEORICALTRAY_HPP
