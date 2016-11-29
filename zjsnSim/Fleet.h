#pragma once
#include "Ship.h"
class Fleet
{
public:
    Fleet();
    Fleet(int _shipNo[6], int _shipAmount, Ship* shipList);
    ~Fleet();

    int showFleet();
public:
    int shipAmount;
    int shipNo[6];
    Ship ship[6];
};

