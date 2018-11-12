#include "Mouse.h"

double TFC::Graphics::Mouse::_x = 0.0;
double TFC::Graphics::Mouse::_y = 0.0;
bool TFC::Graphics::Mouse::_buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool TFC::Graphics::Mouse::_buttonsDown[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool TFC::Graphics::Mouse::_buttonsUp[GLFW_MOUSE_BUTTON_LAST] = { 0 };

void TFC::Graphics::Mouse::MousePosCallback(GLFWwindow* window, double x, double y)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    _x = x;
    _y = height - y;
}

void TFC::Graphics::Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
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

double TFC::Graphics::Mouse::GetX()
{
    return _x;
}

double TFC::Graphics::Mouse::GetY()
{
    return _y;
}

bool TFC::Graphics::Mouse::ButtonDown(int button)
{
    bool x = _buttonsDown[button];
    _buttonsDown[button] = false;
    return x;
}

bool TFC::Graphics::Mouse::ButtonUp(int button)
{
    bool x = _buttonsUp[button];
    _buttonsUp[button] = false;
    return x;
}

bool TFC::Graphics::Mouse::Button(int button)
{
    return _buttons[button];
}
