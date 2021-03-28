#ifndef COPENGLWIDGET_H
#define COPENGLWIDGET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QColorDialog>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <chrono>
#include <QLabel>

#include <basics/Map.h>

class COpenGlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:

    void mousePressEvent(QMouseEvent *e) override
    {

    }
    void mouseReleaseEvent(QMouseEvent *e) override
    {

    }

    void initializeGL() override;
    void paintGL() override;

    COpenGlWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()):QOpenGLWidget(parent,f), timer(new QTimer(this)), map(100,100,100)
    {

    }


    ~COpenGlWidget()
    {

    }


private:
    std::chrono::high_resolution_clock::time_point timePoint;
    QOpenGLShaderProgram *m_program = nullptr;
    int m_frame = 0;
    QTimer* timer = nullptr;

    Map map;

    //
    QOpenGLBuffer *m_vbo = nullptr;
    QOpenGLVertexArrayObject *m_vao = nullptr;


};


#endif // COPENGLWIDGET_H
