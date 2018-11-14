#include "InputManager.h"
#include "Graphics/Mouse.h"
#include "Graphics/Keyboard.h"
#include "Math/Vector3.h"

using namespace TFC::Graphics;
using namespace TFC::Math;

InputManager::InputManager(TFC::Graphics::Physics::RigidBody * rigidbody)
{
    _rigidbody = rigidbody;
    _exit = false;
}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
      // MOUSE EVENTS
        if (Mouse::ButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        {
            _rigidbody->RotateBy(100.0);
        }
        if (Mouse::ButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
        {
            _rigidbody->RotateBy(-100.0);
        }
        if (Mouse::Button(GLFW_MOUSE_BUTTON_MIDDLE))
        {
            _rigidbody->RotateBy(100.0);
        }
   

    // KEYBOARD EVENTS
        if (Keyboard::Key(GLFW_KEY_W))
        {
            _rigidbody->AddForce(Vector3<float>(0.0, 20.0, 0.0));
        }
        if (Keyboard::Key(GLFW_KEY_A))
        {
            _rigidbody->AddForce(Vector3<float>(-20.0, 0.0, 0.0));

        }
        if (Keyboard::Key(GLFW_KEY_S))
        {
            _rigidbody->AddForce(Vector3<float>(0.0, -20.0, 0.0));

        }
        if (Keyboard::Key(GLFW_KEY_D))
        {
            _rigidbody->AddForce(Vector3<float>(20.0, 0.0, 0.0));
        }
        if (Keyboard::Key(GLFW_KEY_ESCAPE))
        {
            _exit = true;
        }
}

bool InputManager::CanExit()
{
    return _exit;
}