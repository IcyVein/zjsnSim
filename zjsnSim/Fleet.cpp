#pragma once
#include "Fleet.h"
#include <iostream>
#include <fstream>
#include <cmath>

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

    outputFile << endl;
    return 0;
}

int Fleet::loadEquip(int fleetEquip[][4], Equip* equipList)
{
    for (int i = 0; i < shipAmountOrg; i++)
    {
        for (int j = 0; j < ship[i].equipSlot; j++)
        {
            ship[i].loadEquip(equipList[fleetEquip[i][j]]);
        }
    }

    return 0;
}

int Fleet::loadShipLv(int shipLv[])
{
    for (int i = 0; i < shipAmountOrg; i++)
    {
        ship[i].lv = shipLv[i];

        ship[i].accurate = (int)round(ship[i].accurate*ship[i].lv / 100.0);
        ship[i].dodge = (int)round(ship[i].dodge*ship[i].lv / 100.0);
        ship[i].toss = (int)round(ship[i].toss*ship[i].lv / 100.0);
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
        else if (stage == NIGHT && ship[i].currHP/(double)ship[i].maxHP < 0.25)// ҹս������
        {
            fireAble[i] = 0;
        }
    }

    return 0;
}

int Fleet::repair(int* repairConsumption)
{
    int lossHP = 0;
    int repairShipConsumption[2] = { 0 };

    for (int i = 0; i < shipAmountOrg; i++)
    {
        lossHP += ship[i].repair(repairShipConsumption);
        repairConsumption[0] += repairShipConsumption[0];
        repairConsumption[1] += repairShipConsumption[1];
    }

    return lossHP;
}