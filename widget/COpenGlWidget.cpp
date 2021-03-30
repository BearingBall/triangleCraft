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

    for(size_t i=0;i<10; ++i)
    {
        for(size_t j= 0; j< 10;++j)
        {
            map.getCube(i,0,j) = std::make_shared<Cube>(1);
            map.getCube(i,1,j) = std::make_shared<Cube>(0);
        }
    }
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
        DestroyBuildPointer tmp = pickingBlock();
        if (tmp.isDestroySeted)
        {
            (*tmp.destroy).reset();
            mouse[Qt::MouseButton::LeftButton] = false;
        }
    }
    if (mouse[Qt::MouseButton::RightButton])
    {
        DestroyBuildPointer tmp = pickingBlock();
        if (tmp.isBuildSeted)
        {
            (*tmp.build) = std::make_shared<Triangle>(tmp.buildType, 0);
            mouse[Qt::MouseButton::RightButton] = false;
        }
    }
}

DestroyBuildPointer COpenGlWidget::pickingBlock()
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
    DestroyBuildPointer destroyBuild;
    if (map.getCube(data[0],data[1],data[2]))
    {
        destroyBuild.destroy = map.getCube(data[0],data[1],data[2])->getTriangle(Type(data2[0]));
        destroyBuild.isDestroySeted = true;

        if ((data2[0] == 0 && data2[1] == 4)||(data2[0] == 1 && data2[1] == 4)||(data2[0] == 4 && data2[1] == 3)||(data2[0] == 5 && data2[1] == 3))
        {
             destroyBuild.build = map.getCube(data[0],data[1],data[2])->getTriangle(Type::yUp);
             destroyBuild.isBuildSeted = true;
             destroyBuild.buildType = Type::yUp;
        }
        if ((data2[0] == 1 && data2[1] == 2)||(data2[0] == 0 && data2[1] == 2)||(data2[0] == 5 && data2[1] == 5)||(data2[0] == 4 && data2[1] == 5))
        {
             destroyBuild.build = map.getCube(data[0],data[1],data[2])->getTriangle(Type::yDown);
             destroyBuild.isBuildSeted = true;
             destroyBuild.buildType = Type::yDown;
        }
        if ((data2[0] == 4 && data2[1] == 2)||(data2[0] == 5 && data2[1] == 2)||(data2[0] == 2 && data2[1] == 2)||(data2[0] == 3 && data2[1] == 2))
        {
             destroyBuild.build = map.getCube(data[0],data[1],data[2])->getTriangle(Type::xDown);
             destroyBuild.isBuildSeted = true;
             destroyBuild.buildType = Type::xDown;
        }
        if ((data2[0] == 2 && data2[1] == 4)||(data2[0] == 3 && data2[1] == 4)||(data2[0] == 5 && data2[1] == 4)||(data2[0] == 4 && data2[1] == 4))
        {
             destroyBuild.build = map.getCube(data[0],data[1],data[2])->getTriangle(Type::xUp);
             destroyBuild.isBuildSeted = true;
             destroyBuild.buildType = Type::xUp;
        }
        if ((data2[0] == 2 && data2[1] == 5)||(data2[0] == 1 && data2[1] == 5)||(data2[0] == 3 && data2[1] == 5)||(data2[0] == 0 && data2[1] == 5))
        {
             destroyBuild.build = map.getCube(data[0],data[1],data[2])->getTriangle(Type::zDown);
             destroyBuild.isBuildSeted = true;
             destroyBuild.buildType = Type::zDown;
        }
        if ((data2[0] == 2 && data2[1] == 3)||(data2[0] == 3 && data2[1] == 3)||(data2[0] == 0 && data2[1] == 3)||(data2[0] == 1 && data2[1] == 3))
        {
             destroyBuild.build = map.getCube(data[0],data[1],data[2])->getTriangle(Type::zUp);
             destroyBuild.isBuildSeted = true;
             destroyBuild.buildType = Type::zUp;
        }

        if (data2[0] == 0 && (data2[1] == 0 || data2[1] == 1))
        {
            if (map.isInRange(data[0]-1,data[1],data[2]))
            {
                if (!map.getCube(data[0]-1,data[1],data[2]))
                    map.getCube(data[0]-1,data[1],data[2]) = std::make_shared<Cube>();
                destroyBuild.buildType = Type::xUp;
                destroyBuild.build = map.getCube(data[0]-1,data[1],data[2])->getTriangle(destroyBuild.buildType);
                destroyBuild.isBuildSeted = true;
            }
        }
        if (data2[0] == 1 && (data2[1] == 0 || data2[1] == 1))
        {
            if (map.isInRange(data[0]+1,data[1],data[2]))
            {
                if (!map.getCube(data[0]+1,data[1],data[2]))
                    map.getCube(data[0]+1,data[1],data[2]) = std::make_shared<Cube>();
                destroyBuild.buildType = Type::xDown;
                destroyBuild.build = map.getCube(data[0]+1,data[1],data[2])->getTriangle(destroyBuild.buildType);
                destroyBuild.isBuildSeted = true;
            }
        }
        if (data2[0] == 2 && (data2[1] == 0 || data2[1] == 1))
        {
            if (map.isInRange(data[0],data[1]-1,data[2]))
            {
                if (!map.getCube(data[0],data[1]-1,data[2]))
                    map.getCube(data[0],data[1]-1,data[2]) = std::make_shared<Cube>();
                destroyBuild.buildType = Type::yUp;
                destroyBuild.build = map.getCube(data[0],data[1]-1,data[2])->getTriangle(destroyBuild.buildType);
                destroyBuild.isBuildSeted = true;
            }
        }
        if (data2[0] == 3 && (data2[1] == 0 || data2[1] == 1))
        {
            if (map.isInRange(data[0],data[1]+1,data[2]))
            {
                if (!map.getCube(data[0],data[1]+1,data[2]))
                    map.getCube(data[0],data[1]+1,data[2]) = std::make_shared<Cube>();
                destroyBuild.buildType = Type::yDown;
                destroyBuild.build = map.getCube(data[0],data[1]+1,data[2])->getTriangle(destroyBuild.buildType);
                destroyBuild.isBuildSeted = true;
            }
        }
        if (data2[0] == 4 && (data2[1] == 0 || data2[1] == 1))
        {
            if (map.isInRange(data[0],data[1],data[2]-1))
            {
                if (!map.getCube(data[0],data[1],data[2]-1))
                    map.getCube(data[0],data[1],data[2]-1) = std::make_shared<Cube>();
                destroyBuild.buildType = Type::zUp;
                destroyBuild.build = map.getCube(data[0],data[1],data[2]-1)->getTriangle(destroyBuild.buildType);
                destroyBuild.isBuildSeted = true;
            }
        }
        if (data2[0] == 5 && (data2[1] == 0 || data2[1] == 1))
        {
            if (map.isInRange(data[0],data[1],data[2]+1))
            {
                if (!map.getCube(data[0],data[1],data[2]+1))
                    map.getCube(data[0],data[1],data[2]+1) = std::make_shared<Cube>();
                destroyBuild.buildType = Type::zDown;
                destroyBuild.build = map.getCube(data[0],data[1],data[2]+1)->getTriangle(destroyBuild.buildType);
                destroyBuild.isBuildSeted = true;
            }
        }

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
