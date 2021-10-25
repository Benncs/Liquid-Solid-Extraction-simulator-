//
// Created by CASALE Benjamin on 17/09/2021.
//
#include "TriangleFabric.hpp"


std::shared_ptr<Triangle> TriangleFactory::GetTriangle(const TriangleType&Type, const double *lenght) {
    {
        if (Type == TriangleType::EQUILATERAL) {
            if (lenght == nullptr) throw std::invalid_argument("No lenght given");
            return std::make_shared<Equilateral>(*lenght);
        }
        else if(Type== TriangleType::RECTANGLE){
            if (lenght == nullptr) throw std::invalid_argument("No lenght given");
            return std::make_shared<Rectangle>(*lenght);
        }
        else {
            throw std::invalid_argument("This type doesn't exist");
        }

    }
}
