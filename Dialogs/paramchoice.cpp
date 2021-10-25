#include "paramchoice.hpp"
#include "ui_paramchoice.h"

ParamChoice::ParamChoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamChoice)
{
    ui->setupUi(this);
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));


        if (this->exec()==QDialog::Accepted)
        {
            auto Flow = this->ui->FeedFlow->text().toDouble();
            auto Xa = this->ui->FeedXa->text().toDouble();
            auto Xb = this->ui->FeedXb->text().toDouble();
            auto Xs = this->ui->FeedXs->text().toDouble();
            Feed = std::make_shared<Current>( Current(Flow,Ratios(Xa,Xb,Xs)));
            Flow = this->ui->OutputFlow->text().toDouble();
            Xa = this->ui->OutputXa->text().toDouble();
            Xb = this->ui->OutputXb->text().toDouble();
            Xs = this->ui->OutputXc->text().toDouble();
            Output = std::make_shared<Current>(Current(Flow,Ratios(Xa,Xb,Xs)));
            this->steps = this->ui->iterations->text().toUInt();
            this->ntray = this->ui->traynum->text().toUInt();
        }

        else this->close();
}

ParamChoice::~ParamChoice()
{
    delete ui;
}


int ParamChoice::getSteps() const
{
    return steps;
}

int ParamChoice::getNtray() const
{
    return ntray;
}

const std::shared_ptr<Current> &ParamChoice::getFeed() const
{
    return Feed;
}

const std::shared_ptr<Current> &ParamChoice::getOutput() const
{
    return Output;
}
