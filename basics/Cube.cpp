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
    if (!parts[type])
        parts[type] = std::make_shared<Triangle>(type, ID);
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

void Cube::drawWithoutTexture(QOpenGLShaderProgram *m_program, QOpenGLFunctions *f)
{
    std::for_each(parts.begin(), parts.end(), [&m_program, &f](std::shared_ptr<Triangle>& current){
       if (current)
       {
           current->drawWithoutTexture(m_program, f);
       }
    });
}

void Cube::drawCalibratingTexture(QOpenGLShaderProgram *m_program, QOpenGLFunctions *f)
{
    for(size_t i = 0; i<6; ++i)
    {
        if (parts[i])
        {
            QVector3D color(static_cast<float>(i)/255,0,1);
            parts[i]->drawCalibratingTexture(m_program,f,color);
        }
    }
}

std::shared_ptr<Triangle>* Cube::getTriangle(const Type &type)
{
    return &parts[type];
}
