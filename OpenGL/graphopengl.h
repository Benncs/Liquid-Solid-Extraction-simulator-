#ifndef GRAPHOPENGL_H
#define GRAPHOPENGL_H

#include <QWidget>

#include "openglwidget.h"

namespace Ui {
class GraphOpenGL;
}

class GraphOpenGL : public QWidget
{
    /*!
     * \brief Interface to have acces to application's opengl widget
    */
    Q_OBJECT

public:
    /*!
     * \brief default constructor
    */
    explicit GraphOpenGL(QWidget *parent = nullptr);

    /*!
     * \brief default destructor
    */
    ~GraphOpenGL();

    /*!
     * \brief opengl widget's getter
     * \return Opengl widget as ptr
    */
    OpenGLWidget* get_open_gl_widget()const;


private:
    Ui::GraphOpenGL *ui;
};

#endif // GRAPHOPENGL_H
