#include "stdafx.h"
#include "BlockHolder.h"

BlockHolder::BlockHolder(Ball* ball)
{
	this->m_ball = ball;
}

BlockHolder::~BlockHolder()
{
}

void BlockHolder::start()
{
	gameObject->setTag("Block Holder");

	setController(m_ball->getController());
}

void BlockHolder::updateComponent()
{
	if (!m_ballController) return;

	updateColliders(m_ballController->getColorState());
}

void BlockHolder::cleanUp()
{
	m_listOfBlocks.clear();
}

void BlockHolder::setController(BallController* contoller)
{
	m_ballController = contoller;
}

void BlockHolder::addBlock(Block* newBlock)
{
	m_listOfBlocks.push_back(newBlock);
}

void BlockHolder::removeBlock(Block* removeBlock)
{
}

void BlockHolder::updateColliders(eColorType ballType)
{
	for (Block* block :  m_listOfBlocks)
	{
		if (checkState(ballType, block->getType()))
		{
			block->setTriggerState(true);
		}
		else
		{
			block->setTriggerState(false);

		}
	}

	
}

bool BlockHolder::checkState(eColorType balltype, eColorType blockType)
{
	return balltype == blockType;
}


