#pragma once
#include <cmath>
#include <ctime>
#include <fstream>
#include "Combat.h"
#include "Defines.h"
#include "Ship.h"


using namespace std;

Combat::Combat(ofstream& _combatLog) :combatLog(_combatLog)
{
}

Combat::Combat(Fleet* _myFleet, Fleet* _opFleet, bool _PVEProtect, ofstream& _combatLog):combatLog(_combatLog)
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
    //combatLog << "End : " << Results() << " at " << stage <<endl;
    int results = Results();
    combatLog << results << endl;
    return results;
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
        // �ҷ�attack
        if (myFleet->fireAble[setAttackShip(i, myFleet)-1] == 1) // ѡ���ҷ����𽢴�������Ƿ��ܹ�����
        {
            setDefenseShip(attackShip->getAttackAmount(stage), opFleet);
            for (int j = 0; j < defenseShipAmount; j++)
            {
                //combatLog << "Shell 1 (My): " << attackShip->name << "attack" << defenseShip[j]->name;
                if (checkHit(*attackShip, *defenseShip[j]) == false) // miss
                {
                    //combatLog << "miss" << endl;
                    continue;
                }
                critRate = attackShip->crit + formationCritMod(myFormation) + formationCritMod(opFormation);
                if (randR() <= critRate)
                {
                    critMod = attackShip->critDamageMod;
                    //combatLog << "crit";
                }
                else
                {
                    critMod = 1.0;
                    //combatLog << "hit";
                }
                attackPower = attackShip->getAttackPower(stage)*courseMod*myFormationMod*critMod;
                armorPower = defenseShip[j]->armor * (1.0 - attackShip->pierce);
                damageOrg = damage(attackPower, armorPower);
                int tempHP = defenseShip[j]->currHP;
                employDamageToEnemy(damageOrg, defenseShip[j]);
                //combatLog << damageOrg << "( " << tempHP << "-->" << defenseShip[j]->currHP << " )" << endl;
            }
            opFleet->checkFireAble(stage);
            opFleet->checkAlive();
            if (opFleet->shipAmount == 0)
            {
                stage = END;
                return stage;
            }
        }

        // �з�attack
        if (opFleet->fireAble[setAttackShip(i, opFleet)-1] == 1) // ѡ��з����𽢴�������Ƿ��ܹ�����
        {
            setDefenseShip(attackShip->getAttackAmount(stage), myFleet);
            
            if (course == TADV)// ���㺽������
            {
                courseMod = 0.65;
            }
            else if (course == TDISADV)
            {
                courseMod = 1.15;
            }
            for (int j = 0; j < defenseShipAmount; j++)
            {
                //combatLog << "Shell 1 (Op): " << attackShip->name << "attack" << defenseShip[j]->name;
                if (checkHit(*attackShip, *defenseShip[j]) == false) // miss
                {
                    //combatLog << "miss" << endl;
                    continue;
                }
                critRate = attackShip->crit + formationCritMod(myFormation) + formationCritMod(opFormation);
                if (randR() <= critRate)
                {
                    critMod = attackShip->critDamageMod;
                    //combatLog << "crit";
                }
                else
                {
                    critMod = 1.0;
                    //combatLog << "hit";
                }
                attackPower = attackShip->getAttackPower(stage)*courseMod*opFormationMod*critMod;
                armorPower = defenseShip[j]->armor * (1.0 - attackShip->pierce);
                damageOrg = damage(attackPower, armorPower);
                int tempHP = defenseShip[j]->currHP;
                employDamageToMy(damageOrg, defenseShip[j]);
                //combatLog << damageOrg << "( " << tempHP << "-->" << defenseShip[j]->currHP << " )" << endl;
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
        // �ҷ�attack
        if (myFleet->fireAble[setAttackShip(i, myFleet) - 1] == 1) // ѡ���ҷ����𽢴�������Ƿ��ܹ�����
        {
            setDefenseShip(attackShip->getAttackAmount(stage), opFleet);
            for (int j = 0; j < defenseShipAmount; j++)
            {
                //combatLog << "Shell 2 (My): " << attackShip->name << "attack" << defenseShip[j]->name;
                if (checkHit(*attackShip, *defenseShip[j]) == false) // miss
                {
                    //combatLog << "miss" << endl;
                    continue;
                }
                critRate = attackShip->crit + formationCritMod(myFormation) + formationCritMod(opFormation);
                if (randR() <= critRate)
                {
                    critMod = attackShip->critDamageMod;
                    //combatLog << "crit";
                }
                else
                {
                    critMod = 1.0;
                    //combatLog << "hit";
                }
                attackPower = attackShip->getAttackPower(stage)*courseMod*myFormationMod*critMod;
                armorPower = defenseShip[j]->armor * (1.0 - attackShip->pierce);
                damageOrg = damage(attackPower, armorPower);
                int tempHP = defenseShip[j]->currHP;
                employDamageToEnemy(damageOrg, defenseShip[j]);
                //combatLog << damageOrg << "( " << tempHP << "-->" << defenseShip[j]->currHP << " )" << endl;
            }
            opFleet->checkFireAble(stage);
            opFleet->checkAlive();
            if (opFleet->shipAmount == 0)
            {
                stage = END;
                return stage;
            }
        }

        // �з�attack
        if (opFleet->fireAble[setAttackShip(i, opFleet) - 1] == 1) // ѡ��з����𽢴�������Ƿ��ܹ�����
        {
            setDefenseShip(attackShip->getAttackAmount(stage), myFleet);

            if (course == TADV)// ���㺽������
            {
                courseMod = 0.65;
            }
            else if (course == TDISADV)
            {
                courseMod = 1.15;
            }
            for (int j = 0; j < defenseShipAmount; j++)
            {
                //combatLog << "Shell 2 (Op): " << attackShip->name << "attack" << defenseShip[j]->name;
                if (checkHit(*attackShip, *defenseShip[j]) == false) // miss
                {
                    //combatLog << "miss" << endl;
                    continue;
                }
                critRate = attackShip->crit + formationCritMod(myFormation) + formationCritMod(opFormation);
                if (randR() <= critRate)
                {
                    critMod = attackShip->critDamageMod;
                    //combatLog << "crit";
                }
                else
                {
                    critMod = 1.0;
                    //combatLog << "hit";
                }
                attackPower = attackShip->getAttackPower(stage)*courseMod*opFormationMod*critMod;
                armorPower = defenseShip[j]->armor * (1.0 - attackShip->pierce);
                damageOrg = damage(attackPower, armorPower);
                int tempHP = defenseShip[j]->currHP;
                employDamageToMy(damageOrg, defenseShip[j]);
                //combatLog << damageOrg << "( " << tempHP << "-->" << defenseShip[j]->currHP << " )" << endl;
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
    int order1[6] = { 5, 6, 4, 3, 2, 1 };
    int order2[6] = { 1, 2, 3, 4, 5, 6 };
    int* order;
    if (stage == SHELL_1)
    {
        order = order1;
    }
    else
        order = order2;
    
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

bool Combat::checkHit(Ship aShip, Ship dShip)
// ��������������֮�����
// ������������֮��Ϊx��ʵ��������Ϊy�����о��������ʹ�ʽ v1.0��
// y = x^3 / 3 / 45^2 + x/2 + 50
// ��x����[-50, 50]ʱ��y����[5, 95]
// ��dy/dx = x^2 / 45^2 +0.5��
// ����dy/dx����[0.5, 2]
{
    int trueAccutate = aShip.accurate - dShip.dodge;
    double hitRate = pow(trueAccutate, 3) / 3 / 45 / 45 + trueAccutate / 2 + 50; // ���������ʹ�ʽ v1.0
    hitRate = fmax(hitRate, 0.05);
    hitRate = fmin(hitRate, 0.95);
    if (randR() < hitRate)
        return true;
    else
        return false;
}

double Combat::damage(double attackPower, double armor)
{
    return attackPower - attackPower * armor / (0.6*attackPower + 0.5*armor);
}

int Combat::employDamageToEnemy(double damageOrg, Ship* target)
{
    if (damageOrg < 0) // δ����
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
    else if (damageOrg<target->currHP*0.10) // ����
    {
        damageOrg = target->currHP*0.10;
    }

    int damageFinal = (int)ceil(damageOrg);
    target->currHP = (int)fmax(0, target->currHP - damageFinal);

    return 0;
}

int Combat::employDamageToMy(double damageOrg, Ship* target)
{
    if (PVEProtect == false) // ��ϰ
    {
        employDamageToEnemy(damageOrg, target);
    }
    else
    {
        if (damageOrg < 0) // δ����
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
        else if (damageOrg < target->currHP*0.10) // ����
        {
            damageOrg = target->currHP*0.10;
        }

        if (target->currHP == target->maxHP && damageOrg>target->maxHP*0.75) // ��Ѫ����
        {
            damageOrg = target->maxHP*randR(0.50, 0.75);
        }
        else if (target->currHP / (double)target->maxHP > 0.25) // ���Ʊ���
        {
            damageOrg = fmin(damageOrg, target->currHP - target->maxHP*0.25);
        }
        else // ���Ʊ���
        {
            damageOrg = fmin(damageOrg, target->currHP*0.10);
        }

        int damageFinal = (int)ceil(damageOrg);
        target->currHP = (int)fmax(1, target->currHP - damageFinal);
    }

    return 0;
}

int Combat::Results()
//SS, S, AA, A, B, C, D�ֱ��Ӧ����ȼ���
// 7, 6,  5, 4, 3, 2, 1
//flag[0]������ȫ���н���������н�����������1�ҵн����޻�����������Ӧ1����4
//flag[1]���ҷ����ˣ��ҷ����ˡ�������Ӧ1����2
//flag[2]�������콢���콢��������Ӧ1����2
//flag[3]���ҷ�ս�������ڵз�2.5����ս�������ڵз���ս���������ڵз���������Ӧ1����3
//����ȫ���н����ҷ����� - SS 1100
//����ȫ���н����ҷ����� - S 1200
//����������н�(2 / 3, 3 / 4, 4 / 5, 4 / 6, 5 / 6)�����콢 - AA 2010
//����������н�(2 / 3, 3 / 4, 4 / 5, 4 / 6, 5 / 6) - A 2020
//����������2 / 3���ҷ����ˣ��������콢 - A 3110
//����������2 / 3���ҷ����ˣ����콢��� - B 3120
//����������2 / 3���ҷ����ˣ��������콢 - B 3210
//����������2 / 3���ҷ����ˣ����콢���ҷ�ս�������ڵз�2.5�� - B 3221
//����������2 / 3���ҷ����ˣ����콢���ҷ�ս����С�ڵз�2.5�� - C 3222
//�н�ȫ����ս�������ڵз����ҷ����� - B(����&ս��) / C(��ϰ) 41-2
//�н�ȫ����ս�������ڵз����ҷ����� - C 42-2
//�н�ȫ����ս���������ڵз� - D 4--3

{
    double myResultsBar = resultsBar(opFleet);
    double opResultsBar = resultsBar(myFleet);

    double opSunkRate = (opFleet->shipAmountOrg - opFleet->shipAmount) / (double)opFleet->shipAmountOrg;

    int flag[4] = { 0 };

    if (abs(opSunkRate - 1.0)<1e-6)
    {
        flag[0] = 1;
    }
    else if (opSunkRate >= 2 / 3.0)
    {
        flag[0] = 2;
    }
    else if (opSunkRate >= 1/7.0)
    {
        flag[0] = 3;
    }
    else
    {
        flag[0] = 4;
    }

    if (abs(opResultsBar)<1e-6)
    {
        flag[1] = 1;
    }
    else
    {
        flag[1] = 2;
    }

    if (opFleet->ship[0].currHP == 0)
    {
        flag[2] = 1;
    }
    else
    {
        flag[2] = 2;
    }

    if (myResultsBar >= opResultsBar*2.5)
    {
        flag[3] = 1;
    }
    else if (myResultsBar >= opResultsBar)
    {
        flag[3] = 2;
    }
    else
    {
        flag[3] = 3;
    }

    //����ȫ���н����ҷ����� - SS 1100
    if (flag[0] == 1 && flag[1] == 1)
    {
        return 7;
    }
    //����ȫ���н����ҷ����� - S 1200
    if (flag[0] == 1 && flag[1] == 2)
    {
        return 6;
    }
    //����������н�(2 / 3, 3 / 4, 4 / 5, 4 / 6, 5 / 6)�����콢 - AA 2010
    if (flag[0] == 2 && flag[2] == 1)
    {
        return 5;
    }
    //����������н�(2 / 3, 3 / 4, 4 / 5, 4 / 6, 5 / 6) - A 2020
    if (flag[0] == 2 && flag[2] == 2)
    {
        return 4;
    }
    //����������2 / 3���ҷ����ˣ��������콢 - A 3110
    if (flag[0] == 3 && flag[1] == 1 && flag[2] == 1)
    {
        return 4;
    }
    //����������2 / 3���ҷ����ˣ����콢��� - B 3120
    if (flag[0] == 3 && flag[1] == 1 && flag[2] == 2)
    {
        return 3;
    }
    //����������2 / 3���ҷ����ˣ��������콢 - B 3210
    if (flag[0] == 3 && flag[1] == 2 && flag[2] == 1)
    {
        return 3;
    }
    //����������2 / 3���ҷ����ˣ����콢���ҷ�ս�������ڵз�2.5�� - B 3221
    if (flag[0] == 3 && flag[1] == 2 && flag[2] == 2 && flag[3] == 1)
    {
        return 3;
    }
    //����������2 / 3���ҷ����ˣ����콢���ҷ�ս����С�ڵз�2.5�� - C 3222
    if (flag[0] == 3 && flag[1] == 2 && flag[2] == 2 && flag[3] == 2)
    {
        return 2;
    }
    //�н�ȫ����ս�������ڵз����ҷ����� - B(����&ս��) / C(��ϰ) 41-2
    if (flag[0] == 4 && flag[1] == 1 &&  flag[3] == 2 && PVEProtect == true)
    {
        return 3;
    }
    if (flag[0] == 4 && flag[1] == 1 && flag[3] == 2 && PVEProtect == false)
    {
        return 2;
    }
    //�н�ȫ����ս�������ڵз����ҷ����� - C 42-2
    if (flag[0] == 4 && flag[1] == 2 && flag[3] == 2)
    {
        return 2;
    }
    //�н�ȫ����ս���������ڵз� - D 4--3
    if (flag[0] == 4 && flag[3] == 3)
    {
        return 1;
    }

    return 0;
}

double Combat::resultsBar(Fleet* fleet)
{
    int currHP = 0;
    int maxHP = 0;

    for (int i = 0; i < fleet->shipAmountOrg; i++)
    {
        currHP += fleet->ship[i].currHP;
        maxHP += fleet->ship[i].maxHP;
    }

    return (maxHP - currHP) / (double)maxHP;
}
