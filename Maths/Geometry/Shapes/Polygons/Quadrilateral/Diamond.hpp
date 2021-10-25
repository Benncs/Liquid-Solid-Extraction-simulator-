//
// Created by CASALE Benjamin on 08/10/2021.
//

#ifndef MATHS2_DIAMOND_HPP
#define MATHS2_DIAMOND_HPP
#include "../Polygon.hpp"
#include "../../../Tools.hpp"
#include "Parallelogram.hpp"


namespace Geometry {
    /**
     * Class derived from Polygon and parallelogram (Virtual) that represents a Diamond
     */
    class Diamond : public virtual Polygon,public virtual Parallelogram{
    public:
        /**
         * Constructor, 4 points represented shape's vertexes
         * @param P1 First Point
         * @param P2 Second Point
         * @param P3 Third Point
         * @param P4 Fourth Point
         */
        Diamond(const Points& P1, const Points& P2, const Points& P3, const Points& P4);

        /**
         * Static Method to check if a polygon is a diamond, note that subclass of diamond are considered as diamonds
         * @param P Polygon to check
         * @return True if polygon is a diamond
         */
        static bool IsDiamond(const std::shared_ptr<Polygon>& P);

    protected:
        double SideLenght = 0;
        /**
         * Check if 4 polygon's edges have the same lenght
         * @param Vertexes Polygon's vertexes
         * @return true if 4 lenghts are the same
         */
        static bool CheckDistance(const std::vector<Points>& Vertexes);
    };
}


#endif //MATHS2_DIAMOND_HPP
