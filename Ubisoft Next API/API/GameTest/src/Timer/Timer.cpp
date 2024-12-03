#include "Timer.h"
#include "stdafx.h"
Timer& Timer::GetInstance()
{
    static Timer instance;
    return instance;
}
