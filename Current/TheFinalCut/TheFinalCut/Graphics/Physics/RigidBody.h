#ifndef __RIGIDBODY__H__
#define __RIGIDBODY__H__

#include "../Sprite.h"

namespace TFC
{
    namespace Graphics
    {
        namespace Physics
        {
            class RigidBody
            {
            public:
                RigidBody();
                ~RigidBody();

                bool Initialize(float gravity, float friction, TFC::Graphics::Sprite& sprite);
                
                void Update();
                void Render(TFC::Math::Vector3<float> color);

                void AddForce(TFC::Math::Vector3<float> force);

            private:
                Sprite* _sprite;

                float _gravity;
                float _friction;
                TFC::Math::Vector3<float> _velocity;
            };
        }
    }
}
#endif  // __RIGIDBODY__H__
