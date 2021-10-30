#ifndef UNDERFLOWFUNCTIONPARSER_H
#define UNDERFLOWFUNCTIONPARSER_H

#include <QWidget>
#include <QJSEngine>

class UnderFlowFunctionParser : public QWidget
{
    /**
      @class Way to dynamically parse function given by user
      **/
    Q_OBJECT
public:

    /**
     * @brief Constructor: Init QJSEngine and QJSValue as function
     * @param Func Function's formula (unknow is written x)
     * @param parent
     */
    UnderFlowFunctionParser(const QString& Func = "2.9767*x*x*x-2.0481*x*x+0.2202*x+0.1711",QWidget *parent = nullptr);

    /**
     * @brief evaluate function (QJSEngine) wth given value
     * @param x
     * @return function's result
     */
    double eval(double x)const;
    ~UnderFlowFunctionParser();
private:
    QJSEngine *Engine;
    QJSValue val;



    static double js_to_double(const QJSValue& js_value)
    {
        if (js_value.isError()) throw std::invalid_argument("Error while parsing");
        else
            return js_value.toString().toDouble();
    }


signals:

};

#endif // UNDERFLOWFUNCTIONPARSER_H
