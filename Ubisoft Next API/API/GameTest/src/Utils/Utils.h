#pragma once

#include <random>
#include "../Vector.h"
#include "App/app.h"
namespace Random
{
	extern int RandomNumber();
	extern float RandomValue();
	extern int RandomRange(int min, int max);
	extern float RandomRange(float min, float max);
	extern Vector2 RandomUnitCircle();
}

namespace Debug
{
	extern void Log( std::string message, Vector3 color = Vector3::One() );
	extern void Log(int value);
	extern void Log(float value);
}
