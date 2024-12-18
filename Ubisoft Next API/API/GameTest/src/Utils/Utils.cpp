#include "stdafx.h"
#include "Utils.h"

int Random::RandomRange(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(min, max - 1);

    int random_number = dist(gen);

    return random_number;
}

float Random::RandomRange(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(min, max - 1);

    float random_number = dist(gen);
    return random_number;
}
Vector2 Random::RandomUnitCircle()
{
    float x, y;
    do {
        x = RandomRange(-1.0f,1.0f);
        y = RandomRange(-1.0f, 1.0f);
    } while (x * x + y * y > 1.0f);

        return { x, y };
}
int Random::RandomNumber()
{
    int random_Number = RandomRange(INT32_MIN, INT32_MAX);
   
    return random_Number;
}

float Random::RandomValue()
{
    return RandomRange(0.0f, 1.0f);
}

void Debug::Log(std::string message, Vector3 color)
{
    Vector3 nomralizedColor = color.Normalize();
    App::Print((APP_VIRTUAL_WIDTH / 2) + (APP_VIRTUAL_WIDTH / 4), 0, message.c_str(), nomralizedColor.x, nomralizedColor.y, nomralizedColor.z);
}

void Debug::Log(int value)
{
}

void Debug::Log(float value)
{
}



float MathF::Clamp(float value, float min, float max)
{
    return (value < min ? min : (value > max) ? max : value);
}

float  MathF::Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

float MathF::Max(float a, float b)
{
    return (a > b) ? a : b;
}

float MathF::Min(float a, float b)
{
    return (a < b) ? a : b;
}
