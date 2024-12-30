#pragma once
#include "SpriteRenderer.h"
class SpriteSheetRenderer : public  SpriteRenderer
{
public:
	SpriteSheetRenderer(std::string filename, int column, int row);
	SpriteSheetRenderer(std::string filename, int column, int row, int spriteOrder);
	virtual ~SpriteSheetRenderer() override;
	virtual void start() override;
	virtual void updateComponent() override;
	virtual void render() override;
	virtual SpriteSheetRenderer* clone() const override;
	void SetAnimation(int ID, bool playfromBegining = false);
	void CreateAnimation(unsigned int ID, float speed, const std::vector<int>& frames);

protected:

	int column;
	int row;

};

