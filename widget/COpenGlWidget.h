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
#include <QCursor>

#include "basics/Camera.h"
#include <basics/Map.h>

class COpenGlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->type() == QEvent::Type::KeyPress)
        {
            keyBoard[event->nativeVirtualKey()] = true;
        }
    }

    void keyReleaseEvent(QKeyEvent *event) override
    {
        if (event->type() == QEvent::Type::KeyRelease)
        {
            keyBoard[event->key()] = false;
        }
    }

    void mouseMoveEvent(QMouseEvent *e) override
    {
        int dx = QCursor::pos().x() - 1920/2;
        int dy = QCursor::pos().y() - 1080/2;
        QCursor::setPos(1920/2,1080/2);
        camera.rotate(-1*(float)dy/5,-1*(float)dx/5);
    }

    void mousePressEvent(QMouseEvent *e) override
    {
        mouse[e->button()] = true;
    }
    void mouseReleaseEvent(QMouseEvent *e) override
    {
        mouse[e->button()] = false;
    }

    void initializeGL() override;
    void paintGL() override;
    void customInit();
    bool isCustomInitialized = false;

    bool keyProccess();
    std::array<std::shared_ptr<Triangle>*,2> pickingBlock();
    void simpleDraw();
    void drawBlock(std::array<unsigned char,4> ID);

    COpenGlWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()):QOpenGLWidget(parent,f), timer(new QTimer(this)), map(30,30,30)
    {
        QCursor::setPos(1920/2,1080/2);
        keyBoard.resize(1000);
        mouse.resize(100);
    }


    ~COpenGlWidget()
    {

    }


private:
    std::chrono::high_resolution_clock::time_point timePoint;
    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLShaderProgram *m_program_picking = nullptr;
    int m_frame = 0;
    QTimer* timer = nullptr;

    Map map;
    Camera camera;
    std::vector<bool> keyBoard;
    std::vector<bool> mouse;


    //
    QOpenGLBuffer *m_vbo = nullptr;
    QOpenGLVertexArrayObject *m_vao = nullptr;


};


#endif // COPENGLWIDGET_H
