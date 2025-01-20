#include "stdafx.h"
#include "BlockHolder.h"
#include"../src/InputManager/InputManager.h"
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

	updateInputs();
}

void BlockHolder::render(bool isDebugVisible)
{
	if (!debugEnity) return;

	Vector3 pos = debugEnity->transform.position;

	std::string value = std::to_string(pos.x) + " " + std::to_string(pos.y);

	App::Print(300, 300, value.c_str(), 1, 1, 0);
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

void BlockHolder::updateInputs()
{
	if (!debugEnity) return;
	if (InputManager::GetInstance().getKey(VK_UP))
	{
		debugEnity->transform.position.y += 2;
	}

	if (InputManager::GetInstance().getKey(VK_DOWN))
	{
		debugEnity->transform.position.y -= 2;
	}

	if (InputManager::GetInstance().getKey(VK_LEFT))
	{
		debugEnity->transform.position.x -= 2;
	}

	if (InputManager::GetInstance().getKey(VK_RIGHT))
	{
		debugEnity->transform.position.x += 2;
	}
}


