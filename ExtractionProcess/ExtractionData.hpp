#ifndef EXTRACTIONDATA_HPP
#define EXTRACTIONDATA_HPP
#include "current.hpp"
#include "QVector"
#include <memory>

struct ExtractionData{
    ExtractionData(const std::shared_ptr<Current>& OperatingPoint,const QVector<std::shared_ptr<Current>>& Refined,const QVector<std::shared_ptr<Current>>& Extracted,unsigned step,unsigned Tray){
        this->Extracted = Extracted;
        this->Refined = Refined;
        this->step = step;
        M = OperatingPoint;
        ntray = Tray;
    };

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


