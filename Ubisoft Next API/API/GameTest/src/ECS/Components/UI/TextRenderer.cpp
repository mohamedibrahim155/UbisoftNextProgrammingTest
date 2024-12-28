#include "stdafx.h"
#include "TextRenderer.h"
#include "../src/ECS/Entity.h"
TextRenderer::TextRenderer(std::string message, const Vector2& offset)
    : RenderComponent(offset)
{
    this->message = message;
    SetFont(BITMAP_HELVETICA_18);
}

TextRenderer::TextRenderer(std::string message, const Vector2& offset, const Vector3& color)
    : RenderComponent(offset)
{
    this->message = message;
    this->color = color;
    SetFont(BITMAP_HELVETICA_18);
}

TextRenderer::TextRenderer(std::string message, const Vector2& offset, const Vector3& Color, eFontType fontType)
    : RenderComponent(offset)
{
    this->message = message;
    this->color = color;
    
    SetFont(fontType);
}



void TextRenderer::Start()
{
    Vector3 messagepos = Vector3(gameObject->transform.position + centerScreen + offset);
    messagePosition = Vector2(messagepos.x, messagepos.y);
}

void TextRenderer::UpdateComponent()
{
    if (!isComponentEnabled) return;

    Vector3 updatedPosition = Vector3(gameObject->transform.position + centerScreen + offset);
    messagePosition = Vector2(updatedPosition.x, updatedPosition.y);
}

void TextRenderer::Render()
{
    if (!isComponentEnabled) return;
    if (message.empty()) return;

    App::Print(messagePosition.x, messagePosition.y, message.c_str(), color.x, color.y, color.z,(void*)fontStyle);
}

TextRenderer* TextRenderer::Clone() const
{
    return new TextRenderer(message);
}

void TextRenderer::SetText(const std::string& message)
{
    this->message = message;
}



void TextRenderer::SetColor(float r, float g, float b)
{
    color = Vector3(r, g, b);
}

void TextRenderer::SetFont(eFontType type)
{

    switch (type)
    {
    case STROKE_ROMAN:
        fontStyle = GLUT_STROKE_ROMAN;
           break;

    case   STROKE_MONO_ROMAN:
        fontStyle = GLUT_STROKE_MONO_ROMAN;
           break;
    case   BITMAP_9_BY_15:
        fontStyle = GLUT_BITMAP_9_BY_15;
           break;
    case  BITMAP_8_BY_13:
        fontStyle = GLUT_BITMAP_8_BY_13;
           break;

    case  BITMAP_TIMES_ROMAN_10:
        fontStyle = GLUT_BITMAP_TIMES_ROMAN_10;
           break;

    case  BITMAP_TIMES_ROMAN_24:
        fontStyle = GLUT_BITMAP_TIMES_ROMAN_24;
           break;
    case   BITMAP_HELVETICA_10:
        fontStyle = GLUT_BITMAP_HELVETICA_10;
           break;
    case  BITMAP_HELVETICA_12:
        fontStyle = GLUT_BITMAP_HELVETICA_12;
           break;
    case  BITMAP_HELVETICA_18:
        fontStyle = GLUT_BITMAP_HELVETICA_18;
           break;

        default: fontStyle = GLUT_STROKE_ROMAN;
        break;
    }
}

int TextRenderer::RenderOrder()
{
    return 0;
}
