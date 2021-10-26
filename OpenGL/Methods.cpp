#include "Methods.h"


ConversionFactors ComputeConversionFactor(const GraphItem& gi, const QRect& rect)
{
    ConversionFactors cf;

    cf.ax = (double)(rect.right() - rect.left()) / (gi.x_max - gi.x_min);
    cf.bx = (double)rect.left() - cf.ax * gi.x_min;

    cf.ay = (double)(rect.top() - rect.bottom()) / (gi.y_max - gi.y_min);
    cf.by = (double)rect.top() - cf.ay * gi.y_max;

    return cf;
}

ConversionFactors ComputeConversionFactor(const MaxMinXY& gi, const QRect& rect)
{
    ConversionFactors cf;

    cf.ax = (double)(rect.right() - rect.left()) / (gi.x_max - gi.x_min);
    cf.bx = (double)rect.left() - cf.ax * gi.x_min;

    cf.ay = (double)(rect.top() - rect.bottom()) / (gi.y_max - gi.y_min);
    cf.by = (double)rect.top() - cf.ay * gi.y_max;

    return cf;
}

MaxMinXY ComputeMaxMinXY(const QVector<GraphItem>& graphs)
{
    const double offset = 0.1;

    MaxMinXY maxmin
    {
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::min(),
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::min()
    };

    QVector<GraphItem>::const_iterator i = graphs.constBegin();

    //Loop through graph element, to find max and min value
    while (i != graphs.constEnd())
    {
        if (maxmin.x_min > i->x_min) maxmin.x_min = i->x_min-offset;
        if (maxmin.x_max < i->x_max) maxmin.x_max = i->x_max+offset;

        if (maxmin.y_min > i->y_min) maxmin.y_min = i->y_min-offset;
        if (maxmin.y_max < i->y_max) maxmin.y_max = i->y_max+offset;

        ++i;
    }

    return maxmin;
}

/**
 * @brief PlotPoint
 * @param cf Coefficient factor to fit point with scene's size
 * @param x abscissa to plot
 * @param y ordinate to plot
 * @return Point ready to be shown
 */
QPointF PlotPoint(const ConversionFactors& cf, double x, double y)
{
    return { cf.ax * x + cf.bx, cf.ay * y + cf.by };
}


/**
 * @brief PlotPoint
 * @param cf Coefficient factor to fit point with scene's size
 * @param pt Point to plot
 * @return Point ready to be shown
 */
QPointF PlotPoint(const ConversionFactors& cf, const Points& pt)
{
    return { cf.ax * pt.x() + cf.bx, cf.ay * pt.y() + cf.by };
}

/**
 * @brief InverseConversionFactor
 * @param cf
 * @param pt
 * @return
 */
Points InverseConversionFactor(const ConversionFactors& cf, const Points& pt){
    auto x = (pt.x()-cf.bx)/cf.ax;
    auto y = (pt.y()-cf.by)/cf.ay;
    return Points(x,y);
}
