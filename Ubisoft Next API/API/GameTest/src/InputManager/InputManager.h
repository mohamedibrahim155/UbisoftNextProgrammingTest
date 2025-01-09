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

	Vector2 GetMousePosition();

private:



	float mouseX, mouseY;

	std::unordered_map<int, bool> m_keys;
};

