#pragma once
#include <string>
#include <iostream>
#include <ctime>
#include "Combat.h"
#include "Defines.h"
#include "Equip.h"
#include "Fleet.h"
#include "Ship.h"

using namespace std;


int main()
{
    time_t t0 = time(NULL);
    ofstream combatLog = ofstream("E:\\wangmeng\\work\\MyProject\\zjsnSim\\data\\combatLog.txt");
    string configPath = "E:\\wangmeng\\work\\MyProject\\zjsnSim\\data\\config.txt";
    int nMax = 0;
    ifstream configFile = ifstream(configPath);
    string myShipListPath;
    string myEquipListPath;
    string opShipListPath;
    string opEquipListPath;
    string outputPath;

    // 载入配置路径
    configFile >> nMax >> myShipListPath >> myEquipListPath >> opShipListPath >> opEquipListPath >> outputPath;
    // 载入我方出征舰队配置
    int myFleetShipAmount = 0;
    int myFleetNo[6] = { 0 };
    int myFleetLv[6] = { 0 };
    int myFleetEquip[6][4] = { 0 };
    configFile >> myFleetShipAmount;
    for (int i = 0; i < myFleetShipAmount; i++)
    {
        configFile >> myFleetNo[i] >> myFleetLv[i] >> myFleetEquip[i][0] >> myFleetEquip[i][1] >> myFleetEquip[i][2] >> myFleetEquip[i][3];
    }
    // 载入敌方舰队配置
    int opFleetShipAmount = 0;
    int opFleetNo[6] = { 0 };
    int opFleetLv[6] = { 0 };
    int opFleetEquip[6][4] = { 0 };
    configFile >> opFleetShipAmount;
    for (int i = 0; i < opFleetShipAmount; i++)
    {
        configFile >> opFleetNo[i] >> opFleetLv[i] >> opFleetEquip[i][0] >> opFleetEquip[i][1] >> opFleetEquip[i][2] >> opFleetEquip[i][3];
    }
    // 是否有PVE保护
    int pveProtect = 1;
    configFile >> pveProtect;

    configFile.close();

    ofstream outputStream = ofstream(outputPath);
    Ship* myShipList = new Ship[1200];
    Ship* opShipList = new Ship[1200];
    Equip* myEquipList = new Equip[240];
    Equip* opEquipList = new Equip[240];
    loadShipList(myShipListPath, myShipList);
    loadEquipList(myEquipListPath, myEquipList);
    loadShipList(opShipListPath, opShipList);
    loadEquipList(opEquipListPath, opEquipList);

    int repairConsumption[2] = { 0 };
    int lossHP = 0;
    for (int i = 0; i < nMax; i++)
    {
        if (i%100 == 0)
        {
            cout << i << endl;
        }
        Fleet* myFleet = new Fleet(myFleetNo, 6, myShipList);
        myFleet->loadShipLv(myFleetLv);
        myFleet->loadEquip(myFleetEquip, myEquipList);
        Fleet* opFleet = new Fleet(opFleetNo, 6, opShipList);
        opFleet->loadShipLv(opFleetLv);
        opFleet->loadEquip(opFleetEquip, opEquipList);
        Combat combat = Combat(myFleet, opFleet, (bool)(pveProtect == 1), combatLog);
        combat.Combating();
        lossHP += myFleet->repair(repairConsumption);
        myFleet->~Fleet();
        opFleet->~Fleet();
    }
    outputStream << "Repair Consumption per combat" << endl
        << "Oil: " << repairConsumption[0] / (double)nMax
        << "Steel: " << repairConsumption[1] / (double)nMax << endl
        << "Loss HP per combat: " << lossHP / (double)nMax << endl;

    time_t t1 = time(NULL);
    time_t timeConsumptionAll = t1 - t0;
    time_t timeConsumptionMin = timeConsumptionAll / 60;
    time_t timeConsumptionSec = timeConsumptionAll - timeConsumptionMin * 60;
    outputStream << "The time consumption: " << timeConsumptionMin << "m" << timeConsumptionSec << "s." << endl;
    combatLog.close();
    outputStream.close();

    return 0;
}