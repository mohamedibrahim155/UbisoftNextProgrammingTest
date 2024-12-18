#pragma once

#include <random>
#include "../Vector.h"
#include "App/app.h"


class Random
{
public:
	static int RandomNumber();
	static float RandomValue();
	static int RandomRange(int min, int max);
	static float RandomRange(float min, float max);
	static Vector2 RandomUnitCircle();
};

class Debug
{
public:
	static void Log(std::string message, Vector3 color = Vector3::One());
	static void Log(int value);
	static void Log(float value);
};



class MathF
{
public:
	static float Clamp(float value, float min, float max);
	static float  Lerp(float a, float b, float t);
	static float Max(float a, float b);
	static float Min(float a, float b);
};
