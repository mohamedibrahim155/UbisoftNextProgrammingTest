#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager()
{
    m_mouseX = 0;
    m_mouseY = 0;
    for (size_t i = 0; i < 256; ++i)
    {
        m_keysStates[i] = false;
    }
}

InputManager::~InputManager()
{
    m_keysStates.clear();
}

InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}
// Returns if the key is pressed Once
bool InputManager::getKeyDown(int key)
{
    bool isPressed = getKey(key);

    if (!m_keysStates[key] && isPressed)
    {
        m_keysStates[key] = true;
        return true;
    }
   
    return false;

  
}
// Returns if the key is released
bool InputManager::getKeyUp(int key)
{
    bool isPressed = getKey(key);

    if (m_keysStates[key] && !isPressed)
    {
        m_keysStates[key] = false;

        return true;
    }

    return false;
}
// Returns the currently pressed state of key
bool InputManager::getKey(int key)
{
    return App::IsKeyPressed(key);
}

//Gets the mouseposition from the screen
Vector2 InputManager::getMousePosition()
{
    App::GetMousePos(m_mouseX, m_mouseY);
    return Vector2(m_mouseX, m_mouseY);
}


