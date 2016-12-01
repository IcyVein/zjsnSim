#pragma once
#include <cmath>
#include <ctime>
#include "Combat.h"
#include "Defines.h"
#include "Ship.h"


using namespace std;

Combat::Combat()
{
}

Combat::Combat(Fleet* _myFleet, Fleet* _opFleet, bool _PVEProtect)
{
    myFleet = _myFleet;
    opFleet = _opFleet;
    PVEProtect = _PVEProtect;

    stage = BUFF;
    course = TADV;
    myFormation = TRAPEZOID;
    opFormation = TRAPEZOID;
    toss = true;

}

Combat::~Combat()
{
}

int Combat::Combating()
{
    Buff();
    Air();
    AntiSub();
    Shell_1();
    Shell_2();
    Torpedo();
    Night();
    return 0;
}
STAGE Combat::Buff()
{
    stage = AIR;
    return stage;
}

STAGE Combat::Air()
{
    stage = ANTISUB;
    return stage;
}

STAGE Combat::AntiSub()
{
    stage = SHELL_1;
    return stage;
}

STAGE Combat::Shell_1()
{
    double attackPower = 0.0;
    double armorPower = 0.0;
    double critRate = 0.0;
    double critMod = 1.0;
    double courseMod = courseCoef(course);
    double myFormationMod = formationCoef(myFormation, stage);
    double opFormationMod = formationCoef(opFormation, stage);
    double damageOrg = 0.0;
    for (int i = 0; i < 6; i++)
    {
        // 我方攻击
        if (myFleet->fireAble[setAttackShip(i, myFleet)-1] == 1) // 选择我方开火舰船并检查是否能够开火
        {
            setDefenseShip(attackShip->getAttackAmount(stage), opFleet);
            critRate = attackShip->crit + formationCritMod(myFormation) + formationCritMod(opFormation);
            if (randR() <= critRate)
                critMod = attackShip->critDamageMod;
            else
                critMod = 1.0;
            attackPower = attackShip->getAttackPower(stage)*courseMod*myFormationMod*critMod;
            for (int j = 0; j < defenseShipAmount; j++)
            {
                armorPower = defenseShip[j]->armor * (1.0 - attackShip->pierce);
                damageOrg = damage(attackPower, armorPower);
                employDamageToEnemy(damageOrg, defenseShip[j]);
            }
            opFleet->checkFireAble(stage);
            opFleet->checkAlive();
            if (opFleet->shipAmount == 0)
            {
                stage = END;
                return stage;
            }
        }

        // 敌方攻击
        if (opFleet->fireAble[setAttackShip(i, opFleet)-1] == 1) // 选择敌方开火舰船并检查是否能够开火
        {
            setDefenseShip(attackShip->getAttackAmount(stage), myFleet);
            critRate = attackShip->crit + formationCritMod(myFormation) + formationCritMod(opFormation);
            if (randR() <= critRate)
                critMod = attackShip->critDamageMod;
            else
                critMod = 1.0;
            if (course == TADV)// 计算航向修正
            {
                courseMod = 0.65;
            }
            else if (course == TDISADV)
            {
                courseMod = 1.15;
            }
            attackPower = attackShip->getAttackPower(stage)*courseMod*opFormationMod*critMod;
            for (int j = 0; j < defenseShipAmount; j++)
            {
                armorPower = defenseShip[j]->armor * (1.0 - attackShip->pierce);
                damageOrg = damage(attackPower, armorPower);
                employDamageToMy(damageOrg, defenseShip[j]);
            }
            myFleet->checkFireAble(stage);
        }
    }

    stage = SHELL_2;
    return stage;
}

