//
// Created by CASALE Benjamin on 17/09/2021.
//

#include "Ratios.hpp"

Ratios::Ratios(const double a, const double b, const double c) : ThreeTuple(a,b,c){
    if(a!=-1){
        if(b==-1 and c!=-1){
            this->b = 1-a-c;
        }
        else if(c==-1 and b!=-1){
            this->c = 1 - b-a;
        }
        else if(c!=-1){
            if(!CloseEnough(a+b+c,1)) throw std::invalid_argument("Ratio sum must be equal to 1 ");
        }
        else{
            throw std::invalid_argument("Ratio sum must be equal to 1 ");
        }
    }
    else{
        if(c!=-1 and b!=-1){
            this->a = 1-b-c;
        }
    }


}

bool Ratios::operator==(const Ratios &R)const
{
    bool boolXa = CloseEnough(this->a,R.a);
    bool boolXb = CloseEnough(this->b,R.b);
    bool boolXc = CloseEnough(this->c,R.c);
    return boolXa && boolXb && boolXc;
}

bool Ratios::IsValid() const
{
    if(a<0 || b<0 || c<0 || a>1 || b>1|| c>1){
        return false;
    }
    return true;
}
