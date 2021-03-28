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
    zUp,
    zDown,
    xUp,
    xDown,
    yUp,
    yDown
};

class Triangle final
{
public:
    Triangle(const Type& _type, size_t ID);
    ~Triangle() = default;
    void draw(QOpenGLShaderProgram *m_program, QOpenGLFunctions* f);
private:
    size_t triangleID;
    Type type;
    std::array<Shard,18> mesh;

    QOpenGLBuffer *m_vbo = nullptr;
    QOpenGLVertexArrayObject *m_vao = nullptr;

    void generateMesh();
    void generateTextureCoods();
};


#endif // TRIANGLE_H
