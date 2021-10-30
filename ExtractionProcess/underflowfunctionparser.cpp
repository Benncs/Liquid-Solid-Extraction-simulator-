#include "underflowfunctionparser.h"

UnderFlowFunctionParser::UnderFlowFunctionParser(const QString& Func,QWidget *parent) :QWidget(parent)
{
    Engine = new QJSEngine();
    const auto JSFunc = "(function(x) { return "+Func+"; })";
    val = Engine->evaluate(JSFunc);
}

double UnderFlowFunctionParser::eval(double x)const
{
    QJSValueList args;;
    args<<x;

    return js_to_double(val.call(args));
}

UnderFlowFunctionParser::~UnderFlowFunctionParser()
{
    delete Engine;
}
