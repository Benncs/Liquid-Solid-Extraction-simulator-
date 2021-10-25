//
// Created by CASALE Benjamin on 07/10/2021.
//

#include "Tools.hpp"

namespace Geometry {
    double AngleBetween(const LinearAlgebra::Vector<double>& V1,const LinearAlgebra::Vector<double>& V2,Trigo::ANGLE angle){
        // For (x,y) into R3, <x,y>=||x||*||y||*cos(alpha)
        //=> alpha = arccos(<x,y>/(||x||*||y||))
        auto scalar = LinearAlgebra::Vector<double>::dot(V1,V2); //Compute <x,y>
        auto cos = scalar/(V2.Norm()*V1.Norm()); //Compute cos(alpha)
        auto acos = std::acos(cos); //Compute alpha
        //Convertion into DEG if needed
        if(angle==Trigo::ANGLE::RAD) return acos;
        else return Trigo::Rad_To_Deg(acos);
    }

    double AngleBetween(const Line2D &L1, const Line2D &L2, Trigo::ANGLE angle) {
        auto O = Points(); //We don't need this points but it's need by ToVecAndPoint function

        auto V1 = L1.ToVecAndPoint(O); //Get direction vector of line 1
        auto V2 = L2.ToVecAndPoint(O); //Get direction vector of line 2
        return AngleBetween(V1, V2, angle);
    }

    double AngleBetween(const Points& P1,const Points& P2,const Points& P3,Trigo::ANGLE angle){
        //Make vector P1P2 and P1P3. Angle P1P2P3 is the angle betwen the two vectors
        auto V1 = Make2PointVec(P1,P2);
        auto V2 = Make2PointVec(P1,P3);
        return AngleBetween(V1,V2,angle);
    }

    Tuple3<double> Deg_To_Deg_Min_Sec(const double& angle_deg){
        int integer = static_cast<int>(angle_deg);
        int m = static_cast<int>((angle_deg-integer)*60);
        double s = (angle_deg-integer-m/60.)*3600;
        return Tuple3<double>(integer,m,s);
    }

    LinearAlgebra::Vector<double> Make2PointVec(const Points& P1, const Points& P2){
        auto x = P1.x()-P2.x();
        auto y = P1.y()-P2.y();
        auto z = P1.z() - P2.z();
        return LinearAlgebra::Vector<double>({x,y,z});
    }




}