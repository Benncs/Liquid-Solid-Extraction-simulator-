#include "process.hpp"

Process::Process(unsigned traynumber, const std::shared_ptr<Current> &Feed, const std::shared_ptr<Current> &Out):ntray(traynumber),Feed(Feed),Output(Out)
{
    OperatingPoint = std::make_shared<Current>(Feed->Mix(*Out));
}

Process::~Process()
{

}

void Process::Run(unsigned int steps)
{

    const std::shared_ptr<Current> VoidFlow = std::make_shared<Current>();
    QVector<std::shared_ptr<Current>> E,R,Rf,Ef;
    for (unsigned index = 0;index<ntray;++index){
        E.emplaceBack(Output);
        R.emplaceBack(Feed);
        Rf.emplaceBack(VoidFlow);
        Ef.emplaceBack(VoidFlow);
    }
    QVector<std::shared_ptr<Current>> refined,extracted;

    TrayOutput FirstTray,LastTray,MiddleTrays;

    for(unsigned i = 0;i<steps;++i){
        FirstTray = TheoricalTray(Feed,E[1]).Compute();
        LastTray = TheoricalTray(R[ntray-2],Output).Compute();

        Ef[0] = FirstTray.Underflow;
        Ef[ntray-1] = LastTray.Underflow;
        Rf[0] = FirstTray.Overflow;
        Rf[ntray-1] = LastTray.Overflow;

        for(unsigned j = 1;j<ntray-1;++j){
            MiddleTrays = TheoricalTray(R[j-1],E[j+1]).Compute();
            Ef[j] = MiddleTrays.Underflow;
            Rf[j] = MiddleTrays.Overflow;
        }

        R = Rf;
        E = Ef;
        refined.emplaceBack(Rf[ntray-1]);
        extracted.emplaceBack(Ef[0]);
    }

    Data = std::make_shared<ExtractionData>(OperatingPoint,refined,extracted,steps,ntray);
    auto S = refined[steps-1]->Mix(*extracted[steps-1]);
    auto S2 = Feed->Mix(*Output);
    Convergence = S==S2;
    if(!Convergence){
        throw std::invalid_argument("Mass conservation issue");
    }


}

const std::shared_ptr<Current> &Process::getFeed() const
{
    return Feed;
}

const std::shared_ptr<Current> &Process::getOutput() const
{
    return Output;
}

const std::shared_ptr<Current> &Process::getOperatingPoint() const
{
    return OperatingPoint;
}

const std::shared_ptr<ExtractionData> &Process::getData() const
{
    return Data;
}




