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
  std::vector<std::shared_ptr<QOpenGLTexture>> normalMaps;



private:
  TextureContainer()
  {
      textures.emplace_back(std::make_shared<QOpenGLTexture>(QImage("C:\\Users\\Public\\Documents\\triangleCraft\\textures\\grass.jpg")));
      normalMaps.emplace_back(std::make_shared<QOpenGLTexture>(QImage("C:\\Users\\Public\\Documents\\triangleCraft\\textures\\grassNormal.png")));
      textures.emplace_back(std::make_shared<QOpenGLTexture>(QImage("C:\\Users\\Public\\Documents\\triangleCraft\\textures\\cobblestoneblock.png")));
      normalMaps.emplace_back(std::make_shared<QOpenGLTexture>(QImage("C:\\Users\\Public\\Documents\\triangleCraft\\textures\\cobblestoneblockNormal.png")));
      textures.emplace_back(std::make_shared<QOpenGLTexture>(QImage("C:\\Users\\Public\\Documents\\triangleCraft\\textures\\barFrame.jpg")));
      normalMaps.emplace_back(std::make_shared<QOpenGLTexture>(QImage("C:\\Users\\Public\\Documents\\triangleCraft\\textures\\barFrameNormal.png")));


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
