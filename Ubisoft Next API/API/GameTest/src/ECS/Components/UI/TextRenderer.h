#pragma once
#include "../RenderComponent.h"

enum eFontType
{
	/*GLUT_STROKE_ROMAN
	GLUT_STROKE_MONO_ROMAN
	GLUT_BITMAP_9_BY_15
	GLUT_BITMAP_8_BY_13
	GLUT_BITMAP_TIMES_ROMAN_10
	GLUT_BITMAP_TIMES_ROMAN_24
	GLUT_BITMAP_HELVETICA_10
	GLUT_BITMAP_HELVETICA_12
	GLUT_BITMAP_HELVETICA_18*/

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

	TextRenderer(std::string message, const Vector2& offset = Vector2::Zero());
	TextRenderer(std::string message, const Vector2& offset, const Vector3& Color = Vector2::One());
	TextRenderer(std::string message, const Vector2& offset, const Vector3& Color, eFontType fontType = BITMAP_TIMES_ROMAN_10);
	~TextRenderer() override = default;

	// Inherited via RenderComponent
	void Start() override;
	void UpdateComponent() override;
	void Render() override;
	TextRenderer* Clone() const override;
	int RenderOrder() override;

	void SetText(const std::string& message);
	void SetColor(float r, float g, float b);
	void SetFont(eFontType type);


	inline  std::string GetText()    const { return message; };
	inline  Vector3     GetColor()   const { return color; };
private:

	std::string message;
	Vector2 messagePosition;
	Vector3 color =Vector3::One();
	void* fontStyle;


};

