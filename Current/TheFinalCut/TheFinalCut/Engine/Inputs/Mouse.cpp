#include "Mouse.h"

double TFC::Engine::Inputs::Mouse::_x = 0.0;
double TFC::Engine::Inputs::Mouse::_y = 0.0;
bool TFC::Engine::Inputs::Mouse::_buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool TFC::Engine::Inputs::Mouse::_buttonsDown[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool TFC::Engine::Inputs::Mouse::_buttonsUp[GLFW_MOUSE_BUTTON_LAST] = { 0 };

using namespace TFC::Engine::Inputs;

void Mouse::MousePosCallback(GLFWwindow* window, double x, double y)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    _x = x;
    _y = height - y;
}

void Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button < 0)
        return;
    if (action != GLFW_RELEASE && _buttons[button] == false)
    {
        _buttonsDown[button] = true;
        _buttonsUp[button] = false;
    }

    if (action != GLFW_RELEASE && _buttons[button] == true)
    {
        _buttonsDown[button] = false;
        _buttonsUp[button] = true;
    }

    _buttons[button] = action != GLFW_RELEASE;
}

double Mouse::GetX()
{
    return _x;
}

double Mouse::GetY()
{
    return _y;
}

bool Mouse::ButtonDown(int button)
{
    bool x = _buttonsDown[button];
    _buttonsDown[button] = false;
    return x;
}

bool Mouse::ButtonUp(int button)
{
    bool x = _buttonsUp[button];
    _buttonsUp[button] = false;
    return x;
}

bool Mouse::Button(int button)
{
    return _buttons[button];
}
