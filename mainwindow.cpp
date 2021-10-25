#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Plot/TernaryDrawer.h"

#include "ExtractionProcess/process.hpp"

#include <QSettings>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    controller = new ProcessController(this);
    this->ui->statusbar->showMessage("Wait for run");


    this->setCentralWidget(controller->GetView());
    this->ui->toolBar->raise();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete controller;

}



void MainWindow::on_actionSave_as_csv_triggered()
{
    if(controller->getReadyToSave()){
        try{
            QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"),"./",tr("doc (*.csv)"));
            if(fileName!="")
                controller->SaveAsCsv(fileName);
        }
        catch(...){
            QMessageBox::critical(this,"Ërror","Error when saving");
        }
    }

}


void MainWindow::on_actionSave_as_txt_triggered()
{

    if(controller->getReadyToSave()){
        try{
        QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"),"./",tr("doc (*.txt)"));
        if(fileName!="")
            controller->SaveAsTxt(fileName);
        }
        catch(...){
            QMessageBox::critical(this,"Ërror","Error when saving");
        }
    }
}
#include "./Dialogs/paramchoice.hpp"

void MainWindow::on_actionInput_triggered()
{
    try{
        controller->GetParamFromDialog();
    }
    catch(const std::invalid_argument&e){
        QMessageBox::critical(this,"Ërror",e.what());
    }
}


void MainWindow::on_actionStart_triggered()
{
    settings = new QSettings("settings.ini", QSettings::IniFormat);;

    if(!controller->getLoadedParam()){
        try{
        controller->GetParamFromIni(settings);
        }
        catch(std::invalid_argument& e){
            ShowMessageError(e);
            return;
        }
    }

    try{
        controller->Start();
        this->ui->statusbar->showMessage("Done");
    }
    catch(std::invalid_argument &e){
        ShowMessageError(e);
    }
    catch(const Exceptions& e){
        auto error = e.what();
        QMessageBox::critical(this,"error",error);
    }

    delete settings;
}


void MainWindow::on_actionFindConvergence_triggered()
{
    this->ui->statusbar->showMessage("Wait for finish");
    settings = new QSettings("settings.ini", QSettings::IniFormat);;

    if(!controller->getLoadedParam()){
        try{
        controller->GetParamFromIni(settings);
        }
        catch(std::invalid_argument& e){
            ShowMessageError(e);
            return;
        }
    }

    try{

        int steps = controller->FindConvergence();
        if(steps>0){
            this->ui->statusbar->showMessage("Done");
            auto Res = QString("Values have converged in %1 steps").arg(steps);
            QMessageBox::information(this,"Resolution achiedved",Res);
        }
        else{
            this->ui->statusbar->showMessage("Resolution failed");
            QMessageBox::information(this,"Resolution failed","Values haven't converged");
        }
    }
    catch(std::invalid_argument &e){
        ShowMessageError(e);
    }
    catch(const Exceptions& e){
        auto error = e.what();
        QMessageBox::critical(this,"error",error);
    }

    delete settings;
}

