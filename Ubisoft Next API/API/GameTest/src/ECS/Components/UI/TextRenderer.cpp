#include "stdafx.h"
#include "TextRenderer.h"
#include "../src/ECS/Entity.h"
TextRenderer::TextRenderer(const std::string& message, const Vector2& offset)
    : RenderComponent(offset)
{
    this->message = message;

    setUI(true);

    setFont(BITMAP_HELVETICA_18);
}

TextRenderer::TextRenderer(const std::string& message, const Vector2& offset, const Vector3& color)
    : RenderComponent(offset)
{
    this->message = message;
    this->m_fontColor = color;

    setUI(true);

    setFont(BITMAP_HELVETICA_18);
}

TextRenderer::TextRenderer(const std::string& message, const Vector2& offset, const Vector3& Color, eFontType fontType)
    : RenderComponent(offset)
{
    this->message = message;
    this->m_fontColor = m_fontColor;

    setUI(true);
    setFont(fontType);
}





void TextRenderer::start()
{
    Vector3 messagepos = Vector3(gameObject->transform.position + m_centerScreen + m_offset);
    messagePosition = Vector2(messagepos.x, messagepos.y);
}

void TextRenderer::updateComponent()
{
    if (!m_isEnabled) return;

    Vector3 updatedPosition = Vector3(gameObject->transform.position + m_centerScreen + m_offset);
    messagePosition = Vector2(updatedPosition.x, updatedPosition.y);
}

void TextRenderer::render()
{
    if (!m_isEnabled) return;
    if (message.empty()) return;

    App::Print(messagePosition.x, messagePosition.y, message.c_str(), m_fontColor.x, m_fontColor.y, m_fontColor.z,(void*)fontStyle);
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
    m_fontColor = Vector3(r, g, b);
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

void TextRenderer::setTextRenderOrder(int order)
{
    m_renderOrder = order;
}

void TextRenderer::setOffset(const Vector2& offset)
{
    m_offset = offset;
}

int TextRenderer::renderOrder()
{
    return m_renderOrder;
}
