#include "stdafx.h"
#include "TextRenderer.h"
#include "../src/ECS/Entity.h"
TextRenderer::TextRenderer(std::string message, const Vector2& offset)
    : RenderComponent(offset)
{
    this->message = message;

    setUI(true);

    setFont(BITMAP_HELVETICA_18);
}

TextRenderer::TextRenderer(std::string message, const Vector2& offset, const Vector3& color)
    : RenderComponent(offset)
{
    this->message = message;
    this->color = color;

    setUI(true);

    setFont(BITMAP_HELVETICA_18);
}

TextRenderer::TextRenderer(std::string message, const Vector2& offset, const Vector3& Color, eFontType fontType)
    : RenderComponent(offset)
{
    this->message = message;
    this->color = color;

    setUI(true);
    setFont(fontType);
}



void TextRenderer::start()
{
    Vector3 messagepos = Vector3(gameObject->transform.position + centerScreen + offset);
    messagePosition = Vector2(messagepos.x, messagepos.y);
}

void TextRenderer::updateComponent()
{
    if (!isComponentEnabled) return;

    Vector3 updatedPosition = Vector3(gameObject->transform.position + centerScreen + offset);
    messagePosition = Vector2(updatedPosition.x, updatedPosition.y);
}

void TextRenderer::render()
{
    if (!isComponentEnabled) return;
    if (message.empty()) return;

    App::Print(messagePosition.x, messagePosition.y, message.c_str(), color.x, color.y, color.z,(void*)fontStyle);
}

TextRenderer* TextRenderer::clone() const
{
    return new TextRenderer(message);
}

void TextRenderer::setText(const std::string& message)
{
    this->message = message;
}



void TextRenderer::setColor(float r, float g, float b)
{
    color = Vector3(r, g, b);
}

void TextRenderer::setFont(eFontType type)
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

int TextRenderer::renderOrder()
{
    return 0;
}
