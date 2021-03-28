#include "Cube.h"
#include "Triangle.h"

Cube::Cube(size_t ID)
{
    parts[0] = std::make_shared<Triangle>(Type::xDown, ID);
    parts[1] = std::make_shared<Triangle>(Type::xUp, ID);
    parts[2] = std::make_shared<Triangle>(Type::yDown, ID);
    parts[3] = std::make_shared<Triangle>(Type::yUp, ID);
    parts[4] = std::make_shared<Triangle>(Type::zDown, ID);
    parts[5] = std::make_shared<Triangle>(Type::zUp, ID);
}

Cube::Cube(const Type& type, size_t ID)
{
    parts[type] = std::make_shared<Triangle>(type, ID);
}

void Cube::setTriangle(const Type &type, size_t ID)
{

}

void Cube::draw(QOpenGLShaderProgram *m_program, QOpenGLFunctions* f)
{
    std::for_each(parts.begin(), parts.end(), [&m_program, &f](std::shared_ptr<Triangle>& current){
       if (current)
       {
           current->draw(m_program, f);
       }
    });
}

void Cube::getTriangle(const Type &type)
{

}
