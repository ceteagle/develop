#include "Texture.h"
#include <iostream>

using namespace std;
using namespace TFC::Engine::Graphics;

Texture::Texture()
{
    _id = -1;
}

Texture::Texture(int id) : _id(id)
{
    if (!GetTextureParams())
    {
        cout << "Error loading image for ID : " << _id << endl;
    }
}

Texture::Texture(std::string path)
{
    _id = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA);
    if (!GetTextureParams())
    {
        cout << "Error loading image : " << path << endl;
    }
}

Texture::~Texture()
{
}

bool Texture::GetTextureParams()
{
    if (_id <= 0)
        return false;

    int mipLevel = 0;
    glBindTexture(GL_TEXTURE_2D, _id);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_WIDTH, &_width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_HEIGHT, &_height);

    return true;
}