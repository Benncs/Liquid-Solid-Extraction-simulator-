#ifndef PROCESSCONTROLLER_H
#define PROCESSCONTROLLER_H

#include <QObject>
#include <QWidget>

#include "TernaryPlotcontroller.hpp"
#include "ExtractionProcess/process.hpp"
#include "savefiles.hpp"
#include <QSettings>
#include "Dialogs/paramchoice.hpp"
#include <memory>

#define MAX_PROCESS_ITERATIONS 500


class ProcessController : public QWidget
{
    Q_OBJECT
public:
    explicit ProcessController(QWidget *parent = nullptr);


    ~ProcessController();
    void Start();
    void GetParamFromDialog();
    void GetParamFromIni(QSettings* Settings);

    void SaveAsCsv(const QString& Filename);
    void SaveAsTxt(const QString& Filename);
    inline  OpenGLWidget* GetView()const{return TernaryController->GetDrawer()->getView();}
    bool getReadyToSave() const;

    bool getLoadedParam() const;

    int FindConvergence();


private:
    std::shared_ptr<ExtractionData> Data;
    std::shared_ptr<Current> Feed,Output;


    const TernaryPlotController *TernaryController = nullptr;
    const ParamChoice *Dialogs = nullptr;

    Process *ExtractionProcess = nullptr;
    SaveFiles *Writer = nullptr;

    bool readyToSave = false;
    bool LoadedParam = false;
    unsigned steps,ntray;

    const std::shared_ptr<Current> GetCurrentsFromIni(QSettings* Settings,const QString& group);
    void Draw(unsigned steps)const;

signals:

};

#endif // PROCESSCONTROLLER_H
