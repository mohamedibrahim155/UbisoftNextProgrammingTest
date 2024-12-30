#include "stdafx.h"
#include "ButtonRenderer.h"
#include "../src/Timer/Timer.h"
#include "../src/Utils/PhysicsUtils.h"
ButtonRenderer::ButtonRenderer(std::string filename) : 
    SpriteRenderer(filename,true)
{
    SetUI(true);

    boxCollider = new BoxCollider(this);
    boxCollider->SetUI(true);

    mousCircle = { GetMousePosition(), 5.0f };

}



void ButtonRenderer::Start()
{
    gameObject->AddComponent(boxCollider);
}

void ButtonRenderer::UpdateComponent()
{
    if (!isComponentEnabled) return;

#pragma region ButtonValidate

    // Update mouse position circle
    mousCircle.centre = GetMousePosition();





    //Checks Button Collision for ButtonPress
    std::vector<Vector2> collisionPnt, collisionNormal;
    if (Physics::CircleVsBox(&mousCircle, &boxCollider->GetBox(), true, collisionPnt, collisionNormal))
    {

        if (!isOnHover)
        {
            OnButtonHover.Invoke();
        }

        if (App::IsKeyPressed(MOUSEEVENTF_LEFTDOWN) ||  (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, true)))
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
    SpriteRenderer::UpdateComponent();

}

void ButtonRenderer::Render()
{
    if (!isComponentEnabled) return;

    // Render Sprite
    SpriteRenderer::Render();



    // Draw Mouse Circle
    DrawCircle(mousCircle.centre.x, mousCircle.centre.y, mousCircle.radius, 36, debugColor);
    
    // Render BoxCollider if enabled

    if (boxCollider && boxCollider->isComponentEnabled)
    {
        boxCollider->Render();
    }


  

}

ButtonRenderer* ButtonRenderer::Clone() const
{
    return new ButtonRenderer(this->fileName);
}


void ButtonRenderer::AddListenersOnButtonPress(const std::function<void()>& callback)
{
    OnButtonClick.Subscribe(callback);
}

void ButtonRenderer::AddListenersOnButtonHover(const std::function<void()>& callback)
{
    OnButtonHover.Subscribe(callback);
}

void ButtonRenderer::AddListenersOnButtonHoverExit(const std::function<void()>& callback)
{
    OnButtonHoverExit.Subscribe(callback);
}

Vector2 ButtonRenderer::GetMousePosition()
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

int ButtonRenderer::RenderOrder()
{
    return 0;
}




