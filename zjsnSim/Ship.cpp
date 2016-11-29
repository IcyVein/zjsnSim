#include "Ship.h"


Ship::Ship()
{
}

Ship::Ship(int _type, int _maxHP, double _speed, int _range, int _equipSlot,
    int _firePower, int _torpedo, int _armor, int _antiAircraft, int _dodge, int _antiSubmarine, int _toss, int _lucky,
    int _ammunition, int _oil, int _capacity[4])
{
    type = _type;
    maxHP = _maxHP;
    speed = _speed;
    range = _range;
    equipSlot = _equipSlot;

    firePower = _firePower;
    torpedo = _torpedo;
    armor = _armor;
    antiAircraft = antiAircraft;
    dodge = _dodge;
    antiSubmarine = antiSubmarine;
    toss = _toss;
    lucky = _lucky;

    ammunition = _ammunition;
    oil = _oil;
    for (int i = 0; i < 4; i++)
        capacity[i] = _capacity[i];

    currHP = _maxHP;
    currAmmunition = _ammunition;
    currOil = _oil;
}

Ship::~Ship()
{
}
