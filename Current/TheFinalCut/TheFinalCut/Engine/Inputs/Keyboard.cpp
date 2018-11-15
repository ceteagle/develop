#include "Keyboard.h"

bool TFC::Engine::Inputs::Keyboard::_keys[GLFW_KEY_LAST] = { 0 };
bool TFC::Engine::Inputs::Keyboard::_keysDown[GLFW_KEY_LAST] = { 0 };
bool TFC::Engine::Inputs::Keyboard::_keysUp[GLFW_KEY_LAST] = { 0 };

using namespace TFC::Engine::Inputs;

void Keyboard::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    if (key < 0)
        return;

    if (action != GLFW_RELEASE && _keys[key] == false)
    {
        _keysDown[key] = true;
        _keysUp[key] = false;
    }
    if (action != GLFW_RELEASE && _keys[key] == true)
    {
        _keysDown[key] = false;
        _keysUp[key] = true;
    }

    _keys[key] = action != GLFW_RELEASE;
}

bool Keyboard::KeyDown(int key)
{
    bool x = _keysDown[key];
    _keysDown[key] = false;
    return x;
}

bool Keyboard::KeyUp(int key)
{
    bool x = _keysUp[key];
    _keysUp[key] = false;
    return x;
}

bool Keyboard::Key(int key)
{
    return _keys[key];
}
