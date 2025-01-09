#include "stdafx.h"
#include "InputManager.h"

InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

bool InputManager::GetKeyDown(int key)
{
    bool isPressed = App::IsKeyPressed(key);
    bool wasPressed = m_keys[key];
    m_keys[key] = isPressed;

    return isPressed && !wasPressed;
}

bool InputManager::GetKeyUp(int key)
{
    bool isPressed = App::IsKeyPressed(key);
    bool wasPressed = m_keys[key];
    m_keys[key] = isPressed;

    return !isPressed && wasPressed;
}

bool InputManager::GetKey(int key)
{
    return App::IsKeyPressed(key);
}

Vector2 InputManager::GetMousePosition()
{
    App::GetMousePos(mouseX, mouseY);

    return Vector2(mouseX, mouseY);
}
