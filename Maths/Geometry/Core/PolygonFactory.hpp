//
// Created by CASALE Benjamin on 08/10/2021.
//

#ifndef MATHS2_POLYGONFACTORY_HPP
#define MATHS2_POLYGONFACTORY_HPP

#include "../Shapes/Polygons/Quadrilateral/Diamond.hpp"
#include "../Shapes/Polygons/Quadrilateral/Square.hpp"
#include <memory>

namespace Geometry {

    enum class POLYGONS {
        SQUARE,
        DIAMOND,
        RECTANGLE,
        PARALLELOGRAM,
        UNKNOW
    };

    class PolygonFactory {
    public:
        template<class ...T>
        static std::shared_ptr<Polygon>
        GetPolygon(const POLYGONS &Name, const Points &P1, const Points &P2, T &&... Ps);
    };

    template<class... T>
    std::shared_ptr<Polygon>
    PolygonFactory::GetPolygon(const POLYGONS &Name, const Points &P1, const Points &P2, T &&... Ps) {
        switch (Name) {
            case POLYGONS::SQUARE: {
                return std::make_shared<Square>(P1, P2, Ps...);
            }
            case POLYGONS::DIAMOND: {
                return std::make_shared<Diamond>(P1, P2, Ps...);
            }
            case POLYGONS::RECTANGLE: {
                return std::make_shared<Rectangle>(P1, P2, Ps...);
            }
            case POLYGONS::PARALLELOGRAM: {
                return std::make_shared<Parallelogram>(P1, P2, Ps...);
            }
            default:
                return std::shared_ptr<Polygon>();
        }

    }

}


#endif //MATHS2_POLYGONFACTORY_HPP
