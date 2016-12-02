#pragma once
#include <cstdlib>
#include "Defines.h"
#include "Fleet.h"
#include "Ship.h"


class Combat
{
public:
    Combat(ofstream& _combatLog);
    Combat(Fleet* _myFleet, Fleet* _opFleet, bool _PVEProtect, ofstream& _combatLog);
    ~Combat();

    int Combating();
    STAGE Buff();
    STAGE Air();
    STAGE AntiSub();
    STAGE Shell_1();
    STAGE Shell_2();
    STAGE Torpedo();
    STAGE Night();
    int Results();
    int shell();
    double resultsBar(Fleet* fleet);

    int setAttackShip(int, Fleet*);
    int setDefenseShip(int, Fleet*);
    bool checkHit(Ship aShip, Ship dShip);

    double damage(double attackPower, double armor);
    int employDamageToEnemy(double damageOrg, Ship* target);
    int employDamageToMy(double damageOrg, Ship* target);
public:
    Fleet* myFleet;
    Fleet* opFleet;
    bool PVEProtect;

    ofstream& combatLog;
private:
    STAGE stage;
    COURSE course;
    FORMATION myFormation;
    FORMATION opFormation;
    bool toss;
    AIRCONTROL airControl;

    Ship* attackShip;
    Ship* defenseShip[3];
    int defenseShipAmount;
};

int foundRandOrder(int amount, int* ans, int repeat = 10);