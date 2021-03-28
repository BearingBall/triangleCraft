#ifndef CUBE_H
#define CUBE_H
#include <array>
#include "Triangle.h"

class Cube final
{
public:
    Cube(size_t ID);
    Cube(const Type& type, size_t ID);
    ~Cube() = default;

    void getTriangle(const Type& type);
    void setTriangle(const Type& type, size_t ID);
    void draw(QOpenGLShaderProgram *m_program, QOpenGLFunctions* f);
private:
    std::array<int,3> index;
    std::array<std::shared_ptr<Triangle>,6>parts;
};





#endif // CUBE_H
