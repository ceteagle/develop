#ifndef __INPUT_MANAGER__H__
#define __INPUT_MANAGER__H__

#include "../Engine/Physics/RigidBody.h"

class InputManager
{
public:
    InputManager(TFC::Engine::Physics::RigidBody * rigidbody, int keyboardInput);
    ~InputManager();

    void Update();
    bool CanExit();

private:
    TFC::Engine::Physics::RigidBody * _rigidbody;
    int _keyboardInput;
    bool _exit;
};

#endif  // __INPUT_MANAGER__H__
