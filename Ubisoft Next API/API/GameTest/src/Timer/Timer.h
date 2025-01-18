#pragma once

class Timer
{
public:

	// Global Timer
	static Timer& GetInstance();
    float deltaTime = 0;
	float unscaledTime = 1;
};

