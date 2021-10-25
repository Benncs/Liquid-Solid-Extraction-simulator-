//
// Created by CASALE Benjamin on 07/10/2021.
//

#ifndef GEOMETRY_TOOLS_HPP
#define GEOMETRY_TOOLS_HPP

#include "Shapes/Line2D.hpp"
#include "../Trigo/Trigo.hpp"
namespace Geometry{
    /**
     * Returns angle between two lines
     * @param L1 First Line
     * @param L2 Second Line
     * @param angle Angle Unit
     * @return Angle between two line
     */
    double AngleBetween(const Line2D& L1,const Line2D& L2,Trigo::ANGLE angle = Trigo::ANGLE::RAD);
    /**
     * Returns angle between two Vectors
     * @param V1 First Vector
     * @param V2 Second Vector
     * @param angle Angle Unit
     * @return Angle between two vectors
     */
    double AngleBetween(const LinearAlgebra::Vector<double>& V1,const LinearAlgebra::Vector<double>& V2,Trigo::ANGLE angle = Trigo::ANGLE::RAD);
    /**
     * Returns angle formed by 3 points
     * @param P1 First Point
     * @param P2 Second Point
     * @param P3 Third Point
     * @param angle Angle Unit
     * @return Angle between two lines
     */
    double AngleBetween(const Points& P1,const Points& P2,const Points& P3,Trigo::ANGLE angle = Trigo::ANGLE::RAD);
    /**
     * Convert Deg in decimal into Deg+Min+sec
     * @param angle_deg Angle Unit
     * @return Converted Angle
     */
    Tuple3<double> Deg_To_Deg_Min_Sec(const double& angle_deg);
    /**
     * Create a 3D Euclidian's Vector. Vector formula used in geometry
     * @param P1 Point 1
     * @param P2 Point 2
     * @return 3D Vector
     */
    LinearAlgebra::Vector<double> Make2PointVec(const Points& P1, const Points& P2);

}

#endif //GEOMETRY_TOOLS_HPP
