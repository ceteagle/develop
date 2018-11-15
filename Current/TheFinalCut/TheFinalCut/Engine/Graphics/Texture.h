#ifndef __TEXTURE__H__
#define __TEXTURE__H__

#include "GLFW/glfw3.h"
#include "SOIL/src/SOIL.h"
#include <string>

namespace TFC
{
    namespace Engine
    {
        namespace Graphics
        {
            class Texture
            {
            public:
                Texture();
                Texture(int id);
                Texture(std::string path);
                ~Texture();

                int GetID() { return _id; }
                int GetWidth() { return _width; }
                int GetHeight() { return _height; }

            private:
                int _id;
                int _width;
                int _height;

                bool GetTextureParams();
            };
        }
    }
}
#endif  // __TEXTURE__H__

