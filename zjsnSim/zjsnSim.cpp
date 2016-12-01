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
    string shipListPath = "E:\\wangmeng\\work\\MyProject\\zjsnSim\\data\\shipList.txt";
    string equipListPath = "E:\\wangmeng\\work\\MyProject\\zjsnSim\\data\\equipList.txt";
    string outputPath = "E:\\wangmeng\\work\\MyProject\\zjsnSim\\data\\output.txt";
    ofstream outputStream = ofstream(outputPath);
    Ship shipList[1200];
    Equip equipList[100];
    loadShipList(shipListPath, shipList);
    loadEquipList(equipListPath, equipList);
    int myFleetNo[6] = { 1, 2, 3, 4, 5, 6 };
    int myFleetEquip[6][4] = {0};
    for (int i = 0; i < 6; i++)
    {
        myFleetEquip[i][0] = 1;
        myFleetEquip[i][1] = 1;
        myFleetEquip[i][2] = 1;
        myFleetEquip[i][3] = 2;
    }
    int opFleetNo[6] = { 6, 6, 6, 6, 6, 6 };
    Fleet* myFleet = new Fleet(myFleetNo, 6, shipList);
    Fleet* opFleet = new Fleet(opFleetNo, 6, shipList);
    myFleet->showFleet(outputStream);
    opFleet->showFleet(outputStream);
    myFleet->loadEquip(myFleetEquip, equipList);
    myFleet->showFleet(outputStream);
    Combat combat = Combat(myFleet, opFleet, true);
    combat.Combating();
    myFleet->showFleet(outputStream);
    opFleet->showFleet(outputStream);

    outputStream.close();

    return 0;
}