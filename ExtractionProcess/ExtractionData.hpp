#ifndef EXTRACTIONDATA_HPP
#define EXTRACTIONDATA_HPP
#include "current.hpp"
#include "QVector"
#include <memory>

struct ExtractionData{


    /**
     * @struct To store results from extraction process
     * @brief Main Constructor
     * @param OperatingPoint : Operating point of the process
     * @param Refined : First part of Historic of every result for each iteration
     * @param Extracted : Second part of Historic of every result for each iteration
     * @param step : Step needed to have convergence
     * @param Tray : Theoretical trays wanted by user
     */
    ExtractionData(const std::shared_ptr<Current>& OperatingPoint,const QVector<std::shared_ptr<Current>>& Refined,const QVector<std::shared_ptr<Current>>& Extracted,unsigned step,unsigned Tray){
        this->Extracted = Extracted;
        this->Refined = Refined;
        this->step = step;
        M = OperatingPoint;
        ntray = Tray;
    };

    /**
     * @brief Default constructor
     */
    ExtractionData(){
        M = std::make_shared<Current>();
        Refined = QVector<std::shared_ptr<Current>>();
        Extracted = QVector<std::shared_ptr<Current>>();
        step = 0;
        ntray = 0;
    };


    std::shared_ptr<Current> M;
    QVector<std::shared_ptr<Current>> Refined;
    QVector<std::shared_ptr<Current>> Extracted;
    unsigned step;
    unsigned ntray;

};

#endif // EXTRACTIONDATA_HPP


