//
// Created by CASALE Benjamin on 08/10/2021.
//

#ifndef MATHS2_POLYGON_HPP
#define MATHS2_POLYGON_HPP
#include <vector>
#include "../../Objects/Points.hpp"
#include "../Shape.hpp"
#include "../Segment2D.hpp"


namespace Geometry {
    /**
     * Class Derived from Shape, represents geometrical polygon with the list of its vertexes.
     */
    class Polygon : public virtual Shape {
    public:
        //Getters
        /**
         * Polygon's perimeter
         * @return Perimeter
         */
        [[nodiscard]] double getPerimeter()const ;

        /**
         * Polygon's Area
         * @return Area
         */
        [[nodiscard]] double getArea()const;

        /**
         * Get list of polygon's vertexes
         * @return vector of vertexes
         */
        [[nodiscard]] const std::vector<Points> &getVertices() const;

        /**
         * Number of edges
         * @return Polygon's number of edges
         */
        [[nodiscard]] inline int getDim() const{return Dim;};
        //OVerrides
        /**
         * Check if a point is included into the polygon's area (its edges are included)
         * @param P Point to check
         * @return True if the point is inside
         */
        [[nodiscard]] bool Contains(const Points &P) const override ;

        /**
         * Overload of equality statement, check : dim , perimeter, area and vertexes
         * @param rhs Polygon to check
         * @return True if every components are the same
         */
        bool operator==(const Polygon &rhs) const;

        /**
         * Overload of equality statement, check : dim , perimeter, area and vertexes
         * @param rhs Polygon to check
         * @return False if every components are the same
         */
        bool operator!=(const Polygon &rhs) const;


    protected:
        //Constructors
        /**
         * General construct, 3 points that represent vertexes are needed at least to form a polygon.
         * @tparam T Points
         * @param P1 First point
         * @param P2 Second point
         * @param Ps Other points ( variadic argument therefore it's an undefined number of arguments)
         */
        template<typename ...T>
        explicit Polygon(const Points &P1,const Points &P2, T &&... Ps);
        /**
         * Default constructor, create a void polygon
         */
        Polygon();
        /**
         * Copy Constructor
         * @param Polygon to copy
         */
        Polygon(const Polygon& p);
        /**
         * Constructor from a vector of point
         * @param PointList Polygons vertexes
         */
        explicit Polygon(const std::vector<Points> &PointList);




    protected:
        std::vector<Points> Vertices;
        int Dim; //Number of edges
        double Area =-1;
        double Perimeter = -1;


    };

    template<typename... T>
    Polygon::Polygon(const Points &P1,const Points &P2, T &&... Ps) {
        Dim = 2+sizeof...(Ps); // 3 Points are needed at least, size of return variadic number of variadic args
        //Push 2 first points in the vector
        Vertices.template emplace_back(P1);
        Vertices.template emplace_back(P2);
        for (auto &&point: {Ps...}) {
            Vertices.template emplace_back(point); //Push variadic points
        }
    }

}
#endif //MATHS2_POLYGON_HPP
