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


Equip::Equip()
{
    no = 0;
    name = "нч";
    type = 0;
    range = 0;

    firePower = 0;
    torpedo = 0;
    bomb = 0;
    armor = 0;

    antiAircraft = 0;
    dodge = 0;
    accurate = 0;
    antiSubmarine = 0;

    toss = 0;
    lucky = 0;
    antiAircraftMod = 0;
    consumption = 0;

    pierce = 0.0;
}

Equip::Equip(int _no, string _name, int _type, int _range,
    int _firePower, int _torpedo, int _bomb, int _armor, 
    int _antiAircraft, int _dodge, int _accurate, int _antiSubmarine, 
    int _toss, int _lucky, double _antiAircraftMod, int _consumption, 
    double _pierce)
{
    no = _no;
    name = _name;
    type = _type;
    range = _range;

    firePower = _firePower;
    torpedo = _torpedo;
    bomb = _bomb;
    armor = _armor;

    antiAircraft = _antiAircraft;
    dodge = _dodge;
    accurate = _accurate;
    antiSubmarine = _antiSubmarine;

    toss = _toss;
    lucky = _lucky;
    antiAircraftMod = _antiAircraftMod;
    consumption = _consumption;

    pierce = _pierce;
}

Equip::~Equip()
{
}

int loadEquipList(string equipListPath, Equip* equip)
{
    ifstream equipListFile = ifstream(equipListPath);
    Equip currEquip;
    int temp = 0;
    while (!equipListFile.eof())
    {
        equipListFile >> currEquip.no >> currEquip.name >> currEquip.type >> currEquip.range
            >> currEquip.firePower >> currEquip.torpedo >> currEquip.bomb >> currEquip.armor 
            >> currEquip.antiAircraft >> currEquip.dodge >> currEquip.accurate >> currEquip.antiSubmarine 
            >> currEquip.toss >> currEquip.lucky >> currEquip.antiAircraftMod >> currEquip.consumption
            >> currEquip.pierce;

        equip[currEquip.no] = currEquip;
    }
    equipListFile.close();
    return 0;
}
