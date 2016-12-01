#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Combat.h"
#include "Defines.h"
#include "Ship.h"
#include "Equip.h"
#include <ctime>

using namespace std;

Ship::Ship()
{
    no = 0;
    name = "нч";
    type = 0;
    maxHP = 0;
    speed = 0;
    range = 0;
    equipSlot = 0;

    firePower = 0;
    torpedo = 0;
    bomb = 0;
    armor = 0;
    antiAircraft = 0;
    accurate = 90;
    dodge = 0;
    antiSubmarine = 0;
    toss = 0;
    lucky = 0;

    ammunition = 0;
    oil = 0;
    capacity[0] = 0;
    for (int i = 1; i < 5; i++)
        capacity[i] = 0;

    crit = 0.05;
    critDamageMod = 1.50;
    pierce = 0.0;

    attackAmount = 1;
    randModMin = 0.89;
    randModMax = 1.22;

    currHP = 0;
    currAmmunition = 0;
    currOil = 0;
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
    bomb = 0;
    armor = _armor;
    antiAircraft = _antiAircraft;
    accurate = 90;
    dodge = _dodge;
    antiSubmarine = _antiSubmarine;
    toss = _toss;
    lucky = _lucky;

    ammunition = _ammunition;
    oil = _oil;
    capacity[0] = _capacity[0];
    for (int i = 1; i < 5; i++)
        capacity[i] = _capacity[i];

    crit = 0.05;
    critDamageMod = 1.50;
    pierce = 0.0;

    attackAmount = 1;
    randModMin = 0.89;
    randModMax = 1.22;

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
    bomb = currShip.bomb;
    armor = currShip.armor;
    antiAircraft = currShip.antiAircraft;
    accurate = currShip.accurate;
    dodge = currShip.dodge;
    antiSubmarine = currShip.antiSubmarine;
    toss = currShip.toss;
    lucky = currShip.lucky;

    ammunition = currShip.ammunition;
    oil = currShip.oil;
    capacity[0] = currShip.capacity[0];
    for (int i = 1; i < 5; i++)
        capacity[i] = currShip.capacity[i];

    crit = currShip.crit;
    critDamageMod = currShip.critDamageMod;
    pierce = currShip.pierce;
    attackAmount = currShip.attackAmount;
    randModMin = currShip.randModMin;
    randModMax = currShip.randModMax;

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
            >> currShip.ammunition >> currShip.oil 
            >> currShip.capacity[0] >> currShip.capacity[1] >> currShip.capacity[2] >> currShip.capacity[3] >> currShip.capacity[4];

        currShip.crit = 0.05;
        currShip.critDamageMod = 1.50;
        currShip.pierce = 0.0;
        currShip.attackAmount = 1;
        currShip.randModMin = 0.89;
        currShip.randModMax = 1.22;

        currShip.currHP = currShip.maxHP;
        currShip.currAmmunition = currShip.ammunition;
        currShip.currOil = currShip.oil;
        //if (currShip.capacity[0] != 0 && (currShip.type == 1 || currShip.type == 2)) // CV|Cvl
        //{
        //    for (int i = 1; i < 5; i++)
        //        shipListFile >> currShip.capacity[i];
        //}
        ship[currShip.no] = currShip;
    }
    shipListFile.close();
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

int Ship::showShip(ofstream& outputFile)
{
    outputFile << no << " " << name << " " << type << " " << currHP << "/" << maxHP << " " << speed << " " << range << " " << equipSlot << " "
        << firePower << " " << torpedo << " " << armor << " " << antiAircraft << " " << accurate << " " << dodge << " " << antiSubmarine << " " << toss << " " << lucky << " "
        << ammunition << " " << oil << " " 
        << capacity[0] << " " << capacity[1] << " " << capacity[2] << " " << capacity[3] << " " << capacity[4] << " " 
        << pierce;

    outputFile << endl;
    return 0;
}

int Ship::loadEquip(Equip equip)
{
    range = fmax(range, equip.range);

    firePower += equip.firePower;
    torpedo += equip.torpedo;
    bomb += equip.bomb;
    armor += equip.armor;

    antiAircraft += equip.antiAircraft;
    dodge += equip.dodge;
    accurate += equip.accurate;
    antiSubmarine += equip.antiSubmarine;

    toss += equip.toss;
    lucky += equip.lucky;

    pierce += equip.pierce;

    return 0;
}

int Ship::getAttackAmount(STAGE stage)
{
    return 1;
}

double Ship::getAttackPower(STAGE stage)
{
    double attackPower = 0;
    double hpMod = 1.0;
    double ammunitionMod = 1.0;
    double randMod = randR(randModMin, randModMax);
    attackPower = (firePower + 5)*hpMod*ammunitionMod*randMod;

    return attackPower;
}
