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

void Debug::DrawCircle(float cx, float cy, float radius, int segments, const Vector3& color)
{

    const float increment = 2.0f * PI / segments;
    float theta = 0.0f;

    for (int i = 0; i < segments; ++i)
    {
        // Calculate start and end points of the segment
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);

        theta += increment;

        float x2 = cx + radius * cosf(theta);
        float y2 = cy + radius * sinf(theta);

        // Draw the line segment
        App::DrawLine(x1, y1, x2, y2, color.x, color.y, color.z);
    }
}

void Debug::DrawBox(const Vector2& minimum, const Vector2& maximum, const Vector3& color)
{
    float topLeftX = minimum.x;
    float topLeftY = maximum.y;

    float topRightX = maximum.x;
    float topRightY = maximum.y;

    float bottomLeftX = minimum.x;
    float bottomLeftY = minimum.y;

    float bottomRightX = maximum.x;
    float bottomRightY = minimum.y;



    App::DrawLine(topLeftX, topLeftY, topRightX, topRightY, color.x, color.y, color.z);
    App::DrawLine(topRightX, topRightY, bottomRightX, bottomRightY, color.x, color.y, color.z);
    App::DrawLine(bottomRightX, bottomRightY, bottomLeftX, bottomLeftY, color.x, color.y, color.z);
    App::DrawLine(bottomLeftX, bottomLeftY, topLeftX, topLeftY, color.x, color.y, color.z);
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
