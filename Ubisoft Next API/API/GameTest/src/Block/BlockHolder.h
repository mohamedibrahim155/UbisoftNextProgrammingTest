#pragma once
#include "../src/Block/Blocks.h"
#include "../src/Ball/BallController.h"
class BlockHolder :  public BaseScriptComponent
{
public:
	BlockHolder(BallComponent* ball);
	~BlockHolder();

	 void start()   override;
	 void updateComponent() override;
	 void render(bool isDebugVisible) override {};
	 void cleanUp() override;

	 void setController(BallController* m_ballController);

	void addBlock(Block* newBlock);

	void updateColliders(eColorType ballType);

	bool checkState(eColorType balltype, eColorType blockType);
private:

	int skipFrame = 1;
	BallController* m_ballController;
	BallComponent* m_ball;
	std::vector<Block*> m_listOfBlocks;

	
};

