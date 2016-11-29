#pragma once
#include "Defines.h"
#include "Fleet.h"


class Combat
{
public:
    Combat();
    Combat(Fleet* _myFleet, Fleet* _opFleet, bool _PVEProtect);
    ~Combat();

    int Combating();
    STAGE Buff();
    STAGE Air();
    STAGE AntiSub();
    STAGE Shell_1();
    STAGE Shell_2();
    STAGE Torpedo();
    STAGE Night();
public:
    Fleet* myFleet;
    Fleet* opFleet;
    bool PVEProtect;
private:
    STAGE stage;
    COURSE course;
    FORMATION formation;
    bool toss;
    AIRCONTROL airControl;
};

