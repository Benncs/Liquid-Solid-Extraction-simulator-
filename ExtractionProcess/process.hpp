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
    /**
     * @class Represent a whole liquid-solid extraction process with a open system (like an extraction columns) at counter-current
     * Mathematical resolution
     */
public:
    /**
     * @brief Main Constructor
     * @param traynumber Number of theoretical trays wanted to simulate
     * @param Feed Input current with solid that we want to extract
     * @param CounterFeed Output current (solvant current)
     */
    Process(unsigned traynumber,const std::shared_ptr<Current>& Feed,const std::shared_ptr<Current>& CounterFeed);

    /**
     * @brief Default Destructor
     */
    ~Process();

    /**
     * @brief Main method
     * Simulate process
     * @param steps Iteration needed by solver to converge
     */
    void Run(unsigned steps);

    //Getters

    /**
     * @brief Const getter method
     * @return InputFeed
     */
    const std::shared_ptr<Current> &getFeed() const;

    /**
     * @brief Const getter method
     * @return SolventFeed
     */
    const std::shared_ptr<Current> &getOutput() const;

    /**
     * @brief Const getter method
     * @return Operating Point
     */
    const std::shared_ptr<Current> &getOperatingPoint() const;

    /**
     * @brief Const getter method
     * @return Results
     */
    const std::shared_ptr<ExtractionData> &getData() const;

private:

    unsigned ntray;
    std::shared_ptr<Current> InputFeed;
    std::shared_ptr<Current> SolventFeed;
    std::shared_ptr<Current> OperatingPoint;
    std::shared_ptr<ExtractionData> Data;


    bool Convergence = false;


};

#endif // PROCESS_HPP
