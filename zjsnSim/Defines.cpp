#pragma once
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "Defines.h"

using namespace std;

unsigned int times = 0;

double courseCoef(COURSE course)
{
    switch (course)
    {
    case TADV:
        return 1.15;
        break;
    case INSAME:
        return 1.00;
        break;
    case INREVERSE:
        return 0.80;
        break;
    case TDISADV:
        return 0.65;
        break;
    default:
        return 0.0;
        break;
    }
}

double formationCoef(FORMATION formation, STAGE stage)
{
    if (stage != NIGHT)
    {
        switch (formation)
        {
        case SINGLE:
            return 1.0;
            break;
        case COMPLEX:
            return 0.8;
            break;
        case WHEEL:
            return 0.75;
            break;
        case TRAPEZOID:
            return 1.0;
            break;
        case HORIZONTAL:
            return 0.8;
            break;
        default:
            return 0;
            break;
        }
    }
    else
    {
        switch (formation)
        {
        case SINGLE:
            return 1.1;
            break;
        case COMPLEX:
            return 0.9;
            break;
        case WHEEL:
            return 1.0;
            break;
        case TRAPEZOID:
            return 1.0;
            break;
        case HORIZONTAL:
            return 1.0;
            break;
        default:
            return 0;
            break;
        }
    }
}

double formationCritMod(FORMATION formation)
{
    switch (formation)
    {
    case SINGLE:
        return 0.0;
        break;
    case COMPLEX:
        return 0.0;
        break;
    case WHEEL:
        return 0.0;
        break;
    case TRAPEZOID:
        return 0.20;
        break;
    case HORIZONTAL:
        return 0.0;
        break;
    default:
        return 0;
        break;
    }
}

int foundRandOrder(int amount, int* ans, int repeat)
{
    int temp, randNum;
    times++;
    srand(time(NULL) + times);
    for (int i = 0; i < amount*repeat; i++)
    {
        randNum = rand() % amount;
        temp = ans[i / repeat];
        ans[i / repeat] = ans[randNum];
        ans[randNum] = temp;
    }

    return 0;
}

double randR(double _min, double _max)
// 生成[_min, _max]的均匀分布，已验证其随机性
{
    times++;
    int luckNum = 100;
    srand(time(NULL) % luckNum + times);
    return (rand() % luckNum) / (double)luckNum * (_max - _min) + _min;
}
