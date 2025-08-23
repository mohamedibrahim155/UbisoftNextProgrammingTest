///-------------------------
/// Input Manager manages the Windows Keyinput
/// ------------------------
#pragma once
#include "../App/app.h"
#include <unordered_map>


class InputManager
{
public:
	InputManager();
	~InputManager();
	static InputManager& GetInstance();

	bool getKeyDown(int key);
	bool getKeyUp(int key);
	bool getKey(int key);

	void refreshInputs();

	Vector2 getMousePosition();

private:
	float m_mouseX;
	float m_mouseY;
	std::unordered_map<int, bool> m_keysStates;
};

