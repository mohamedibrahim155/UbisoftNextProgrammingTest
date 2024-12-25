#pragma once
#include "SpriteRenderer.h"
class SpriteSheetRenderer : public  SpriteRenderer
{
public:
	SpriteSheetRenderer(std::string filename, int column, int row);
	SpriteSheetRenderer(std::string filename, int column, int row, int spriteOrder);
	virtual ~SpriteSheetRenderer() override;
	virtual void Start() override;
	virtual void UpdateComponent() override;
	virtual void Render() override;
	virtual SpriteSheetRenderer* Clone() const override;
	void SetAnimation(int ID, bool playfromBegining = false);
	void CreateAnimation(unsigned int ID, float speed, const std::vector<int>& frames);

protected:

	int column;
	int row;

};

