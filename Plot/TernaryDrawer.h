#ifndef TERNARYDRAWER_H
#define TERNARYDRAWER_H

#include <QWidget>
#include "OpenGL/graphopengl.h"

#include <cmath>

#include "TernaryPlot/Triangles/Triangle.hpp"



namespace Ui {
class Plot;
}

class TernaryDrawer : public QWidget
{
    /*!
     * \brief Contains function that can be used by controller to draw element in the canvas (ternary plot) 
    */
    Q_OBJECT

public:
    /*!
     * \brief Constructor 
    */
    explicit TernaryDrawer(QWidget *parent = nullptr);
    
    /*!
     * \brief Destructor  
    */
    ~TernaryDrawer();
    
    /*!
     * \brief Draw the main triangle, ternary plot's base 
     * \param Triangle given by model as ptr  
    */
    void DrawTriangle(const std::shared_ptr<Triangle>& triangle)const;
    
    /*!
     * \brief Draw a line in the ternary plot, 
     * \param Point1,Point2 : first and end point of the line given in cartesian coordinates
     * \param Pen, QPEn with which we want to draw the line 
    */
    void DrawLine(const Points& Point1,const Points& Point2, const QPen& Pen = QPen{Qt::red,3})const;
    
    /*!
     * \brief Plot a point in the ternary plot
     * \param Point : Cartesian coordinates of the point  
    */
    void DrawPoint(const Points& Point)const;
    
    /*!
     * \brief Set cursor position in the opengl object in order to draw it 
     * \param String that contains cursor position  
    */
    void SetCursorPosition(const QString& Position)const;

    inline void Refresh()const{View->repaint();};

    inline void Clear()const{View->FlushGraphs();};

    inline OpenGLWidget* getView()const{return View;}


public slots:
    /*!
     * \brief Get cursor position from opengl widget 
     * \param Point coordinates (cartesian) from opengl widget 
    */
    void GetCursorPosition(const Points& point)const;

signals:
    /*!
     * \brief Send cursor position to the controller in order convert it into ratio  
     * \param Point coordinates (cartesian) from opengl widget 
    */
    void CursorPosition(const Points& point)const;

private:
    Ui::Plot *ui; //User interface 

    const GraphOpenGL *GraphView; //View given by graph factory
    OpenGLWidget *View; //View show by app
};

#endif // TERNARYDRAWER_H
