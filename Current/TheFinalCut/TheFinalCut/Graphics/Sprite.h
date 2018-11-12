#ifndef __SPRITE__H__
#define __SPRITE__H__

#include "GLFW/glfw3.h"
#include "Texture.h"
#include <iostream>
#include <string>
#include "../Math/Vector3.h"

namespace TFC
{
    namespace Graphics
    {
        class Sprite
        {
        public:
            Sprite();
            Sprite(std::string imagePath);
            Sprite(std::string imagePath, TFC::Math::Vector3<float>& pos);
            ~Sprite();

            void Update();
            void Render();

            void SpeedTo(float speed);
            void SpeedBy(float speed);
            void MoveTo(TFC::Math::Vector3<float>& v);
            void MoveBy(TFC::Math::Vector3<float>& v);
            void RotateTo(float rotation);
            void RotateBy(float rotation);
            void SetScale(float s);
            void SetScale(TFC::Math::Vector3<float>& v);

            void MoveLeft();
            void MoveRight();
            void MoveUp();
            void MoveDown();

        private:
            TFC::Graphics::Texture _texture;
            TFC::Math::Vector3<float> _pos;
            TFC::Math::Vector3<float> _scale;
            float _rotation;
            float _speed;
        };
    }
}

#endif  // __SPRITE__H__
