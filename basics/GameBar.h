#ifndef GAMEBAR_H
#define GAMEBAR_H
#include "Camera.h"
#include "MeshShard.h"
#include "TextureContainer.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include "somethingFromC++17.h"

class GameBar final
{
private:
    unsigned int currentFrame = 0;
    unsigned int numberOfFrames = 6;
    float frameSize = 0.2;
    float frameWidth = 0.05;
    float sizeBetween = 0.23;
    float farness = 1;
    float downer = 0.45;
    float rotAddition = -50;
    float upUncurrent = 0.03;

    std::array<Shard,24> mesh;
    QOpenGLBuffer *m_vbo = nullptr;
    QOpenGLVertexArrayObject *m_vao = nullptr;

    void generateMesh();
    void generateNormals();
    void generateTexture();
public:
    GameBar();
    ~GameBar();

    void draw(QOpenGLShaderProgram *m_program, QOpenGLFunctions* f, Camera& camera);

    void nextItem();
    void previousItem();
    unsigned int currentID();

};

inline void GameBar::generateMesh()
{
    mesh[0].setVertex(QVector3D(-frameSize/2,-frameSize/2,0));
    mesh[1].setVertex(QVector3D(-frameSize/2,frameSize/2,0));
    mesh[2].setVertex(QVector3D(-frameSize/2+frameWidth,-frameSize/2,0));

    mesh[3].setVertex(QVector3D(-frameSize/2,frameSize/2,0));
    mesh[4].setVertex(QVector3D(-frameSize/2+frameWidth,frameSize/2,0));
    mesh[5].setVertex(QVector3D(-frameSize/2+frameWidth,-frameSize/2,0));

    mesh[6].setVertex(QVector3D(frameSize/2,-frameSize/2,0));
    mesh[7].setVertex(QVector3D(frameSize/2,frameSize/2,0));
    mesh[8].setVertex(QVector3D(frameSize/2-frameWidth,-frameSize/2,0));

    mesh[9].setVertex(QVector3D(frameSize/2,frameSize/2,0));
    mesh[10].setVertex(QVector3D(frameSize/2-frameWidth,frameSize/2,0));
    mesh[11].setVertex(QVector3D(frameSize/2-frameWidth,-frameSize/2,0));

    mesh[12].setVertex(QVector3D(-frameSize/2,frameSize/2,0));
    mesh[13].setVertex(QVector3D(frameSize/2,frameSize/2,0));
    mesh[14].setVertex(QVector3D(-frameSize/2,frameSize/2-frameWidth,0));

    mesh[15].setVertex(QVector3D(frameSize/2,frameSize/2,0));
    mesh[16].setVertex(QVector3D(frameSize/2,frameSize/2-frameWidth,0));
    mesh[17].setVertex(QVector3D(-frameSize/2,frameSize/2-frameWidth,0));

    mesh[18].setVertex(QVector3D(-frameSize/2,-frameSize/2,0));
    mesh[19].setVertex(QVector3D(frameSize/2,-frameSize/2,0));
    mesh[20].setVertex(QVector3D(-frameSize/2,-frameSize/2+frameWidth,0));

    mesh[21].setVertex(QVector3D(frameSize/2,-frameSize/2,0));
    mesh[22].setVertex(QVector3D(frameSize/2,-frameSize/2+frameWidth,0));
    mesh[23].setVertex(QVector3D(-frameSize/2,-frameSize/2+frameWidth,0));

}

inline void GameBar::generateNormals()
{
    for(int i=0;i<24;++i)
    {
        mesh[i].normal[0] = 0;
        mesh[i].normal[1] = 0;
        mesh[i].normal[2] = 1;
    }
}

inline void GameBar::generateTexture()
{
    for(int i=0;i<24;++i)
    {
        mesh[i].textureCoord[0] = (mesh[i].vertex[0]+frameSize/2)/frameSize;
        mesh[i].textureCoord[1] = (mesh[i].vertex[1]+frameSize/2)/frameSize;
    }
}

inline GameBar::GameBar()
{
    generateMesh();
    generateNormals();
    generateTexture();

    m_vao = new QOpenGLVertexArrayObject;
    if (m_vao->create())
        m_vao->bind();

    m_vbo = new QOpenGLBuffer;
    m_vbo->create();
    //m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo->bind();

    m_vbo->allocate(mesh.data(), mesh.size()*sizeof(Shard));

    m_vbo->release();
    m_vao->release();
}

inline GameBar::~GameBar()
{
    delete m_vao;
    delete m_vbo;
}
#include "QDebug"
inline void GameBar::draw(QOpenGLShaderProgram *m_program, QOpenGLFunctions *f, Camera &camera)
{
    //Fuck code
    delete m_vao;
    delete m_vbo;
    m_vao = new QOpenGLVertexArrayObject;
    if (m_vao->create())
    m_vao->bind();

    m_vbo = new QOpenGLBuffer;
    m_vbo->create();
    m_vbo->bind();

    m_vbo->allocate(mesh.data(), mesh.size()*sizeof(Shard));

    m_vbo->release();
    m_vao->release();
    //

    m_vao->bind();
    m_vbo->bind();

    for(int i = 0;i<numberOfFrames;++i)
    {

        float tetta = 180/M_PI*atan2(camera.getEye().y(),
                                     sqrt(camera.getEye().x()*camera.getEye().x()+camera.getEye().z()*camera.getEye().z()));
        float alpha = 180/M_PI*atan2(camera.getEye().x(),camera.getEye().z());

        tetta = clamp<float>(tetta, -89.9, 89.9);

        QMatrix4x4 rot;
        rot.rotate(tetta + rotAddition , camera.getRight());
        rot.rotate(alpha, QVector3D(0,1,0));

        m_program->setUniformValue("rotate", rot);
        QMatrix4x4 trans;
        trans.translate(camera.getPosBesideScreen(farness));
        trans.translate((-downer+(i!=currentFrame?0:upUncurrent))*camera.getHead());
        trans.translate(((frameSize+sizeBetween)*((numberOfFrames-1)*0.5-(numberOfFrames-1-i))/2)*camera.getRight());

        m_program->setUniformValue("translate", trans);


        m_program->enableAttributeArray("posAttr");
        m_program->setAttributeBuffer("posAttr", GL_FLOAT, offsetof(Shard, vertex), 3, sizeof(Shard));
        m_program->enableAttributeArray("textAttr");
        m_program->setAttributeBuffer("textAttr", GL_FLOAT, offsetof(Shard, textureCoord), 2, sizeof(Shard));
        m_program->enableAttributeArray("normAttr");
        m_program->setAttributeBuffer("normAttr", GL_FLOAT, offsetof(Shard, normal), 3, sizeof(Shard));


        m_program->setUniformValue("textureMap", 0);
        f->glActiveTexture(GL_TEXTURE0);
        TextureContainer::Instance().textures[2]->bind();
        m_program->setUniformValue("normalMap", 1);
        f->glActiveTexture(GL_TEXTURE1);
        TextureContainer::Instance().normalMaps[2]->bind();

        f->glDisable(GL_DEPTH_TEST);
        f->glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        f->glDrawArrays(GL_TRIANGLES, 0, 24);
    }
    m_vbo->release();
    m_vao->release();
}

inline void GameBar::nextItem()
{
    if (currentFrame+1 < numberOfFrames)
    {
        currentFrame++;
    }
}

inline void GameBar::previousItem()
{
    if (currentFrame > 0)
    {
        currentFrame--;
    }
}

inline unsigned int GameBar::currentID()
{
    if (currentFrame == 1)
        return 1;
    return 0;
}


#endif // GAMEBAR_H
