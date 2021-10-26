#include "TernaryDrawer.h"
#include "ui_plot.h"

#include "TernaryPlot/Triangles/TriangleFabric.hpp"



TernaryDrawer::TernaryDrawer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot)
{
    ui->setupUi(this);

    GraphView = new GraphOpenGL(this);

    View = GraphView->get_open_gl_widget();

    ui->horizontalLayout->addWidget(View);

    connect(View,&OpenGLWidget::CursorPosition, this, &TernaryDrawer::GetCursorPosition);

}

TernaryDrawer::~TernaryDrawer()
{
    delete ui;
}



void TernaryDrawer::DrawTriangle(const std::shared_ptr<Triangle>& triangle)const
{
    const QPen Pen = QPen{Qt::black,3};
    View->DrawSegmentWith2Points(triangle->A(),triangle->B(),Pen);
    View->DrawSegmentWith2Points(triangle->B(),triangle->C(),Pen);
    View->DrawSegmentWith2Points(triangle->C(),triangle->A(),Pen);

}

void TernaryDrawer::DrawLine(const Points &Point1, const Points &Point2, const QPen& Pen)const
{
    View->DrawSegmentWith2Points(Point1,Point2,Pen);

}

void TernaryDrawer::DrawPoint(const Points &Point)const
{
    const Points P2 = {Point.x()+0.001,Point.y()+0.001};
    QPen PenPoint = QPen{Qt::darkGreen,9};
    View->DrawSegmentWith2Points(Point,P2,PenPoint);
}

void TernaryDrawer::SetCursorPosition(const QString &Position)const
{
    View->setPosition(Position);
    View->repaint();
}


void TernaryDrawer::GetCursorPosition(const Points &point)const
{
    emit CursorPosition(point);
}
