#include "Triangle.h"
#include "TextureContainer.h"

Triangle::Triangle(const Type& _type, size_t ID)
{
    type = _type;
    triangleID = ID;
    generateMesh();
    generateTextureCoods();

    m_vao = new QOpenGLVertexArrayObject();
    if (m_vao->create())
        m_vao->bind();

    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo->create();
    m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo->bind();

    m_vbo->allocate(mesh.data(), mesh.size()*sizeof(Shard));
}

void Triangle::draw(QOpenGLShaderProgram *m_program, QOpenGLFunctions* f)
{
    m_vbo->bind();
    m_vao->bind();
    m_program->enableAttributeArray("posAttr");
    m_program->setAttributeBuffer("posAttr", GL_FLOAT, offsetof(Shard, vertex), 3, sizeof(Shard));
    m_program->enableAttributeArray("textAttr");
    m_program->setAttributeBuffer("textAttr", GL_FLOAT, offsetof(Shard, textureCoord), 2, sizeof(Shard));

    TextureContainer::Instance().textures[triangleID]->bind();
    m_program->setUniformValue("textureMap", 0);
    f->glActiveTexture(GL_TEXTURE0);

    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    f->glDrawArrays(GL_TRIANGLES, 0, 18);

    /*
    if (lines)
    {
        m_program->setUniformValue(m_colAttr, QVector3D(0.5,0.5,0.5));
        glPolygonOffset(1.0f, 1.0f);
        glDisable(GL_POLYGON_OFFSET_FILL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, vertexCounter);
    }
    */
}

void Triangle::drawWithoutTexture(QOpenGLShaderProgram *m_program, QOpenGLFunctions *f)
{
    m_vbo->bind();
    m_vao->bind();
    m_program->enableAttributeArray("posAttr");
    m_program->setAttributeBuffer("posAttr", GL_FLOAT, offsetof(Shard, vertex), 3, sizeof(Shard));

    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    f->glDrawArrays(GL_TRIANGLES, 0, 18);
}

void Triangle::drawCalibratingTexture(QOpenGLShaderProgram *m_program, QOpenGLFunctions *f, QVector3D color)
{
    m_vbo->bind();
    m_vao->bind();
    m_program->enableAttributeArray("posAttr");
    m_program->setAttributeBuffer("posAttr", GL_FLOAT, offsetof(Shard, vertex), 3, sizeof(Shard));

    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for(size_t i=0;i<6;++i)
    {
        color.setY(static_cast<float>(i)/255);
        m_program->setUniformValue("textAttr", color);
        f->glDrawArrays(GL_TRIANGLES, i*3, 3);
    }

}

void Triangle::generateMesh()
{
    QVector3D A;
    QVector3D B;
    QVector3D C;
    QVector3D D;
    QVector3D E;

    if (type == Type::yDown)
    {
        A = QVector3D(-0.5,-0.5,-0.5);
        B = QVector3D(-0.5,-0.5,0.5);
        C = QVector3D(0.5,-0.5,0.5);
        D = QVector3D(0.5,-0.5,-0.5);
        E = QVector3D(0,0,0);
    }

    if (type == Type::yUp)
    {
        A = QVector3D(-0.5,0.5,-0.5);
        B = QVector3D(-0.5,0.5,0.5);
        C = QVector3D(0.5,0.5,0.5);
        D = QVector3D(0.5,0.5,-0.5);
        E = QVector3D(0,0,0);
    }
    if (type == Type::xDown)
    {
        A = QVector3D(-0.5,-0.5,-0.5);
        B = QVector3D(-0.5,-0.5,0.5);
        C = QVector3D(-0.5,0.5,0.5);
        D = QVector3D(-0.5,0.5,-0.5);
        E = QVector3D(0,0,0);
    }
    if (type == Type::xUp)
    {
        A = QVector3D(0.5,-0.5,-0.5);
        B = QVector3D(0.5,-0.5,0.5);
        C = QVector3D(0.5,0.5,0.5);
        D = QVector3D(0.5,0.5,-0.5);
        E = QVector3D(0,0,0);
    }
    if (type == Type::zDown)
    {
        A = QVector3D(-0.5,-0.5,-0.5);
        B = QVector3D(-0.5,0.5,-0.5);
        C = QVector3D(0.5,0.5,-0.5);
        D = QVector3D(0.5,-0.5,-0.5);
        E = QVector3D(0,0,0);
    }
    if (type == Type::zUp)
    {
        A = QVector3D(-0.5,-0.5,0.5);
        B = QVector3D(-0.5,0.5,0.5);
        C = QVector3D(0.5,0.5,0.5);
        D = QVector3D(0.5,-0.5,0.5);
        E = QVector3D(0,0,0);
    }

    mesh[0].setVertex(A);
    mesh[1].setVertex(B);
    mesh[2].setVertex(C);
    mesh[3].setVertex(C);
    mesh[4].setVertex(D);
    mesh[5].setVertex(A);
    mesh[6].setVertex(E);
    mesh[7].setVertex(A);
    mesh[8].setVertex(B);
    mesh[9].setVertex(E);
    mesh[10].setVertex(B);
    mesh[11].setVertex(C);
    mesh[12].setVertex(E);
    mesh[13].setVertex(C);
    mesh[14].setVertex(D);
    mesh[15].setVertex(E);
    mesh[16].setVertex(D);
    mesh[17].setVertex(A);
}

