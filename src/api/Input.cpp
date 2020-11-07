#include "Input.hpp"
#include "Engine.hpp"

bool Input::cursorHidden = false;
glm::vec2 Input::currentCursorPos = glm::vec2(0);
glm::vec2 Input::lastCursorPos = glm::vec2(0);

void Input::init() {
    double x, y;
    glfwGetCursorPos(Engine::getWindow(), &x, &y);
    Input::lastCursorPos = glm::vec2(x, y);
    Input::currentCursorPos = glm::vec2(x, y);
}

void Input::update() {
    double x, y;
    glfwGetCursorPos(Engine::getWindow(), &x, &y);
    Input::lastCursorPos = Input::currentCursorPos;
    Input::currentCursorPos = glm::vec2(x, y);
}

bool Input::keyPressed(int key) {
    return glfwGetKey(Engine::getWindow(), key) == GLFW_PRESS;
}

glm::vec2 Input::cursorPos() {
    return Input::currentCursorPos;
}

glm::vec2 Input::cursorPosOffset() {
    return Input::currentCursorPos - Input::lastCursorPos;
}

bool Input::buttonPressed(int button) {
    glfwGetMouseButton(Engine::getWindow(), button) == GLFW_PRESS;
}

void Input::setCursorHidden(bool hidden) {
    int mode;
    if (hidden)
        mode = GLFW_CURSOR_DISABLED;
    else
        mode = GLFW_CURSOR_NORMAL;
    
    glfwSetInputMode(Engine::getWindow(), GLFW_CURSOR, mode);
    Input::cursorHidden = hidden;
}

void Input::toggleCursorHidden() {
    setCursorHidden(!Input::cursorHidden);
}

bool Input::isCursorHidden() {
    return Input::cursorHidden;
}
