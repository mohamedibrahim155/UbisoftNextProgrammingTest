#include "stdafx.h"
#include "ButtonRenderer.h"
#include "../src/Timer/Timer.h"
#include "../src/Utils/PhysicsUtils.h"
ButtonRenderer::ButtonRenderer(std::string filename) : 
    SpriteRenderer(filename,true)
{
    setUI(true);

    boxCollider = new BoxCollider(this);
    boxCollider->setUI(true);

    mousCircle = { getMousePosition(), 5.0f };

}







void ButtonRenderer::start()
{
    gameObject->addComponent(boxCollider);
}

void ButtonRenderer::updateComponent()
{
    if (!m_isEnabled) return;

#pragma region ButtonValidate

    // Update mouse position circle
    mousCircle.centre = getMousePosition();





    //Checks Button Collision for ButtonPress
    std::vector<Vector2> collisionPnt, collisionNormal;
    if (Physics::CircleVsBox(&mousCircle, &boxCollider->getBox(), true, collisionPnt, collisionNormal))
    {

        if (!isOnHover)
        {
            OnButtonHover.Invoke();
        }

        if (IsMousePressed(VK_LBUTTON) || (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, true)))
        {
            OnButtonClick.Invoke();
        }

        isOnHover = true;
    }
    else
    {
        if (isOnHover)
        {
            OnButtonHoverExit.Invoke();
        }
        isOnHover = false;
    }
    

#pragma endregion

    // Update Sprite
    SpriteRenderer::updateComponent();

}

void ButtonRenderer::render()
{
    if (!m_isEnabled) return;

    // Render Sprite
    SpriteRenderer::render();



    // Draw Mouse Circle
    DrawCircle(mousCircle.centre.x, mousCircle.centre.y, mousCircle.radius, 36, m_debugColor);
    
    // Render BoxCollider if enabled

    if (boxCollider && boxCollider->m_isEnabled)
    {
        boxCollider->render();
    }


  

}

void ButtonRenderer::cleanUp()
{
    cleanEvents();
}

ButtonRenderer* ButtonRenderer::clone() const
{
    return new ButtonRenderer(this->m_fileName);
}


void ButtonRenderer::addListenersOnButtonPress(const std::function<void()>& callback)
{
    OnButtonClick.Subscribe(callback);
}

void ButtonRenderer::addListenersOnButtonHover(const std::function<void()>& callback)
{
    OnButtonHover.Subscribe(callback);
}

void ButtonRenderer::addListenersOnButtonHoverExit(const std::function<void()>& callback)
{
    OnButtonHoverExit.Subscribe(callback);
}

void ButtonRenderer::cleanEvents()
{
    OnButtonClick.clear();
    OnButtonHover.clear();
    OnButtonHoverExit.clear();
}

Vector2 ButtonRenderer::getMousePosition()
{
    float x, y;

    App::GetMousePos(x, y);

    return Vector2(x, y);

}


void ButtonRenderer::DrawCircle(float cx, float cy, float radius, int segments, const Vector3& color)
{

    const float increment = 2.0f * PI / segments;
    float theta = 0.0f;

    for (int i = 0; i < segments; ++i)
    {
        // Calculate start and end points of the segment
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);

        theta += increment;

        float x2 = cx + radius * cosf(theta);
        float y2 = cy + radius * sinf(theta);

        // Draw the line segment
        App::DrawLine(x1, y1, x2, y2, color.x, color.y, color.z);
    }

}

bool ButtonRenderer::IsMousePressed(const int mouseKey)
{
    bool isPressed = App::IsKeyPressed(mouseKey);

    bool wasPressed = previousMouseKeyStates[mouseKey];
    previousMouseKeyStates[mouseKey] = isPressed;

    return isPressed && !wasPressed;
}

int ButtonRenderer::renderOrder()
{
    return 0;
}




