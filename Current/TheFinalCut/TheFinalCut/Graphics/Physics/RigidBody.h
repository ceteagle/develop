#ifndef __RIGIDBODY__H__
#define __RIGIDBODY__H__

#include "../Sprite.h"

namespace TFC
{
    namespace Graphics
    {
        namespace Physics
        {
            class RigidBody : public Sprite
            {
            public:
                RigidBody();
                void Initialize();
                RigidBody(std::string imagePath);
                RigidBody(std::string imagePath, TFC::Math::Vector3<float>& pos);
                ~RigidBody();

                bool Initialize(float gravity, float friction);
                
                void Update();
                void Render(TFC::Math::Vector3<float> color);

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
