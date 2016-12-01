#include "Fleet.h"
#include <iostream>
#include <fstream>

using namespace std;

Fleet::Fleet()
{
}

Fleet::Fleet(int _shipNo[6], int _shipAmount, Ship* shipList)
{
    memset(alive, 0, 6);
    memset(fireAble, 0, 6);
    shipAmount = _shipAmount;
    shipAmountOrg = _shipAmount;
    for (int i = 0; i < shipAmount; i++)
    {
        shipNo[i] = _shipNo[i];
        ship[i] = shipList[shipNo[i]];
        alive[i] = 1;
        fireAble[i] = 1;
    }
}

Fleet::~Fleet()
{
}

int Fleet::showFleet()
{
    for (int i = 0; i < shipAmountOrg; i++)
    {
        ship[i].showShip();
    }
    return 0;
}

int Fleet::showFleet(ofstream& outputFile)
{
    for (int i = 0; i < shipAmountOrg; i++)
    {
        ship[i].showShip(outputFile);
    }
    return 0;
}

int Fleet::checkAlive()
{
    for (int i = 0; i < shipAmountOrg; i++)
    {
        if (alive[i] == 1 && ship[i].currHP == 0)
        {
            alive[i] = 0;
            fireAble[i] = 0;
            shipAmount--;
        }
    }
    return 0;
}

int Fleet::checkFireAble(STAGE stage)
{
    for (int i = 0; i < shipAmountOrg; i++)
    {
        if (alive[i] == 0)
        {
            fireAble[i] = 0;
        }
        else if (stage == NIGHT && ship[i].currHP/(double)ship[i].maxHP < 0.25)// Ò¹Õ½£¬´óÆÆ
        {
            fireAble[i] = 0;
        }
    }

    return 0;
}