#ifndef TEXTURECONTAINER_H
#define TEXTURECONTAINER_H
#include <QOpenGLTexture>
#include <vector>

#include <bits/shared_ptr.h>

class TextureContainer final
{
public:
  static TextureContainer& Instance()
  {
      static TextureContainer me;
      return me;
  }
  std::vector<std::shared_ptr<QOpenGLTexture>> textures;




private:
  TextureContainer()
  {
      textures.emplace_back(std::make_shared<QOpenGLTexture>(QImage("C:\\Users\\Public\\Documents\\triangleCraft\\textures\\grass.jpg")));
      textures.emplace_back(std::make_shared<QOpenGLTexture>(QImage("C:\\Users\\Public\\Documents\\triangleCraft\\textures\\debug.jpg")));

      std::for_each(textures.begin(),textures.end(),[](std::shared_ptr<QOpenGLTexture>& current)
      {
          current->setMinificationFilter(QOpenGLTexture::Nearest);
          current->setMagnificationFilter(QOpenGLTexture::Linear);
          current->setWrapMode(QOpenGLTexture::Repeat);
      });
  }

  ~TextureContainer()
  {

  }
};


#endif // TEXTURECONTAINER_H
