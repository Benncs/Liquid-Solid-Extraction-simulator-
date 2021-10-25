#include "theoricaltray.hpp"

TheoricalTray::TheoricalTray(const std::shared_ptr<Current>& Feed, const std::shared_ptr<Current>& Output):Feed(Feed),Output(Output)
{
    OperatingPoint = std::make_shared<Current>(Feed->Mix(*Output));
    SlopeOM = OperatingPoint->getRatios().C()/OperatingPoint->getRatios().B();
    UnderFlowRatios = Ratios(0,1/(1+SlopeOM));
}

TrayOutput TheoricalTray::Compute()
{
    if(OperatingPoint->getRatios().C()<=UnderFlowFunction(OperatingPoint->getRatios().B())){
        throw std::invalid_argument("Solvent flow rate to low");
    }
    this->ComputeOverFlowRatios();
    double FlowRatio = (OperatingPoint->getRatios().B()-OverFlowRatios.B())/(UnderFlowRatios.B()-OperatingPoint->getRatios().B());
    double UnderFlow_Flow = OperatingPoint->getFlow()*FlowRatio/(1+FlowRatio);
    double OverFlow_Flow = UnderFlow_Flow/FlowRatio;

    auto UF = std::make_shared<Current>(UnderFlow_Flow,UnderFlowRatios);
    auto OF = std::make_shared<Current>(OverFlow_Flow,OverFlowRatios);
    return  TrayOutput(OF,UF,this->OperatingPoint);
}

void TheoricalTray::ComputeOverFlowRatios()
{
    auto X = new LinearAlgebra::Vector<double>({0,0});

    const std::function<double()> F1 = [&X,this](){
        const double x = X->GetElement(0);
        const double y = X->GetElement(1);
        return y-this->UnderFlowFunction(x);
    };

    const std::function<double()> F2 = [&X,this](){
        const double x= X->GetElement(0);
        const double y = X->GetElement(1);
        return y-SlopeOM*x;
    };

    Calculus::NewtonN(X,std::move(F1),std::move(F2));

    auto Xb = X->GetElement(0);
    auto Xs = X->GetElement(1);
    auto Xa = 1-Xb-Xs;
    OverFlowRatios = Ratios(Xa,Xb);

    delete X;

}
