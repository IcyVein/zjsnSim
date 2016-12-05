#pragma once

using namespace std;

class Equip
{
public:
    Equip();
    Equip(int _no, string _name, int _type, int _range, 
        int _firePower, int _torpedo, int _bomb, int _armor, int _antiAircraft, int _dodge, int _accurate, int _antiSubmarine, int _toss, int _lucky, double _antiAircraftMod, 
        int _consumption, double _pierce);
    ~Equip();


    friend int loadEquipList(string equipListPath, Equip* equip);
public:
    int no;
    string name;
    int type;
    int range;
    int firePower;
    int torpedo;
    int bomb;
    int armor;
    int antiAircraft;
    int dodge;
    int accurate;
    int antiSubmarine;
    int toss;
    int lucky;
    double antiAircraftMod;
    int consumption;
    double pierce;
};
