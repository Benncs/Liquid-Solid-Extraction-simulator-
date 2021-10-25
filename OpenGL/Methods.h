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


struct PointDoubleXY
{
    PointDoubleXY(const double X,const double Y): x(X),y(Y){}
    double x;
    double y;
};

struct ConversionFactors
{
    double ax, bx;
    double ay, by;
};

struct MaxMinXY
{
    double x_min, x_max;
    double y_min, y_max;
};

struct GraphItem
{

    GraphItem(double xmin,double xmax,double ymin, double ymax):x_min(xmin),x_max(xmax),y_min(ymin),y_max(ymax) {}
    double x_min, x_max;
    double y_min, y_max;

    QVector<Points> elements;
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
