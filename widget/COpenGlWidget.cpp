#include "COpenGlWidget.h"

void COpenGlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:\\Users\\Public\\Documents\\triangleCraft\\vsh.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:\\Users\\Public\\Documents\\triangleCraft\\fsh.glsl");
    m_program->link();

    //map.getCube(1,0,1) = std::make_shared<Cube>(0);
    m_vao = new QOpenGLVertexArrayObject;
    if (m_vao->create())
        m_vao->bind();
    m_vbo = new QOpenGLBuffer;
    m_vbo->create();
    m_vbo->bind();

    Shard* mesh = new Shard[3];
    mesh[0].setVertex(QVector3D(0,0,0));
    mesh[1].setVertex(QVector3D(1,0,1));
    mesh[2].setVertex(QVector3D(0,1,0));

    QMatrix4x4 matrix2;
    matrix2.translate(2,0,-2);
    matrix2.rotate(static_cast<float>(m_frame)/10,{0,1,0});
    m_program->setUniformValue("translate", matrix2);

    m_vao->bind();
    m_vbo->bind();
    m_vbo->allocate(mesh, 3*sizeof(Shard));
    m_program->enableAttributeArray("posAttr");
    m_program->setAttributeBuffer("posAttr", GL_FLOAT, offsetof(Shard, vertex), 3, sizeof(Shard));
    m_vbo->release();
}

void COpenGlWidget::paintGL()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    m_vao->bind();
    m_program->bind();

    std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeSpan =
            std::chrono::duration_cast<std::chrono::duration<double>> (timePoint2-timePoint);


    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    //matrix.lookAt(QVector3D(0,0,0), QVector3D(1,0,1), QVector3D(0,1,0));
    m_program->setUniformValue("perspective", matrix);

    ///

    m_vao->bind();
    m_vbo->bind();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 18);

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
