#include "InputManager.h"
#include "../Engine/Engine.h"
#include "../Engine/Inputs/Mouse.h"
#include "../Engine/Inputs/Keyboard.h"
#include "../Math/Vector3.h"

using namespace TFC::Engine::Physics;
using namespace TFC::Engine::Inputs;
using namespace TFC::Math;

InputManager::InputManager(RigidBody * rigidbody, int keyboardInput)
{
    _rigidbody = rigidbody;
    _keyboardInput = keyboardInput;
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
    if (_keyboardInput & WASD_PLAYER)
    {
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
    }

    if (_keyboardInput & IJKL_PLAYER)
    {
        if (Keyboard::Key(GLFW_KEY_I))
        {
            _rigidbody->AddForce(Vector3<float>(0.0, 20.0, 0.0));
        }
        if (Keyboard::Key(GLFW_KEY_J))
        {
            _rigidbody->AddForce(Vector3<float>(-20.0, 0.0, 0.0));

        }
        if (Keyboard::Key(GLFW_KEY_K))
        {
            _rigidbody->AddForce(Vector3<float>(0.0, -20.0, 0.0));

        }
        if (Keyboard::Key(GLFW_KEY_L))
        {
            _rigidbody->AddForce(Vector3<float>(20.0, 0.0, 0.0));
        }
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