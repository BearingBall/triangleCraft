#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <stdlib.h>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QColorDialog>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include "MeshShard.h"
#include <QVector3D>

enum Type{
    xDown,
    xUp,
    yDown,
    yUp,
    zDown,
    zUp
};

class Triangle final
{
public:
    Triangle(const Type& _type, size_t ID);
    ~Triangle();
    void draw(QOpenGLShaderProgram *m_program, QOpenGLFunctions* f);
    void drawWithoutTexture(QOpenGLShaderProgram *m_program, QOpenGLFunctions* f);
    void drawCalibratingTexture(QOpenGLShaderProgram *m_program, QOpenGLFunctions* f, QVector3D color);
    const Shard* getDataMesh()
    {
        return mesh.data();
    }
private:
    size_t triangleID;
    Type type;
    std::array<Shard,18> mesh;

    QOpenGLBuffer *m_vbo = nullptr;
    QOpenGLVertexArrayObject *m_vao = nullptr;

    void generateMesh();
    void generateTextureCoods();
    void generateNormals();
};


#endif // TRIANGLE_H
