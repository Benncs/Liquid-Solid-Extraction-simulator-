#include "processcontroller.hpp"



ProcessController::ProcessController(QWidget *parent) : QWidget(parent)
{
    TernaryController = new TernaryPlotController(this);
}

void ProcessController::GetParamFromIni(QSettings *Settings)
{
    //Current are grouped, Feed and Out. Groups contain the same keys
    Feed = GetCurrentsFromIni(Settings,"Feed");
    Output = GetCurrentsFromIni(Settings,"Out");
    if(Settings->contains("Tray") && Settings->contains("Steps")){
        ntray = Settings->value("Tray").toUInt();
        steps = Settings->value("Steps").toUInt();
    }
    else{
        //Error that will be caught by mainwindow if ntray is missing or steps number
        throw std::invalid_argument("At leats one value is missing in .ini file");

    }

}

const std::shared_ptr<Current> ProcessController::GetCurrentsFromIni(QSettings *Settings, const QString &group)
{
    //Groups contains the same keys
    try{
        Settings->beginGroup(group); //Start group reading
        //Check if keys exists
        if(Settings->contains("Xa") && Settings->contains("Xb")){
            //Getting current's param : flow and ratios
            const Ratios currentratios = Ratios(Settings->value("Xa").toDouble(),Settings->value("Xb").toDouble());
            const double flow = Settings->value("Flow").toDouble();
            Settings->endGroup(); //Stop group reading
            return std::make_shared<Current>(flow,currentratios);
        }
        else{
            //If at leat one key miss, throw an error, that will be caught later
            Settings->endGroup();//End group before throwing error
            throw std::invalid_argument("At leats one value is missing in .ini file");

        }

     }
     catch(const std::exception& e){
         //If something happens, throw and error that will be caugh by main app window method
         QString thrown = QString::fromLocal8Bit(e.what()); //Char convertion to string
         auto E = "Error while loading params from .ini, please check file:\n"+thrown;
         throw std::invalid_argument(E.toStdString());
    }
}

void ProcessController::DrawUnderFlowLimit()const
{
    if(Drawn){
        const double dx = 0.001;
        double inf = 0;
        double sup = 1;
        int Nombre_Point = 2+ (sup-inf)/dx;

        for(int i=2;i<Nombre_Point;i++){
                double x = inf+(i-1)*dx;
                double x2 = inf+(i)*dx;
                double res2 = TheoreticalTray::UnderFlowFunction(x2);
                double res = TheoreticalTray::UnderFlowFunction(x);
                try{
                    TernaryController->DrawLineInside(Ratios(1-x-res,x),Ratios(1-x2-res2,x2),QPen{Qt::GlobalColor::darkCyan,2});
                }catch(...){
                    break;
                }
        }
        TernaryController->Refresh();
    }


}

ProcessController::~ProcessController()
{
    delete TernaryController;
}

void ProcessController::Start()
{
        /*There is no exception because
         * If error while loading param -> error already thrown
         * If error while computation, error throw by process
         * Everything will be caught by main app window */

        //Standard verification to avoid strange results given by user
        if(steps<2) steps=2;
        if(ntray==0) ntray=1;

        //Init process
        ExtractionProcess = new Process(ntray,Feed,Output);

        //Call main method, process will compute everything
        ExtractionProcess->Run(steps);

        //Result from simulator
        Data = ExtractionProcess->getData();

        //Drawing results
        Draw(steps);
        //If everything is OK, data can be saved
        readyToSave=true;
        delete ExtractionProcess; //Delete Process -> memory optimisation

        Drawn = true;



}

void ProcessController::GetParamFromDialog()
{
    try{
        Dialogs = new ParamChoice(this); //Init dialog that contains fields

        //Loading parameters if diaog ok is pressed
        Feed = Dialogs->getFeed();
        Output = Dialogs->getOutput();
        steps = Dialogs->getSteps();
        ntray = Dialogs->getNtray();

        //basic verification
        if(steps<=0) throw std::invalid_argument("Iterations number must be strictly positive");
        if(ntray<=0) throw std::invalid_argument("Number of therocial tray must be strictly positive");

        //If everyting ok, param are correctly loaded
        LoadedParam = true;
        delete Dialogs; //Delete dialog because it's useless anymore
    }
    catch(const std::exception& e){
        //If something happens, throw a exception that will be caught by main app window
        QString thrown = QString::fromLocal8Bit(e.what());
        auto E = "Error while loading params, please chekc your inputs\n"+thrown;
        throw std::invalid_argument(E.toStdString());
    }
}

void ProcessController::SaveAsCsv(const QString &Filename)
{
    //Data have to be correctly computed to be saved
    if(readyToSave){
        Writer = new SaveFiles(); //Init a new saver
        Writer->WriteCsv(Filename,Data,Feed,Output); //Write data
        delete Writer; //No need to keep writer in memory
    }
    else{
        //Handling error
        throw std::invalid_argument("Cannot save");
    }

}

void ProcessController::SaveAsTxt(const QString &Filename)
{
    //Data have to be correctly computed to be saved
    if(readyToSave){
        Writer = new SaveFiles(); //Init a new saver
        Writer->WriteTxt(Filename,Data,Feed,Output);//Write data
        delete Writer;//No need to keep writer in memory
    }
    else{
        //Handling error
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
    /*
     * Basically a loop from step = 0 to step number that allow simulation convergence */
//    if(ntray==0) ntray=1; //Basic verification

    //Init new process, this object is independant from steps number
    ExtractionProcess = new Process(ntray,Feed,Output);

        unsigned int count = 0; //To count number of iteration
        unsigned steps = 2; //It's useless to init from 1 because it's impossible to converge with 1 step

        const int stepiteration = 1+(int)ntray/5.; //Variable step, the more ntray is bigger the more steps will be bigger

        //While condition is only a number of iteration because if there is convergence, the function returns step number

        while (count < MAX_PROCESS_ITERATIONS){
            count++; //To avoid infinite loop
            try{
                ExtractionProcess->Run(steps); //Run with given step
                //Because of the try scope, if run succeeds, we're sure that data are corrects
                Data = ExtractionProcess->getData();
                readyToSave=true;
                Draw(steps);
                delete ExtractionProcess;
                return steps;
            }
            catch(const std::invalid_argument& e){
                //If mass conservation error issue occurs, it means that there is no convergence
                if(QString::fromLocal8Bit(e.what())=="Mass conservation issue"){
                    steps+=stepiteration; //Step increasing for the next loop
                }
                else{
                    //If another error occure we have to handle it
                    throw std::invalid_argument("Error while finding steps");
                }
            }

        }

        delete ExtractionProcess; //Memory optimisation
        return -1; //If no convergence, as step has to be positive if step ==1 -> no convergence
    }

void ProcessController::Draw(unsigned steps)const
{
    TernaryController->Clear(); //Clear precedent drawing

    //variable to allow better code lisiblity
    const auto FeedRatios = ExtractionProcess->getFeed()->getRatios();
    const auto OutRatios = ExtractionProcess->getOutput()->getRatios();
    const auto UF = Data->Refined[steps-1]->getRatios();
    const auto OV = Data->Extracted[steps-1]->getRatios();

    //Draw 2 lines and 1 point
    TernaryController->DrawLine(FeedRatios,OutRatios);
    TernaryController->DrawLine(UF,OV);
    TernaryController->DrawPoint(Data->M->getRatios());
    TernaryController->Refresh(); //Refresh scene to draw it
}
