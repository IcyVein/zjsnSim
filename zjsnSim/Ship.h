#pragma once
#include <string>
#include <fstream>
#include "Defines.h"
#include "Equip.h"

using namespace std;

class Ship
{
public:
    Ship();
    Ship(int no, string name, int _type, int _lv, int _maxHP, double _speed, int _range, int _equipSlot,
        int _firePower, int _torpedo, int _armor, int _antiAircraft, int _accurate, int _dodge, int _antiSubmarine, int _toss, int _lucky,
        int _ammunition, int _oil, int _capacity[4], int _skill, double _repairConsumptionOil, double _repairConsumptionSteel);
    ~Ship();
    Ship operator=(Ship currShip);
    int showShip();
    int showShip(ofstream& outputFile);

    int loadEquip(Equip equip);

    int getAttackAmount(STAGE stage);
    double getAttackPower(STAGE stage);

    int repair(int* repairConsumption);

    friend int loadShipList(string shipListPath, Ship* ship);
public:
    int no;
    string name;
    int type;
    int lv;
    int maxHP;
    double speed;
    int range;
    int equipSlot;

    int firePower;
    int torpedo;
    int bomb;
    int armor;
    int antiAircraft;
    int accurate;
    int dodge;
    int antiSubmarine;
    int toss;
    int lucky;

    int ammunition;
    int oil;
    int capacity[5];

    int attackAmount;
    double randModMin;
    double randModMax;
    double randModMinNight;
    double randModMaxNight;

    int skill;
    double repairConsumptionOil;
    double repairConsumptionSteel;

public:
    int currHP;
    int currAmmunition;
    int currOil;
    double crit;
    double critDamageMod;
    double pierce;
    Equip equip[4];
};
