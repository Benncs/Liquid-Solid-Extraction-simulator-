

// Copyright (c) Made by CASALE Benjamin on 10/11/ 2021
// Scientific purpose
//

//
// Created by CASALE Benjamin on 09/10/2021.
//



#ifndef MATHS2_PARALLELOGRAM_HPP
#define MATHS2_PARALLELOGRAM_HPP
#include "../Polygon.hpp"
#include "../../../Tools.hpp"
namespace Geometry {
    class Parallelogram : public virtual Polygon{
        /**
         * Class derived from Polygon (Virtual) that represents a parallelogram
         */

    public:
        /**
         * Constructor, 4 points represented shape's vertexes
         * @param P1 First Point
         * @param P2 Second Point
         * @param P3 Third Point
         * @param P4 Fourth Point
         */
        Parallelogram(const Points& P1, const Points& P2, const Points& P3, const Points& P4);

        /**
         * Getter of the first vertex
         * @return First vertex
         */
        [[nodiscard]] inline const Points& A()const {return Vertices[0];}

        /**
         * Getter of the second vertex
         * @return Second vertex
         */
        [[nodiscard]] inline const Points& B()const {return Vertices[1];}

        /**
         * Getter of the third vertex
         * @return Third vertex
         */
        [[nodiscard]] inline const Points& C()const {return Vertices[2];}

        /**
         * Getter of the fourth vertex
         * @return Fourth vertex
         */
        [[nodiscard]] inline const Points& D()const {return Vertices[3];}

        /**
         * Parallelogram's width getter
         * @return Width
         */
        [[nodiscard]] inline double getWidth() const {return Width;}

        /**
         * Parallelogram's lenght getter
         * @return Lenght
         */
        [[nodiscard]] inline double getLenght() const {return Lenght;}

        /**
         * Parallelogram's height getter
         * @return Height
         */
        [[nodiscard]] inline double getHeight() const {return Height;}


        /**
         * Static Method to check if a polygon is a parallelogram, note that subclass of parallelogram are considered as parallelogram
         * @param P Polygon to check
         * @return True if polygon is a parallelogram
         */
        static inline bool IsParallelogram(const std::shared_ptr<Polygon> &P) {
            return Check(P->getVertices());
        }


    private:
        /**
         * Check if a 4 point make a parallelogram
         * @param Vertexes Polygon's vertex
         * @return True if it's a parallelogram
         */
        static bool Check(const std::vector<Points>& Vertexes);



    protected:
        double Width;
        double Lenght;
        double Height;
    };


}


#endif //MATHS2_PARALLELOGRAM_HPP
