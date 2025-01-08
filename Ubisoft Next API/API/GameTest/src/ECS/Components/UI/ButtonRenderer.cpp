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

ButtonRenderer::ButtonRenderer(std::string filename, TextRenderer* textComponent) : SpriteRenderer(filename, true)
{
    setUI(true);

    boxCollider = new BoxCollider(this);
    boxCollider->setUI(true);

    mousCircle = { getMousePosition(), 5.0f };

    if (textComponent)
    {
        this->textComponent = textComponent;
    }
}









void ButtonRenderer::start()
{
    gameObject->addComponent(boxCollider);

    if (textComponent)
    {
        textComponent->setEntity(gameObject);
        textComponent->start();
    }
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

    if (textComponent)
    {
        textComponent->updateComponent();
    }
}

void ButtonRenderer::render()
{
    if (!m_isEnabled) return;

    //Renders Text
 

    // Render Sprite
    SpriteRenderer::render();

    if (textComponent)
    {
        textComponent->render();
    }

    // Draw Mouse Circle
    Debug::DrawCircle(mousCircle.centre.x, mousCircle.centre.y, mousCircle.radius, 36, m_debugColor);
   

    if (boxCollider && boxCollider->m_isEnabled)
    {
        boxCollider->render();
    }


  

}

void ButtonRenderer::cleanUp()
{
    cleanEvents();

    if (textComponent)
    {
        delete textComponent;
    }
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

void ButtonRenderer::setTextColor(float r, float g, float b)
{
    if (!textComponent) return;
  
    textComponent->setColor(r, g, b);
    
}

void ButtonRenderer::setText(const std::string& message)
{
    if (!textComponent) return;

    textComponent->setText(message);
}

Vector2 ButtonRenderer::getMousePosition()
{
    float x, y;

    App::GetMousePos(x, y);

    return Vector2(x, y);

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




