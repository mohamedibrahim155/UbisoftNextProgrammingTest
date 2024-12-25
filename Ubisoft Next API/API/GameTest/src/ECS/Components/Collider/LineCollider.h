#pragma once
#include "Collider.h"
class LineCollider : public Collider
{
public:

	LineCollider(const Vector2& startpoint, const Vector2& endpoint);
	~LineCollider() override = default;

	// Inherited via Collider
	void Start() override {};
	void UpdateComponent() override {};
	void Render() override;
	void CalculateShape() override;
	LineCollider* Clone() const override;

	SLine GetLine();
	void SetLine(const Vector2& startpoint, const Vector2& endpoint);
private:

	SLine m_line;
	

	// Inherited via Collider
	SBox GetBounds() override;





};

