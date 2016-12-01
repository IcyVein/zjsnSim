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
    string outputPath = "E:\\wangmeng\\work\\MyProject\\zjsnSim\\data\\output.txt";
    ofstream outputStream = ofstream(outputPath);
    Ship shipList[1200];
    loadShipList(shipListPath, shipList);
    int myFleetNo[6] = { 1, 2, 3, 4, 5, 6 };
    int opFleetNo[6] = { 6, 6, 6, 6, 6, 6 };
    Fleet* myFleet = new Fleet(myFleetNo, 6, shipList);
    Fleet* opFleet = new Fleet(opFleetNo, 6, shipList);
    myFleet->showFleet(outputStream);
    opFleet->showFleet(outputStream);
    Combat combat = Combat(myFleet, opFleet, true);
    combat.Combating();
    myFleet->showFleet(outputStream);
    opFleet->showFleet(outputStream);

    outputStream.close();

    return 0;
}