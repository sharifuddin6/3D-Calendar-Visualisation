#include "assetloader.h"
#include "stdio.h"

AssetLoader::AssetLoader() {
  totalTextures = 1;
  textures = new GLuint[totalTextures];
}

void AssetLoader::loadAssets() {
  glGenTextures(totalTextures, textures);
//  loadTexturePNG(&textures[0], "asset/text.png");
//  loadTexture(&textures[1], "asset/terrain_texture/texture.jpeg");

}

GLuint AssetLoader::loadTexturePNG(GLuint *textureID, const char *filename) {
  // load texture
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glBindTexture(GL_TEXTURE_2D, *textureID);

  int width, height;
//  QImage tmpImage = QImage(filename, "PNG");
//  QImage image = QGLWidget::convertToGLFormat(tmpImage);

//  width = image.width();
//  height = image.height();

  //printf("[%d,%d]\n", width, height);

  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

  glEnable (GL_BLEND); // transparent blending
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
//               GL_UNSIGNED_BYTE, image.bits());

  return *textureID;
}

// getter
GLuint* AssetLoader::getTexture(int index) {
  return &textures[index];
}
