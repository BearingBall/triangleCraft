#include "COpenGlWidget.h"

void COpenGlWidget::initializeGL()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1);
    initializeOpenGLFunctions();
}

void COpenGlWidget::paintGL()
{
    customInit();
    keyProccess();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    simpleDraw();
    ++m_frame;
}

void COpenGlWidget::customInit()
{
    if (isCustomInitialized)
        return;
    isCustomInitialized = true;

    m_program_picking = new QOpenGLShaderProgram(this);
    m_program_picking->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:\\Users\\Public\\Documents\\triangleCraft\\vshPicking.glsl");
    m_program_picking->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:\\Users\\Public\\Documents\\triangleCraft\\fshPicking.glsl");
    m_program_picking->link();

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:\\Users\\Public\\Documents\\triangleCraft\\vsh.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:\\Users\\Public\\Documents\\triangleCraft\\fsh.glsl");
    m_program->link();

    map.getCube(1,4,1) = std::make_shared<Cube>(Type::yDown, 1);
    map.getCube(1,6,1) = std::make_shared<Cube>(Type::yUp, 1);
    map.getCube(2,5,1) = std::make_shared<Cube>(Type::xUp, 1);
    map.getCube(0,5,1) = std::make_shared<Cube>(Type::xDown, 1);
    map.getCube(1,5,2) = std::make_shared<Cube>(Type::zUp, 1);
    map.getCube(1,5,0) = std::make_shared<Cube>(Type::zDown, 1);

    map.getCube(1,0,0) = std::make_shared<Cube>(0);
    map.getCube(2,0,0) = std::make_shared<Cube>(0);
    map.getCube(3,0,0) = std::make_shared<Cube>(0);
    map.getCube(4,0,0) = std::make_shared<Cube>(0);
    map.getCube(0,0,1) = std::make_shared<Cube>(0);
    map.getCube(0,0,2) = std::make_shared<Cube>(0);
    map.getCube(0,0,3) = std::make_shared<Cube>(0);
    map.getCube(0,0,4) = std::make_shared<Cube>(0);
}

bool COpenGlWidget::keyProccess()
{
    if (keyBoard[Qt::Key::Key_W])
    {
        camera.step(0.1,0);
    }
    if (keyBoard[Qt::Key::Key_S])
    {
        camera.step(-0.1,0);
    }
    if (keyBoard[Qt::Key::Key_A])
    {
        camera.step(0,-0.1);
    }
    if (keyBoard[Qt::Key::Key_D])
    {
        camera.step(0,0.1);
    }
    if (mouse[Qt::MouseButton::LeftButton])
    {
        std::array<std::shared_ptr<Triangle>*,2> tmp = pickingBlock();
        if (tmp[0])
        {
            qDebug()<<"trying to destroy \n";
            tmp[0]->reset();
            mouse[Qt::MouseButton::LeftButton] = false;
        }
    }
}

std::array<std::shared_ptr<Triangle>*,2> COpenGlWidget::pickingBlock()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    m_program_picking->bind();
    m_program_picking->setUniformValue("perspective", camera.getPerspective());
    m_program_picking->setUniformValue("view", camera.getView());
    map.drawWithoutTexture(m_program_picking,this);
    m_program->release();
    glFlush();
    glFinish();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    std::array<unsigned char,4> data;
    glReadPixels(QCursor::pos().x(), QCursor::pos().y()-80,1,1, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    data[0] -= 1;
    data[1] -= 1;
    data[2] -= 1;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    qDebug()<<data[0]<<" "<<data[1]<<" "<<data[2]<<"\n";

    std::array<unsigned char,4> data2;
    if (map.getCube(data[0],data[1],data[2]))
    {
      m_program_picking->bind();
      m_program_picking->setUniformValue("perspective", camera.getPerspective());
      m_program_picking->setUniformValue("view", camera.getView());
      QMatrix4x4 matrix;
      matrix.translate(data[0],data[1],data[2]);
      m_program_picking->setUniformValue("translate", matrix);
      map.getCube(data[0],data[1],data[2])->drawCalibratingTexture(m_program_picking,this);
      glFlush();
      glFinish();
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glReadPixels(QCursor::pos().x(), QCursor::pos().y()-80,1,1, GL_RGBA, GL_UNSIGNED_BYTE, data2.data());
      qDebug()<<data2[0]<<" "<<data2[1]<<"\n";
    }
    std::array<std::shared_ptr<Triangle>*,2> destroyBuild;
    if (map.getCube(data[0],data[1],data[2]))
    {
        destroyBuild[0] = map.getCube(data[0],data[1],data[2])->getTriangle(Type(data2[0]));
    }
    return destroyBuild;
}

void COpenGlWidget::simpleDraw()
{
    m_program->bind();
    m_program->setUniformValue("perspective", camera.getPerspective());
    m_program->setUniformValue("view", camera.getView());

    map.draw(m_program,this);

    m_program->release();
}