STAGE Combat::Shell_2()
{
    double attackPower = 0.0;
    double armorPower = 0.0;
    double critRate = 0.0;
    double critMod = 1.0;
    double courseMod = courseCoef(course);
    double myFormationMod = formationCoef(myFormation, stage);
    double opFormationMod = formationCoef(opFormation, stage);
    double damageOrg = 0.0;
    for (int i = 0; i < 6; i++)
    {
        // 我方攻击
        if (myFleet->fireAble[setAttackShip(i, myFleet) - 1] == 1) // 选择我方开火舰船并检查是否能够开火
        {
            setDefenseShip(attackShip->getAttackAmount(stage), opFleet);
            critRate = attackShip->crit + formationCritMod(myFormation) + formationCritMod(opFormation);
            if (randR() <= critRate)
                critMod = attackShip->critDamageMod;
            else
                critMod = 1.0;
            attackPower = attackShip->getAttackPower(stage)*courseMod*myFormationMod*critMod;
            for (int j = 0; j < defenseShipAmount; j++)
            {
                armorPower = defenseShip[j]->armor * (1.0 - attackShip->pierce);
                damageOrg = damage(attackPower, armorPower);
                employDamageToEnemy(damageOrg, defenseShip[j]);
            }
            opFleet->checkFireAble(stage);
            opFleet->checkAlive();
            if (opFleet->shipAmount == 0)
            {
                stage = END;
                return stage;
            }
        }

        // 敌方攻击
        if (opFleet->fireAble[setAttackShip(i, opFleet) - 1] == 1) // 选择敌方开火舰船并检查是否能够开火
        {
            setDefenseShip(attackShip->getAttackAmount(stage), myFleet);
            critRate = attackShip->crit + formationCritMod(myFormation) + formationCritMod(opFormation);
            if (randR() <= critRate)
                critMod = attackShip->critDamageMod;
            else
                critMod = 1.0;
            if (course == TADV)// 计算航向修正
            {
                courseMod = 0.65;
            }
            else if (course == TDISADV)
            {
                courseMod = 1.15;
            }
            attackPower = attackShip->getAttackPower(stage)*courseMod*opFormationMod*critMod;
            for (int j = 0; j < defenseShipAmount; j++)
            {
                armorPower = defenseShip[j]->armor * (1.0 - attackShip->pierce);
                damageOrg = damage(attackPower, armorPower);
                employDamageToMy(damageOrg, defenseShip[j]);
            }
            myFleet->checkFireAble(stage);
        }
    }

    stage = TORPEDO;
    return stage;
}

STAGE Combat::Torpedo()
{
    stage = NIGHT;
    return stage;
}

STAGE Combat::Night()
{
    stage = END;
    return stage;
}

int Combat::setAttackShip(int rounds, Fleet* fleet)
{
    int order[6] = { 5, 6, 4, 3, 2, 1 };
    int attackShipNo = order[rounds + 6 - fleet->shipAmountOrg];
    attackShip = &fleet->ship[attackShipNo-1];

    return attackShipNo;
}
int Combat::setDefenseShip(int attackAmount, Fleet* fleet)
{
    defenseShipAmount = (int)fmin(attackAmount, fleet->shipAmount);

    int order[6] = { 1, 2, 3, 4, 5, 6 };
    int temp = 0;
    for (int i = 0; i < 6; i++)
    {
        if (fleet->alive[i])
            order[temp++] = order[i];
    }
    foundRandOrder(fleet->shipAmount, order);

    for (int i = 0; i < defenseShipAmount; i++)
    {
        defenseShip[i] = &fleet->ship[order[i]-1];
    }

    return 0;
}

double Combat::damage(double attackPower, double armor)
{
    return attackPower - attackPower * armor / (0.6*attackPower + 0.5*armor);
}

int Combat::employDamageToEnemy(double damageOrg, Ship* target)
{
    if (damageOrg < 0) // 未击穿
    {
        if (randR()<=0.50) // Miss
        {
            damageOrg = 0;
        }
        else
        {
            damageOrg = fmin((attackShip->firePower + 5) / 10.0, target->currHP*0.10);
        }
    }
    else if (damageOrg<target->currHP*0.10) // 擦弹
    {
        damageOrg = target->currHP*0.10;
    }

    int damageFinal = (int)ceil(damageOrg);
    target->currHP = (int)fmax(0, target->currHP - damageFinal);

    return 0;
}

int Combat::employDamageToMy(double damageOrg, Ship* target)
{
    if (PVEProtect == false) // 演习
    {
        employDamageToEnemy(damageOrg, target);
    }
    else
    {
        if (damageOrg < 0) // 未击穿
        {
            if (randR() <= 0.50) // Miss
            {
                damageOrg = 0;
            }
            else
            {
                damageOrg = fmin((attackShip->firePower + 5) / 10.0, target->currHP*0.10);
            }
        }
        else if (damageOrg < target->currHP*0.10) // 擦弹
        {
            damageOrg = target->currHP*0.10;
        }

        if (target->currHP == target->maxHP && damageOrg>target->maxHP*0.75) // 满血保护
        {
            damageOrg = target->maxHP*randR(0.50, 0.75);
        }
        else if (target->currHP / (double)target->maxHP > 0.25) // 中破保护
        {
            damageOrg = fmin(damageOrg, target->currHP - target->maxHP*0.25);
        }
        else // 大破保护
        {
            damageOrg = fmin(damageOrg, target->currHP*0.10);
        }

        int damageFinal = (int)ceil(damageOrg);
        target->currHP = (int)fmax(1, target->currHP - damageFinal);
    }

    return 0;
}
