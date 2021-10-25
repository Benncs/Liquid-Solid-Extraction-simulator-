#include "graphopengl.h"
#include "ui_graphopengl.h"

GraphOpenGL::GraphOpenGL(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphOpenGL)
{
    ui->setupUi(this);
    ui->openGLWidget->setParent(this);
}

GraphOpenGL::~GraphOpenGL()
{
    delete ui;
}

OpenGLWidget *GraphOpenGL::get_open_gl_widget()const
{
    return ui->openGLWidget;
}
