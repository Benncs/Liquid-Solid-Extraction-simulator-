#include "processcontroller.hpp"



ProcessController::ProcessController(QWidget *parent) : QWidget(parent)
{
    TernaryController = new TernaryPlotController(this);
}

void ProcessController::GetParamFromIni(QSettings *Settings)
{
    Feed = GetCurrentsFromIni(Settings,"Feed");
    Output = GetCurrentsFromIni(Settings,"Out");
    if(Settings->contains("Tray") && Settings->contains("Steps")){
        ntray = Settings->value("Tray").toInt();
        steps = Settings->value("Steps").toInt();
    }
    else{
        throw std::invalid_argument("At leats one value is missing in .ini file");

    }

}

const std::shared_ptr<Current> ProcessController::GetCurrentsFromIni(QSettings *Settings, const QString &group)
{
    try{
        Settings->beginGroup(group);
        if(Settings->contains("Xa") && Settings->contains("Xb")){
            const Ratios currentratios = Ratios(Settings->value("Xa").toDouble(),Settings->value("Xb").toDouble());
            const double flow = Settings->value("Flow").toDouble();
            Settings->endGroup();
            return std::make_shared<Current>(flow,currentratios);
        }
        else{
            Settings->endGroup();
            throw std::invalid_argument("At leats one value is missing in .ini file");

        }

     }
     catch(const std::exception& e){
         QString thrown = QString::fromLocal8Bit(e.what());
         auto E = "Error while loading params from .ini, please check file:\n"+thrown;
         throw std::invalid_argument(E.toStdString());
     }
}

ProcessController::~ProcessController()
{
    delete TernaryController;
}

void ProcessController::Start()
{
        if(steps<2) steps=2;
        if(ntray==0) ntray=1;
        ExtractionProcess = new Process(ntray,Feed,Output);

        ExtractionProcess->Run(steps);
        Data = ExtractionProcess->getData();

        Draw(steps);
        readyToSave=true;
        delete ExtractionProcess;

}

void ProcessController::GetParamFromDialog()
{
    try{
        Dialogs = new ParamChoice(this);
        Feed = Dialogs->getFeed();
        Output = Dialogs->getOutput();
        steps = Dialogs->getSteps();
        ntray = Dialogs->getNtray();
        if(steps<=0) throw std::invalid_argument("Iterations number must be strictly positive");
        if(ntray<=0) throw std::invalid_argument("Number of therocial tray must be strictly positive");
        LoadedParam = true;
        delete Dialogs;
    }
    catch(const std::exception& e){
        QString thrown = QString::fromLocal8Bit(e.what());
        auto E = "Error while loading params, please chekc your inputs\n"+thrown;
        throw std::invalid_argument(E.toStdString());
    }

}

void ProcessController::SaveAsCsv(const QString &Filename)
{

    if(readyToSave){
        Writer = new SaveFiles();
        Writer->WriteCsv(Filename,Data,Feed,Output);
        delete Writer;
    }
    else{
        throw std::invalid_argument("Cannot save");
    }

}

void ProcessController::SaveAsTxt(const QString &Filename)
{

    if(readyToSave){
        Writer = new SaveFiles();
        Writer->WriteTxt(Filename,Data,Feed,Output);
        delete Writer;
    }
    else{
        throw std::invalid_argument("Cannot save");
    }


}

bool ProcessController::getReadyToSave() const
{
    return readyToSave;
}

bool ProcessController::getLoadedParam() const
{
    return LoadedParam;
}

int ProcessController::FindConvergence()
{
    if(ntray==0) ntray=1;
    ExtractionProcess = new Process(ntray,Feed,Output);

        unsigned int count = 0;
        unsigned steps = 2;
        const int stepiteration = 1+(int)ntray/5.;

        while (count < MAX_PROCESS_ITERATIONS){
            count++;
            qDebug()<<count;
            try{
                ExtractionProcess->Run(steps);
                Data = ExtractionProcess->getData();
                readyToSave=true;
                Draw(steps);
                delete ExtractionProcess;
                return steps;
            }
            catch(const std::invalid_argument& e){
                if(QString::fromLocal8Bit(e.what())=="Mass conservation issue"){
                    steps+=stepiteration;
                }
                else{
                    throw std::invalid_argument("Error while finding steps");
                }
            }

        }

        delete ExtractionProcess;
        return -1;
    }

void ProcessController::Draw(unsigned steps)const
{
    TernaryController->Clear();
    //const auto O = Ratios(1,0,0);
    const auto FeedRatios = ExtractionProcess->getFeed()->getRatios();
    const auto OutRatios = ExtractionProcess->getOutput()->getRatios();
    const auto UF = Data->Refined[steps-1]->getRatios();
    const auto OV = Data->Extracted[steps-1]->getRatios();

    TernaryController->DrawLine(FeedRatios,OutRatios);
    TernaryController->DrawLine(UF,OV);
    TernaryController->DrawPoint(Data->M->getRatios());
    TernaryController->Refresh();
}
