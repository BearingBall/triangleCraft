#ifndef MAP_H
#define MAP_H
#include "Cube.h"
#include <memory>


class Map final
{
public:
    Map(size_t x, size_t y, size_t z);
    ~Map() = default;
    std::shared_ptr<Cube>& getCube(size_t x, size_t y, size_t z);
    void draw(QOpenGLShaderProgram *m_program, QOpenGLFunctions* f);
private:
    std::array<size_t, 3> mapSize;
    std::vector<std::shared_ptr<Cube>> map;
};

inline Map::Map(size_t x, size_t y, size_t z)
{
    mapSize[0] = x;
    mapSize[1] = y;
    mapSize[2] = z;
    map.resize(x*y*z);
}

inline std::shared_ptr<Cube>& Map::getCube(size_t x, size_t y, size_t z)
{
    return map[x+y*mapSize[0]+z*mapSize[0]*mapSize[1]];
}

inline void Map::draw(QOpenGLShaderProgram *m_program, QOpenGLFunctions* f)
{
    for(size_t i=0; i<mapSize[0]; ++i)
        for(size_t j=0; j<mapSize[1]; ++j)
            for(size_t k =0; k<mapSize[2];++k)
            {
                if (getCube(i,j,k))
                {
                    QMatrix4x4 matrix;
                    matrix.translate(i,j,k);
                    m_program->setUniformValue("translate", matrix);
                    getCube(i,j,k)->draw(m_program, f);
                }
            }
}




#endif // MAP_H
