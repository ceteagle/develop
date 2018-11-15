#ifndef __SPRITE__H__
#define __SPRITE__H__

#include "GLFW/glfw3.h"
#include "Texture.h"
#include <string>
#include "../../Math/Vector3.h"
#include "../../Math/Rectangle.h"

namespace TFC { namespace Engine { namespace Physics { class RigidBody; } } }

namespace TFC
{
    namespace Engine
    {
        namespace Graphics
        {
            class Sprite
            {
                friend class TFC::Engine::Physics::RigidBody;

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

                TFC::Math::Vector3<float> GetSize();
                void SetBoundingBoxColor(TFC::Math::Vector3<float>& color);

                virtual TFC::Math::Rectangle & GetBoundingBox();

            protected:
                TFC::Math::Vector3<float> _scale;
                TFC::Engine::Graphics::Texture _texture;

                float _rotation;

            private:
                TFC::Math::Rectangle _boundingBox;

                float _speed;
            };
        }
    }
}

#endif  // __SPRITE__H__
