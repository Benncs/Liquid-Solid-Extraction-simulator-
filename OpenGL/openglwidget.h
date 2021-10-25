#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QObject>

#include "Methods.h"

#include <QDebug>


#include "./TernaryPlot/Interfaces/Points.hpp"


class OpenGLWidget: public QOpenGLWidget{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

    ~OpenGLWidget();

    void paintEvent(QPaintEvent* e) override;

    QVector<GraphItem>& get_graphs();

    template<typename F>
    void InsertGraph(const F& function, double x_min, double x_max, unsigned int seg_count,Qt::GlobalColor Color = Qt::red);

    void DrawLine(const Points& Point1,const Points& Point2,const QPen Pen = QPen{Qt::red,3});

    void draw_graphs();

    void FlushGraphs(){graphs.clear();};

    void DrawPoint(const Points& point);
    void mouseMoveEvent(QMouseEvent* event)override;




    void setPosition(const QString &newPosition);

signals:
    void CursorPosition(const Points& point);



private:
    QVector<GraphItem> graphs;

    void ShowPosition(QPainter* painter);

    void Init();

    QPen MainPen{Qt::black,3};

    QFont TextFont{"Verdana",10};

    ConversionFactors cf;
    MaxMinXY maxmin;

    QPainter *painter;

    QString Position;

};


//template<typename F>
//void OpenGLWidget::InsertGraph(const F& function, double x_min, double x_max, unsigned int seg_count,Qt::GlobalColor Color){

//   // GraphItem graph{ x_min, x_max, std::numeric_limits<double>::max(),std::numeric_limits<double>::min()};

//    auto graph = GraphItem(x_min,x_max, std::numeric_limits<double>::max(),std::numeric_limits<double>::min());

//        double x,y;

////        auto d = (x_max - x_min) / (double)seg_count;
////        for (auto x = x_min; x <= x_max; x += d)
////        {

////            auto y = function(x);

////            if (graph.y_min > y) graph.y_min = y;
////            if (graph.y_max < y) graph.y_max = y;

//         graph.elements << Points{x, y};
//         graph.Colors << Color;




//        graph.Color =Color;

//        this->graphs << graph;
//}

#endif // OPENGLWIDGET_H
