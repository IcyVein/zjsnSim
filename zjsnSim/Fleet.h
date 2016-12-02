#pragma once
#include <fstream>
#include "Defines.h"
#include "Ship.h"

using namespace std;

class Fleet
{
public:
    Fleet();
    Fleet(int _shipNo[6], int _shipAmount, Ship* shipList);
    ~Fleet();

    int showFleet();
    int showFleet(ofstream& outputFile);

    int loadEquip(int fleetEquip[][4], Equip* equipList);
    int loadShipLv(int shipLv[]);

    int checkAlive();
    int checkFireAble(STAGE stage);
public:
    int shipAmount;
    int shipAmountOrg;
    int shipNo[6];
    Ship ship[6];

    int alive[6];
    int fireAble[6];
};

