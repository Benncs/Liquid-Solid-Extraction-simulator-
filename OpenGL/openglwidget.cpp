#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget* parent): QOpenGLWidget(parent){


    TextFont.setBold(true);
    auto surf= QSurfaceFormat();
    surf.setSwapBehavior(QSurfaceFormat::SingleBuffer);
    this->setFormat(surf);

}

OpenGLWidget::~OpenGLWidget()
{
    delete painter;
}

void OpenGLWidget::paintEvent(QPaintEvent *e)
{

    this->draw_graphs();

}


const QVector<GraphItem> &OpenGLWidget::get_graphs()const
{
    return this->graphsContainer;
}

void OpenGLWidget::DrawSegmentWith2Points(const Points &Point1, const Points &Point2,const QPen Pen)
{

    double x_min = 0;
    double x_max = 1;
    auto graph = GraphItem(x_min,x_max, std::numeric_limits<double>::max(),std::numeric_limits<double>::min());
    graph.Pen = Pen;
    graph.elements << Point1;
    graph.elements << Point2;

    if (graph.y_min > Point1.y()) graph.y_min = Point1.y();
    if (graph.y_max < Point2.y()) graph.y_max = Point2.y();

    this->graphsContainer << graph;
    return;

}

void OpenGLWidget::Init(){
    auto rect = this->contentsRect();
    auto boundary = rect + QMargins(-1, 0, 0, -1);

    auto offset = 10;

    auto draw_rect = boundary + QMargins(-offset, -offset, -offset, -offset);

    maxmin = ComputeMaxMinXY(this->graphsContainer);
    cf = ComputeConversionFactor(maxmin, draw_rect);

    painter  = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::RenderHint::Antialiasing);

    // background brush
    painter->setBrush(Qt::white);

    // erase the background with color white
    painter->drawRect(boundary);

    painter->setFont(TextFont);
}

void OpenGLWidget::setPosition(const QString &newPosition)
{
    Position = newPosition;
}

void OpenGLWidget::draw_graphs(){
    Init();

    QVector<GraphItem>::iterator i = this->graphsContainer.begin();

    while (i != this->graphsContainer.constEnd()){
        QPainterPath path;
        painter->setPen(i->Pen);
        const auto PointNumber = i->elements.count();
        path.moveTo(PlotPoint(cf, i->elements[0]));
        for (auto p = 0; p < PointNumber; ++p)
            path.lineTo(PlotPoint(cf, i->elements[p]));
        painter->drawPath(path);

        ++i;

    }
//    painter->setPen(QColor("black"));
//    auto topleftTextBox = PlotPoint(cf,0,0.8);
//    auto boundary = QRectF(topleftTextBox,QSizeF(100,100) );
//    painter->drawText(boundary,Qt::AlignCenter,Position);
    ShowPosition(painter);
    painter->end();

}


void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    auto x = event->position().x();
    auto y= event->position().y();
//    auto x = event->scenePosition().x();
//    auto y = event->scenePosition().y();
    auto Point = InverseConversionFactor(cf,Points(x,y));
    emit this->CursorPosition(Point);

}

void OpenGLWidget::ShowPosition(QPainter *painter)
{
    painter->setPen(QColor("black"));
    auto topleftTextBox = PlotPoint(cf,0.55,0.8);
    auto boundary = QRectF(topleftTextBox,QSizeF(100,100) );
    painter->drawText(boundary,Qt::AlignCenter,Position);
}








