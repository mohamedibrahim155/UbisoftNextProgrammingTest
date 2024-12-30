#pragma once
#include "Collider.h"
class LineCollider : public Collider
{
public:

	LineCollider(const Vector2& startpoint, const Vector2& endpoint);
	~LineCollider() override = default;

	// Inherited via Collider
	void start() override {};
	void updateComponent() override {};
	void render() override;
	void calculateShape() override;
	LineCollider* clone() const override;

	SLine getLine();
	void setLine(const Vector2& startpoint, const Vector2& endpoint);
private:

	SLine m_line;
	

	// Inherited via Collider
	SBox getBounds() override;





};

