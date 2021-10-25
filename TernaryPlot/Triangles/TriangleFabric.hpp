//
// Created by CASALE Benjamin on 17/09/2021.
//

#ifndef TERNARYPLOT_TRIANGLEFABRIC_HPP
#define TERNARYPLOT_TRIANGLEFABRIC_HPP
#include "Triangle.hpp"
#include "Equilateral.hpp"
#include "Rectangle.hpp"
#include <memory>



class TriangleFactory {
    /*!
     * \brief Triangle Factory to have acces to a specific triangle
    */

public:
    /*!
     * \brief Get Specific triangle
     * \param Type : Triangle Type name
     * \param lenght : (optional) pointer to triangle's lenght
     * \return shared ptr pointed to a triangle
    */
    static std::shared_ptr<Triangle> GetTriangle(const TriangleType& Type, const double *lenght = nullptr);
};

#endif //TERNARYPLOT_TRIANGLEFABRIC_HPP
