#pragma once
#include "../App/app.h"
#include <unordered_map>
class InputManager
{
public:
	static InputManager& GetInstance();


	bool GetKeyDown(int key);
	bool GetKeyUp(int key);
	bool GetKey(int key);

private:




	std::unordered_map<int, bool> m_keys;
};

