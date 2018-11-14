#include "Engine.h"
#include "Mouse.h"
#include "Keyboard.h"

#include <iostream>

using namespace std;
using namespace TFC::Graphics;

int Engine::SCREEN_WIDTH = 1024;
int Engine::SCREEN_HEIGHT = 768;
GLFWwindow * Engine::_window = nullptr;
float Engine::_deltaTime = 0.0;

Engine::Engine()
{
}


Engine::~Engine()
{
}

bool TFC::Graphics::Engine::Initialize(const char * title)
{
    if (!glfwInit())
    {
        cout << "Error initializing GLFW" << endl;
        return false;
    }

    _window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, nullptr, nullptr);
    if (_window == nullptr)
    {
        cout << "Error creating window" << endl;
        return false;
    }

    // OpenGL setup
    //
    glfwMakeContextCurrent(_window);
    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);
    glfwSwapInterval(1);

    glfwSetCursorPosCallback(_window, Mouse::MousePosCallback);
    glfwSetMouseButtonCallback(_window, Mouse::MouseButtonCallback);

    glfwSetKeyCallback(_window, Keyboard::KeyCallback);

    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int xPos = (mode->width - SCREEN_WIDTH) / 2;
    int yPos = (mode->height - SCREEN_HEIGHT) / 2;
    glfwSetWindowPos(_window, xPos, yPos);

    // GL setup
    //
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -10.0, 10.0);
    glDepthRange(-10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);

    // Alpha blending
    //
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _lastTime = (float)glfwGetTime();

    return true;
}

void Engine::Update()
{
    float now = (float)glfwGetTime();
    _deltaTime = now - _lastTime;
    _lastTime = now;

    glfwPollEvents();
}

void Engine::BeginRender()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::EndRender()
{
    glfwSwapBuffers(_window);
}
