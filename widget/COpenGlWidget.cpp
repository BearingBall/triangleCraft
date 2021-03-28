#include "COpenGlWidget.h"

void COpenGlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:\\Users\\Public\\Documents\\triangleCraft\\vsh.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:\\Users\\Public\\Documents\\triangleCraft\\fsh.glsl");
    m_program->link();

    //map.getCube(0,0,0) = std::make_shared<Cube>(0);
}

void COpenGlWidget::paintGL()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeSpan =
            std::chrono::duration_cast<std::chrono::duration<double>> (timePoint2-timePoint);


    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    m_program->setUniformValue("perspective", matrix);

    //map.draw(m_program,this);
/*
    if (timeSpan.count() > 0.5f)
    {
        timePoint = std::chrono::high_resolution_clock::now();
        fps = static_cast<float>(frames)/timeSpan.count();
        fpsLabel->setText( std::to_string(fps).c_str());
        frames = 0;
    }
    ++frames;
*/

    m_program->release();
    ++m_frame;
}
