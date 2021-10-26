#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QObject>

#include "Methods.h"

#include <QDebug>


#include "./TernaryPlot/Interfaces/Points.hpp"


class OpenGLWidget: public QOpenGLWidget{
    Q_OBJECT
public:
    /**
     * @brief OpenGLWidget constructor
     * @param parent
     */
    explicit OpenGLWidget(QWidget *parent = nullptr);

    ~OpenGLWidget();

    /**
     * @brief To get a painevent (draw and refresh scene)
     * @param e
     */
    void paintEvent(QPaintEvent* e) override;


    /**
     * @brief const getter method
     * @return
     */
    const QVector<GraphItem>& get_graphs()const;


    void DrawSegmentWith2Points(const Points& Point1,const Points& Point2,const QPen Pen = QPen{Qt::red,3});


    /**
     * @brief Main method
     * Draw every graphs that have been added before into graph container
     */
    void draw_graphs();


    /**
     * @brief Clear scene
     */
    void FlushGraphs(){graphsContainer.clear();};

    /**
     * @brief Draw a point into the scene
     * @param point Point to add
     */
    void DrawPoint(const Points& point);

    /**
     * @brief mouseMoveEvent, get mouse position on the window
     * @param event
     */
    void mouseMoveEvent(QMouseEvent* event)override;



    /**
     * @brief set position of mouse's cursor in order to show it
     * @param newPosition String fromated by controller
     */
    void setPosition(const QString &newPosition);

signals:
    /**
     * @brief Emit mouse coordinates
     * @param point coordinates
     */
    void CursorPosition(const Points& point)const;



private:
    /**
     * @brief graphsContainer contains every graph added by controlelr in order to show them
     */
    QVector<GraphItem> graphsContainer;


    /**
     * @brief ShowPosition, write mouse's cursor
     * @param painter
     */
    void ShowPosition(QPainter* painter);


    /**
     * @brief Init the scene, clear it, computes its bound
     */
    void Init();

    QPen MainPen{Qt::black,3};


    QFont TextFont{"Verdana",10};

    ConversionFactors cf;
    MaxMinXY maxmin;

    QPainter *painter;

    QString Position;

};



#endif // OPENGLWIDGET_H
