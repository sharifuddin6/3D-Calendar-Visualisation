#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <GL/glut.h>

class AssetLoader {

  public:
    // constructor
    AssetLoader();

    // methods
    void loadAssets();

    GLuint loadTexturePNG(GLuint *textureID, const char *filename);

    // getter
    GLuint *getTexture(int index);

  private:
    // variables
    int totalTextures;
    GLuint *textures;

};

#endif // ASSETLOADER_H

