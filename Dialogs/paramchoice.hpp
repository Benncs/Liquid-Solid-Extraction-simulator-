#ifndef PARAMCHOICE_HPP
#define PARAMCHOICE_HPP

#include <QDialog>
#include "ExtractionProcess/current.hpp"
#include <memory>

namespace Ui {
class ParamChoice;
}

class ParamChoice : public QDialog
{
    Q_OBJECT

    /**
     * @class Dialog to load process parameters from user
     */

public:
    /**
     * @brief Constructor
     * @param parent
     */
    explicit ParamChoice(QWidget *parent = nullptr);

    /**
     * @brief Default Destructor
     */
    ~ParamChoice();

    /**
     * @brief const getter method
     * @return number of stes given by user
     */
    int getSteps() const;

    /**
     * @brief const getter method
     * @return number of trays given by user
     */
    int getNtray() const;

    /**
     * @brief const getter method
     * @return Feed given by user
     */
    const std::shared_ptr<Current> &getFeed() const;

    /**
     * @brief const getter method
     * @return Output given by user
     */
    const std::shared_ptr<Current> &getOutput() const;

private:
    Ui::ParamChoice *ui;
    std::shared_ptr<Current> Feed,CounterFeed;
    unsigned steps,ntray;
};

#endif // PARAMCHOICE_HPP
