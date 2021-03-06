#pragma once
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Defines.h"

using namespace std;

extern unsigned int times;

enum STAGE
{
    BUFF, AIR, ANTISUB, SHELL_1, SHELL_2, TORPEDO, NIGHT, END
};

enum COURSE
{
    TADV, INSAME, INREVERSE, TDISADV
};
double courseCoef(COURSE course);

enum FORMATION
{
    SINGLE, COMPLEX, WHEEL, TRAPEZOID, HORIZONTAL
};
double formationCoef(FORMATION formation, STAGE stage);
double formationCritMod(FORMATION formation);

enum AIRCONTROL
{
    ENSURE, ADV, DISADV
};

int foundRandOrder(int amount, int* ans, int repeat);
double randR(double _min = 0.0, double _max = 1.0);