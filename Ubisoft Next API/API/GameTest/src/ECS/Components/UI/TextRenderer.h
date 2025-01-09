#pragma once
#include "../Renders/RenderComponent.h"

enum eFontType
{
	STROKE_ROMAN,
	STROKE_MONO_ROMAN,
	BITMAP_9_BY_15,
	BITMAP_8_BY_13,
	BITMAP_TIMES_ROMAN_10,
	BITMAP_TIMES_ROMAN_24,
	BITMAP_HELVETICA_10,
	BITMAP_HELVETICA_12,
	BITMAP_HELVETICA_18,
};
class TextRenderer : public RenderComponent
{
public:

	TextRenderer(const std::string& message, const Vector2& offset = Vector2::Zero());
	TextRenderer(const std::string& message, const Vector2& offset, const Vector3& Color = Vector2::One());
	TextRenderer(const std::string& messagee, const Vector2& offset, const Vector3& Color, eFontType fontType = BITMAP_TIMES_ROMAN_10);
	~TextRenderer() override = default;

	// Inherited via RenderComponent
	void start() override;
	void updateComponent() override;
	void render(bool isDebugVisible) override;
    void cleanUp() override {};
	TextRenderer* clone() const override;
	int renderOrder() override;

	//Sets text components data
	void setText(const std::string& message);
	void setColor(float r, float g, float b);
	void setFont(eFontType type);
	void setTextRenderOrder(int order);
	void setOffset(const Vector2& offset);

	// Getters for text Component
	inline  std::string getText()    const { return message; };
	inline  Vector3     getColor()   const { return m_fontColor; };
private:

	int m_renderOrder = 10;
	std::string message;

	Vector2 messagePosition;
	Vector3 m_fontColor =Vector3::One();

	void* fontStyle = nullptr;


};

