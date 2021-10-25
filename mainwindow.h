#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include "./Controllers/processcontroller.hpp"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    
    /*!
     * \brief Constructor 
     */
    MainWindow(QWidget *parent = nullptr);
    
    /*!
     * \brief Destructor 
     */
    ~MainWindow();
    
    

private slots:

    void on_actionSave_as_csv_triggered();

    void on_actionSave_as_txt_triggered();

    void on_actionInput_triggered();

    void on_actionStart_triggered();

    void on_actionFindConvergence_triggered();

private:
    Ui::MainWindow *ui;
    //QOpenGLWidget *View; //Object in which canvas is drawn
    ProcessController *controller; //Ternary plot's controller

    QSettings *settings;

    void inline ShowMessageError(const std::exception&e){
        auto error = e.what();
        QMessageBox::critical(this,"error",error);
    }


};
#endif // MAINWINDOW_H
