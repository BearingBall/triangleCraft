#ifndef MESHSHARD_H
#define MESHSHARD_H
#include <QtMath>
#include <math.h>
#include <array>
#include <QOpenGLExtraFunctions>
#include <QVector3D>
#include <QVector2D>

class Shard final
{
public:
    std::array<GLfloat,3> vertex;
    std::array<GLfloat,3> normal;
    std::array<GLfloat,2> textureCoord;

    Shard() = default;
    ~Shard() = default;

    Shard(QVector3D& vector)
    {
        vertex[0] = vector.x();
        vertex[1] = vector.y();
        vertex[2] = vector.z();
    }

    void setVertex(const QVector3D& _vertex)
    {
        vertex[0] = _vertex.x();
        vertex[1] = _vertex.y();
        vertex[2] = _vertex.z();
    }

    void setTextureCoord(const QVector2D& _texture)
    {
        textureCoord[0] = _texture.x();
        textureCoord[1] = _texture.y();
    }
};

#endif // MESHSHARD_H
