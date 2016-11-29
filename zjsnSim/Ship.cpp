#include <string>
#include <fstream>
#include <iostream>
#include "Ship.h"
#include "Equip.h"

using namespace std;

Ship::Ship()
{
}

Ship::Ship(int _no, string _name, int _type, int _maxHP, double _speed, int _range, int _equipSlot,
    int _firePower, int _torpedo, int _armor, int _antiAircraft, int _dodge, int _antiSubmarine, int _toss, int _lucky,
    int _ammunition, int _oil, int _capacity[5])
{
    no = _no;
    name = _name;
    type = _type;
    maxHP = _maxHP;
    speed = _speed;
    range = _range;
    equipSlot = _equipSlot;

    firePower = _firePower;
    torpedo = _torpedo;
    armor = _armor;
    antiAircraft = _antiAircraft;
    dodge = _dodge;
    antiSubmarine = _antiSubmarine;
    toss = _toss;
    lucky = _lucky;

    ammunition = _ammunition;
    oil = _oil;
    capacity[0] = _capacity[0];
    if (capacity[0] != 0 && (type == 1 || type == 2)) // CV|Cvl
    {
        for (int i = 1; i < 5; i++)
            capacity[i] = _capacity[i];
    }

    currHP = _maxHP;
    currAmmunition = _ammunition;
    currOil = _oil;
}

Ship::~Ship()
{
}

Ship Ship::operator=(Ship currShip)
{
    no = currShip.no;
    name = currShip.name;
    type = currShip.type;
    maxHP = currShip.maxHP;
    speed = currShip.speed;
    range = currShip.range;
    equipSlot = currShip.equipSlot;

    firePower = currShip.firePower;
    torpedo = currShip.torpedo;
    armor = currShip.armor;
    antiAircraft = currShip.antiAircraft;
    dodge = currShip.dodge;
    antiSubmarine = currShip.antiSubmarine;
    toss = currShip.toss;
    lucky = currShip.lucky;

    ammunition = currShip.ammunition;
    oil = currShip.oil;
    capacity[0] = currShip.capacity[0];
    if (capacity[0] != 0 && (type == 1 || type == 2)) // CV|Cvl
    {
        for (int i = 1; i < 5; i++)
            capacity[i] = currShip.capacity[i];
    }

    currHP = currShip.currHP;
    currAmmunition = currShip.currAmmunition;
    currOil = currShip.currOil;
    return *this;
}

int loadShipList(string shipListPath, Ship* ship)
{
    ifstream shipListFile = ifstream(shipListPath);
    Ship currShip;
    while (!shipListFile.eof())
    {
        shipListFile >> currShip.no >> currShip.name >> currShip.type >> currShip.maxHP >> currShip.speed >> currShip.range >> currShip.equipSlot
            >> currShip.firePower >> currShip.torpedo >> currShip.armor >> currShip.antiAircraft >> currShip.dodge >> currShip.antiSubmarine >> currShip.toss >> currShip.lucky
            >> currShip.ammunition >> currShip.oil >> currShip.capacity[0];
        currShip.currHP = currShip.maxHP;
        currShip.currAmmunition = currShip.ammunition;
        currShip.currOil = currShip.oil;
        if (currShip.capacity[0] != 0 && (currShip.type == 1 || currShip.type == 2)) // CV|Cvl
        {
            for (int i = 1; i < 5; i++)
                shipListFile >> currShip.capacity[i];
        }
        ship[currShip.no] = currShip;
    }
    return 0;
}

int Ship::showShip()
{
    cout << no << " " << name << " " << type << " " << maxHP << " " << speed << " " << range << " " << equipSlot << " " 
        << firePower << " " << torpedo << " " << armor << " " << antiAircraft << " " << dodge << " " << antiSubmarine << " " << toss << " " << lucky << " "
        << ammunition << " " << oil << " " << capacity[0] << " ";
    if (capacity[0] != 0 && (type == 1 || type == 2))
    {
        cout << capacity[1] << " " << capacity[2] << " " << capacity[3] << " " << capacity[4];
    }
    cout << endl;
    return 0;
}
