#include "stdafx.h"
#include "ButtonRenderer.h"
#include "../src/Timer/Timer.h"
#include "../src/Utils/PhysicsUtils.h"
#include "../src/InputManager/InputManager.h"
ButtonRenderer::ButtonRenderer(std::string filename) : 
    SpriteRenderer(filename,true)
{
    setUI(true);

    boxCollider = new BoxCollider(this);
    boxCollider->setUI(true);

    mousCircle = { InputManager::GetInstance().GetMousePosition(), 5.0f };

}

ButtonRenderer::ButtonRenderer(std::string filename, TextRenderer* textComponent) : SpriteRenderer(filename, true)
{
    setUI(true);

    boxCollider = new BoxCollider(this);
    boxCollider->setUI(true);

    mousCircle = { InputManager::GetInstance().GetMousePosition(), 5.0f};

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
    mousCircle.centre = InputManager::GetInstance().GetMousePosition();





    //Checks Button Collision for ButtonPress
    std::vector<Vector2> collisionPnt, collisionNormal;
    if (Physics::CircleVsBox(&mousCircle, &boxCollider->getBox(), true, collisionPnt, collisionNormal))
    {

        if (!isOnHover)
        {
            OnButtonHover.Invoke();
        }

        if (InputManager::GetInstance().GetKeyDown(VK_LBUTTON) || (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, true)))
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

void ButtonRenderer::render(bool isDebugRender)
{
    if (!m_isEnabled) return;

    //Renders Text
 

    // Render Sprite
    SpriteRenderer::render(isDebugRender);

    if (textComponent)
    {
        textComponent->render(isDebugRender);
    }

    if (!isDebugRender) return;
    // Draw Mouse Circle
    Debug::DrawCircle(mousCircle.centre.x, mousCircle.centre.y, mousCircle.radius, 36, m_debugColor);
   

    if (boxCollider && boxCollider->m_isEnabled)
    {
        boxCollider->render(isDebugRender);
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








int ButtonRenderer::renderOrder()
{
    return 0;
}




