#pragma once
#include "../BaseLevel.h"
class MainMenu  : public BaseLevel
{
public:
	MainMenu() : BaseLevel(MAINMENU) {};
	// Inherited via BaseLevel
	void Initialize() override;
	void CleanScene() override;


};

