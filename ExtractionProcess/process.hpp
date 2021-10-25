#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "ExtractionProcess/current.hpp"
#include <QVector>
#include "theoricaltray.hpp"
#include <exception>
#include <memory>

#include "ExtractionData.hpp"




class Process
{
public:
    Process(unsigned traynumber,const std::shared_ptr<Current>& Feed,const std::shared_ptr<Current>& Out);
    ~Process();
    void Run(unsigned steps);

    const std::shared_ptr<Current> &getFeed() const;
    const std::shared_ptr<Current> &getOutput() const;
    const std::shared_ptr<Current> &getOperatingPoint() const;
    const std::shared_ptr<ExtractionData> &getData() const;

private:

    unsigned ntray;
    std::shared_ptr<Current> Feed;
    std::shared_ptr<Current> Output;
    std::shared_ptr<Current> OperatingPoint;
    std::shared_ptr<ExtractionData> Data;

    bool Convergence = false;


};

#endif // PROCESS_HPP
