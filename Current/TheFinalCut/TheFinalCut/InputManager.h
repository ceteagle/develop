#ifndef __INPUT_MANAGER__H__
#define __INPUT_MANAGER__H__

#include "Graphics/Physics/RigidBody.h"

class InputManager
{
public:
    InputManager(TFC::Graphics::Physics::RigidBody * rigidbody);
    ~InputManager();

    void Update();
    bool CanExit();

private:
    TFC::Graphics::Physics::RigidBody * _rigidbody;
    bool _exit;
};

#endif  // __INPUT_MANAGER__H__
