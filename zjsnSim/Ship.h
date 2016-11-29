#pragma once
class Ship
{
public:
    Ship();
    Ship(int _type, int _maxHP, double _speed, int _range, int _equipSlot,
        int _firePower, int _torpedo, int _armor, int _antiAircraft, int _dodge, int _antiSubmarine, int _toss, int _lucky,
        int _ammunition, int _oil, int _capacity[4]);
    ~Ship();
private:
    int type;
    int maxHP;
    double speed;
    int range;
    int equipSlot;

    int firePower;
    int torpedo;
    int armor;
    int antiAircraft;
    int dodge;
    int antiSubmarine;
    int toss;
    int lucky;

    int ammunition;
    int oil;
    int capacity[4];
public:
    int currHP;
    int currAmmunition;
    int currOil;
};

