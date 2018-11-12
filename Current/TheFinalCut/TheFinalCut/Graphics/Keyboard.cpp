#include "Keyboard.h"

bool TFC::Graphics::Keyboard::_keys[GLFW_KEY_LAST] = { 0 };
bool TFC::Graphics::Keyboard::_keysDown[GLFW_KEY_LAST] = { 0 };
bool TFC::Graphics::Keyboard::_keysUp[GLFW_KEY_LAST] = { 0 };

void TFC::Graphics::Keyboard::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
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

bool TFC::Graphics::Keyboard::KeyDown(int key)
{
    bool x = _keysDown[key];
    _keysDown[key] = false;
    return x;
}

bool TFC::Graphics::Keyboard::KeyUp(int key)
{
    bool x = _keysUp[key];
    _keysUp[key] = false;
    return x;
}

bool TFC::Graphics::Keyboard::Key(int key)
{
    return _keys[key];
}
