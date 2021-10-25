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

public:
    explicit ParamChoice(QWidget *parent = nullptr);
    ~ParamChoice();


    int getSteps() const;
    int getNtray() const;

    const std::shared_ptr<Current> &getFeed() const;
    const std::shared_ptr<Current> &getOutput() const;

private:
    Ui::ParamChoice *ui;
    std::shared_ptr<Current> Feed,Output;
    unsigned steps,ntray;
};

#endif // PARAMCHOICE_HPP