void Triangle::generateTextureCoods()
{
    if (type == Type::yDown)
    {
        mesh[0].setTextureCoord(QVector2D(128.0/512,256.0/384));
        mesh[1].setTextureCoord(QVector2D(128.0/512,384.0/384));
        mesh[2].setTextureCoord(QVector2D(256.0/512,384.0/384));
        mesh[3].setTextureCoord(QVector2D(256.0/512,384.0/384));
        mesh[4].setTextureCoord(QVector2D(256.0/512,256.0/384));
        mesh[5].setTextureCoord(QVector2D(128.0/512,256.0/384));
        mesh[6].setTextureCoord(QVector2D(64.0/512,128.0/384));
        mesh[7].setTextureCoord(QVector2D(128.0/512,256.0/384));
        mesh[8].setTextureCoord(QVector2D(0.0/512,256.0/384));
        mesh[9].setTextureCoord(QVector2D((384.0+64.0)/512,128.0/384));
        mesh[10].setTextureCoord(QVector2D(512.0/512,256.0/384));
        mesh[11].setTextureCoord(QVector2D(386.0/512,256.0/384));
        mesh[12].setTextureCoord(QVector2D((256.0+64.0)/512,128.0/384));
        mesh[13].setTextureCoord(QVector2D(384.0/512,256.0/384));
        mesh[14].setTextureCoord(QVector2D(256.0/512,256.0/384));
        mesh[15].setTextureCoord(QVector2D((128.0+64.0)/512,128.0/384));
        mesh[16].setTextureCoord(QVector2D(256.0/512,256.0/384));
        mesh[17].setTextureCoord(QVector2D(128.0/512,256.0/384));
    }
    if (type == Type::yUp)
    {
        mesh[0].setTextureCoord(QVector2D(128.0/512,0.0/384));
        mesh[1].setTextureCoord(QVector2D(128.0/512,128.0/384));
        mesh[2].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[3].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[4].setTextureCoord(QVector2D(256.0/512,0.0/384));
        mesh[5].setTextureCoord(QVector2D(128.0/512,0.0/384));
        mesh[6].setTextureCoord(QVector2D(64.0/512,256.0/384));
        mesh[7].setTextureCoord(QVector2D(0.0/512,128.0/384));
        mesh[8].setTextureCoord(QVector2D(128.0/512,128.0/384));
        mesh[9].setTextureCoord(QVector2D((128.0+64.0)/512,256.0/384));
        mesh[10].setTextureCoord(QVector2D(128.0/512,128.0/384));
        mesh[11].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[12].setTextureCoord(QVector2D((256.0+64.0)/512,256.0/384));
        mesh[13].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[14].setTextureCoord(QVector2D(384.0/512,128.0/384));
        mesh[15].setTextureCoord(QVector2D((384.0+64.0)/512,256.0/384));
        mesh[16].setTextureCoord(QVector2D(384.0/512,128.0/384));
        mesh[17].setTextureCoord(QVector2D(512.0/512,128.0/384));
    }
    if (type == Type::xDown)
    {
        mesh[0].setTextureCoord(QVector2D(0.0/512,256.0/384));
        mesh[1].setTextureCoord(QVector2D(128.0/512,256.0/384));
        mesh[2].setTextureCoord(QVector2D(128.0/512,128.0/384));
        mesh[3].setTextureCoord(QVector2D(128.0/512,128.0/384));
        mesh[4].setTextureCoord(QVector2D(0.0/512,128.0/384));
        mesh[5].setTextureCoord(QVector2D(0.0/512,256.0/384));
        mesh[6].setTextureCoord(QVector2D(256.0/512,(256.0+64.0)/384));
        mesh[7].setTextureCoord(QVector2D(128.0/512,384.0/384));
        mesh[8].setTextureCoord(QVector2D(128.0/512,256.0/384));
        mesh[9].setTextureCoord(QVector2D(256.0/512,(128.0+64.0)/384));
        mesh[10].setTextureCoord(QVector2D(128.0/512,256.0/384));
        mesh[11].setTextureCoord(QVector2D(128.0/512,128.0/384));
        mesh[12].setTextureCoord(QVector2D(256.0/512,(64.0)/384));
        mesh[13].setTextureCoord(QVector2D(128.0/512,128.0/384));
        mesh[14].setTextureCoord(QVector2D(128.0/512,0.0/384));
        mesh[15].setTextureCoord(QVector2D(384.0/512,(128.0+64.0)/384));
        mesh[16].setTextureCoord(QVector2D(512.0/512,128.0/384));
        mesh[17].setTextureCoord(QVector2D(512.0/512,256.0/384));
    }
    if (type == Type::xUp)
    {
        mesh[0].setTextureCoord(QVector2D(384.0/512,256.0/384));
        mesh[1].setTextureCoord(QVector2D(256.0/512,256.0/384));
        mesh[2].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[3].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[4].setTextureCoord(QVector2D(384.0/512,128.0/384));
        mesh[5].setTextureCoord(QVector2D(384.0/512,256.0/384));
        mesh[6].setTextureCoord(QVector2D(128.0/512,(256.0+64.0)/384));
        mesh[7].setTextureCoord(QVector2D(256.0/512,384.0/384));
        mesh[8].setTextureCoord(QVector2D(256.0/512,256.0/384));
        mesh[9].setTextureCoord(QVector2D(128.0/512,(128.0+64.0)/384));
        mesh[10].setTextureCoord(QVector2D(256.0/512,256.0/384));
        mesh[11].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[12].setTextureCoord(QVector2D(128.0/512,(64.0)/384));
        mesh[13].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[14].setTextureCoord(QVector2D(256.0/512,0.0/384));
        mesh[15].setTextureCoord(QVector2D(512.0/512,(128.0+64.0)/384));
        mesh[16].setTextureCoord(QVector2D(384.0/512,128.0/384));
        mesh[17].setTextureCoord(QVector2D(384.0/512,256.0/384));
    }
    if (type == Type::zDown)
    {
        mesh[0].setTextureCoord(QVector2D(128.0/512,256.0/384));
        mesh[1].setTextureCoord(QVector2D(128.0/512,128.0/384));
        mesh[2].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[3].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[4].setTextureCoord(QVector2D(256.0/512,256.0/384));
        mesh[5].setTextureCoord(QVector2D(128.0/512,256.0/384));
        mesh[6].setTextureCoord(QVector2D(0.0/512,(128.0+64.0)/384));
        mesh[7].setTextureCoord(QVector2D(128.0/512,256.0/384));
        mesh[8].setTextureCoord(QVector2D(128.0/512,128.0/384));
        mesh[9].setTextureCoord(QVector2D((128.0+64.0)/512,0.0/384));
        mesh[10].setTextureCoord(QVector2D(128.0/512,128.0/384));
        mesh[11].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[12].setTextureCoord(QVector2D(384.0/512,(128.0+64.0)/384));
        mesh[13].setTextureCoord(QVector2D(256.0/512,128.0/384));
        mesh[14].setTextureCoord(QVector2D(256.0/512,256.0/384));
        mesh[15].setTextureCoord(QVector2D((128.0+64.0)/512,384.0/384));
        mesh[16].setTextureCoord(QVector2D(256.0/512,256.0/384));
        mesh[17].setTextureCoord(QVector2D(128.0/512,256.0/384));
    }
    if (type == Type::zUp)
    {
        mesh[0].setTextureCoord(QVector2D(512.0/512,256.0/384));
        mesh[1].setTextureCoord(QVector2D(512.0/512,128.0/384));
        mesh[2].setTextureCoord(QVector2D(384.0/512,128.0/384));
        mesh[3].setTextureCoord(QVector2D(384.0/512,128.0/384));
        mesh[4].setTextureCoord(QVector2D(384.0/512,256.0/384));
        mesh[5].setTextureCoord(QVector2D(512.0/512,256.0/384));
        mesh[6].setTextureCoord(QVector2D(128.0/512,(128.0+64.0)/384));
        mesh[7].setTextureCoord(QVector2D(0.0/512,256.0/384));
        mesh[8].setTextureCoord(QVector2D(0.0/512,128.0/384));
        mesh[9].setTextureCoord(QVector2D((128.0+64.0)/512,128.0/384));
        mesh[10].setTextureCoord(QVector2D(128.0/512,0.0/384));
        mesh[11].setTextureCoord(QVector2D(256.0/512,0.0/384));
        mesh[12].setTextureCoord(QVector2D(256.0/512,(128.0+64.0)/384));
        mesh[13].setTextureCoord(QVector2D(384.0/512,128.0/384));
        mesh[14].setTextureCoord(QVector2D(384.0/512,256.0/384));
        mesh[15].setTextureCoord(QVector2D((128.0+64.0)/512,256.0/384));
        mesh[16].setTextureCoord(QVector2D(256.0/512,384.0/384));
        mesh[17].setTextureCoord(QVector2D(128.0/512,384.0/384));
    }
}
