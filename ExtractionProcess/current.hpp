#ifndef CURRENT_HPP
#define CURRENT_HPP

#include "./TernaryPlot/Interfaces/Ratios.hpp"

#include "QTextStream"

class Current
{
    /**
     * @class Represents a Current with mass flow and composition (as ratio of 3 components)
     */
public:
    /**
     * @brief Main Constructor
     * @param Flow : Mass flow
     * @param Ratios Current's composition
     */
    Current(double Flow,const Ratios& Ratios);

    /**
     * @brief const method
     * Addition of two currents (flow and composition)
     * @param F2 Current to add
     * @return Addition of 2 currents
     */
    Current Mix(const Current& F2)const;

    const std::shared_ptr<Current> Mix(const std::shared_ptr<Current>F2)const;

    /**
     * @brief Default constructor
     */
    Current();

    /**
     * @brief First copy constructor
     * @param ToCopy Current to copy
     */
    Current(const Current& ToCopy);

    /**
     * @brief Second copy constructor
     * @param ToCopy Current to copy
     */
    Current(const std::shared_ptr<Current> &ToCopy);

    //Overload

    /**
     * @brief assigment = overload
     * @param C Current to assign
     */
    void operator= (const Current& C);

    /**
     * @brief Equality == overload, const method
     * @param C Current to compare
     * @return true if current are the same
     */
    bool operator== (const Current& C)const;

    /**
     * @brief Equality == overload, const method
     * @param C Current to compare
     * @return true if current are the same
     */
    bool operator== (const std::shared_ptr<Current>& C)const;

    /**
     * Inequality != overload, const method
     * @param C Current to compare
     * @return false if current are the same
     */
    bool operator!= (const Current& C)const;

    /**
     * @brief const getter method, const method
     * @return Current's composition (as ratio)
     */
    const Ratios &getRatios() const;

    /**
     * @brief const getter method
     * @return Current's flow
     */
    double getFlow() const;


private:

    /** @brief Current's composition **/
    Ratios ratios;

    /** @brief Current's mass flow **/
    double Flow;

    /**
     * @brief static method, use to compare double with a tolerance
     * @param x first double to compare
     * @param y first double to compare
     * @param tol Equality tolerance
     * @return true if 2 elements are almost equal
     */
    static inline bool CloseEnough(double x, double y,double tol=1e-4){
        return std::abs(x-y)<tol;
    }
};

/**
 * @brief stream << overload,const method
 * @param outStream Stream
 * @param current Current to add in the stream
 * @return Stream with data added
 */
QTextStream &operator <<(QTextStream &outStream, const Current&  current);

#endif // CURRENT_HPP
