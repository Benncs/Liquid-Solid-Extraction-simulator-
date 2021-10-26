#ifndef METHODS_H
#define METHODS_H


#include <QObject>
#include <QVector>
#include <QOpenGLWidget>
#include <QPainterPath>
#include <QPaintEvent>
#include <QVector>
#include <QOpenGLWidget>
#include <QPainter>
#include "TernaryPlot/Interfaces/Points.hpp"


//struct PointDoubleXY
//{
//    PointDoubleXY(const double X,const double Y): x(X),y(Y){}
//    double x;
//    double y;
//};


/**
 * @brief The ConversionFactors struct
 * Store 4 factor to convert coordinates to fit with the scene's size
 */
struct ConversionFactors
{
    //each coordinates has a different factor
    double ax, bx;
    double ay, by;
};


/**
 * @brief The MaxMinXY struct
 * Store scene's bounds
 */
struct MaxMinXY
{
    double x_min, x_max;
    double y_min, y_max;
};


/**
 * @brief The GraphItem struct
 * Store every drawing information
 */
struct GraphItem
{

    GraphItem(double xmin,double xmax,double ymin, double ymax):x_min(xmin),x_max(xmax),y_min(ymin),y_max(ymax) {}

    //value max and min stored in graph
    double x_min, x_max;
    double y_min, y_max;


    //Each point to connect with each other
    QVector<Points> elements;

    //Pen with which this graph is drawn
    QPen Pen;
    QColor Color = QColor("black");
};



MaxMinXY ComputeMaxMinXY(const QVector<GraphItem>& graphs);

QPointF PlotPoint(const ConversionFactors& cf, double x, double y);
QPointF PlotPoint(const ConversionFactors& cf, const Points& pt);
Points InverseConversionFactor(const ConversionFactors& cf, const Points& pt);

ConversionFactors ComputeConversionFactor(const GraphItem& gi, const QRect& rect);
ConversionFactors ComputeConversionFactor(const MaxMinXY& gi, const QRect& rect);


#endif // METHODS_H
