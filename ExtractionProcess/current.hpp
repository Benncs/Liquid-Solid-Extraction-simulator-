#ifndef CURRENT_HPP
#define CURRENT_HPP

#include "./TernaryPlot/Interfaces/Ratios.hpp"

#include "QTextStream"

class Current
{
public:
    Current(double Flow,const Ratios& Ratios);
    Current Mix(const Current& F2)const;
    Current();
    Current(const Current& ToCopy);
    Current(const std::shared_ptr<Current> &ToCopy);

    void operator= (const Current& C);
    bool operator== (const Current& C)const;
    bool operator!= (const Current& C)const;

    const Ratios &getRatios() const;
    double getFlow() const;


private:
    Ratios ratios;
    double Flow;
    static inline bool CloseEnough(double x, double y,double tol=1e-4){
        return std::abs(x-y)<tol;
    }
};

QTextStream &operator <<(QTextStream &outStream, const Current&  current);

#endif // CURRENT_HPP
