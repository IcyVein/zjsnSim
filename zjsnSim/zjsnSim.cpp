#pragma once
#include <string>
#include <iostream>
#include "Combat.h"
#include "Defines.h"
#include "Equip.h"
#include "Fleet.h"
#include "Ship.h"

using namespace std;


int main()
{
    ofstream combatLog = ofstream("E:\\wangmeng\\work\\MyProject\\zjsnSim\\data\\combatLog.txt");
    string configPath = "E:\\wangmeng\\work\\MyProject\\zjsnSim\\data\\config.txt";
    int nMax = 0;
    ifstream configFile = ifstream(configPath);
    string myShipListPath;
    string myEquipListPath;
    string opShipListPath;
    string opEquipListPath;
    string outputPath;
    configFile >> nMax >> myShipListPath >> myEquipListPath >> opShipListPath >> opEquipListPath >> outputPath;
    configFile.close();
    ofstream outputStream = ofstream(outputPath);
    Ship* myShipList = new Ship[1200];
    Ship* opShipList = new Ship[1200];
    Equip myEquipList[100];
    Equip opEquipList[100];
    loadShipList(myShipListPath, myShipList);
    loadEquipList(myEquipListPath, myEquipList);
    loadShipList(opShipListPath, opShipList);
    loadEquipList(opEquipListPath, opEquipList);
    int myFleetNo[6] = { 1001, 2, 3, 4, 5, 6 };
    int myFleetEquip[6][4] = {0};
    for (int i = 0; i < 6; i++)
    {
        myFleetEquip[i][0] = 1;
        myFleetEquip[i][1] = 1;
        myFleetEquip[i][2] = 1;
        myFleetEquip[i][3] = 2;
    }
    int opFleetNo[6] = { 10, 11, 12, 13, 14, 15 };
    int opFleetEquip[6][4] = { 0 };
    for (int i = 0; i < 6; i++)
    {
        opFleetEquip[i][0] = 0;
        opFleetEquip[i][1] = 0;
        opFleetEquip[i][2] = 0;
        opFleetEquip[i][3] = 0;
    }
    for (int i = 0; i < nMax; i++)
    {
        if (i%100 == 0)
        {
            cout << i << endl;
        }
        Fleet* myFleet = new Fleet(myFleetNo, 6, myShipList);
        Fleet* opFleet = new Fleet(opFleetNo, 6, opShipList);
        Combat combat = Combat(myFleet, opFleet, true, combatLog);
        combat.Combating();
        opFleet->showFleet(outputStream);
        myFleet->~Fleet();
        opFleet->~Fleet();
    }
    

    //myFleet->showFleet(outputStream);
    //opFleet->showFleet(outputStream);
    //myFleet->loadEquip(myFleetEquip, myEquipList);
    //opFleet->loadEquip(opFleetEquip, opEquipList);
    //myFleet->showFleet(outputStream);
    //opFleet->showFleet(outputStream);
    //Combat combat = Combat(myFleet, opFleet, true, combatLog);
    //combat.Combating();
    //myFleet->showFleet(outputStream);
    //opFleet->showFleet(outputStream);

    combatLog.close();
    outputStream.close();

    return 0;
}