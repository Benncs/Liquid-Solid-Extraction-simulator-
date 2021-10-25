//
// Created by CASALE Benjamin on 17/09/2021.
//

#ifndef TERNARYPLOT_TRIANGLE_HPP
#define TERNARYPLOT_TRIANGLE_HPP
#include "../Interfaces/Points.hpp"

enum class TriangleType{
    /*!
     * \brief Enumeration to store each triangle type
    */
    EQUILATERAL,
    RECTANGLE,
    TRIANGLe,
};

class Triangle{
    /*!
     \brief Represent's a triangle, it needs 3 vertexes given as 3 points
    */
public:

    /*!
     * \brief Constructor
     * \param A: Coordinates of Vertex A
     * \param B: Coordinates of Vertex B
     * \param C: Coordinates of Vertex C
    */
    Triangle(const Points& A,const Points& B,const Points& C):VertexA(A),VertexB(B),VertexC(C){

    }
    /*!
     * \brief Default constructor
    */
    Triangle()= default;

    /*!
     * \brief Copy Constructor
     * \param Triangle to copy
    */
    Triangle(const Triangle& T){
        VertexA = T.VertexA;
        VertexB = T.VertexB;
        VertexC = T.VertexC;
        height = T.height;
        width = T.width;
    }

    /*!
     * \brief Vertex A's getter
     * \return Vertex A
    */
    [[nodiscard]] inline Points A()const {return VertexA;}

    /*!
     * \brief Vertex B's getter
     * \return Vertex B
    */
    [[nodiscard]] inline Points B()const {return VertexB;}

    /*!
     * \brief Vertex C's getter
     * \return  Vertex C
    */
    [[nodiscard]] inline Points C()const {return VertexC;}

    /*!
     * \brief Triangle's width  getter
     * \return Triangle's width
    */
    [[nodiscard]] inline double Width()const {return width;}

    /*!
     * \brief Triangle's height getter
     * \return Triangle's height
    */
    [[nodiscard]] inline double Height()const {return height;}


    /*!
     * \brief Test if a given point is located inside the area delimited by the triangle
     * \param Point to test
     * \return True if the point is inside
    */
    [[nodiscard]] bool Contains(const Points& points)const;




    TriangleType getType() const;

protected:;
    Points VertexA;
    Points VertexB;
    Points VertexC;
    double height = 0;
    double width = 0;
    TriangleType Type;

};

#endif //TERNARYPLOT_TRIANGLE_HPP
