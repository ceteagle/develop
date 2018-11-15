#ifndef __RIGIDBODY__H__
#define __RIGIDBODY__H__

#include "../Graphics/Sprite.h"

namespace TFC
{
    namespace Engine
    {
        namespace Physics
        {
            class RigidBody : public Graphics::Sprite
            {
            public:
                RigidBody();
                void Initialize();
                RigidBody(std::string imagePath);
                RigidBody(std::string imagePath, TFC::Math::Vector3<float>& pos);
                ~RigidBody();

                void Update();
                void Render(TFC::Math::Vector3<float> color);

                void SetGravity(float gravity);
                void SetFriction(float friction);

                void AddForce(TFC::Math::Vector3<float> force);

            private:
                float _gravity;
                float _friction;
                TFC::Math::Vector3<float> _velocity;
            };
        }
    }
}
#endif  // __RIGIDBODY__H__
