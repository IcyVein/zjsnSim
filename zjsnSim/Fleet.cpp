#include "Fleet.h"
#include <iostream>

using namespace std;

Fleet::Fleet()
{
}

Fleet::Fleet(int _shipNo[6], int _shipAmount, Ship* shipList)
{
    shipAmount = _shipAmount;
    for (int i = 0; i < shipAmount; i++)
    {
        shipNo[i] = _shipNo[i];
        ship[i] = shipList[shipNo[i]];
    }
}

Fleet::~Fleet()
{
}

int Fleet::showFleet()
{
    for (int i = 0; i < shipAmount; i++)
    {
        ship[i].showShip();
    }
    return 0;
}
