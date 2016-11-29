#include <string>
#include "Ship.h"
#include "Equip.h"
#include "Fleet.h"

using namespace std;

int main()
{
    string shipListPath = "E:\\wangmeng\\work\\MyProject\\zjsnSim\\data\\shipList.txt";
    Ship shipList[1000];
    loadShipList(shipListPath, shipList);
    int fleet[6] = { 1, 1, 1, 1, 2, 2 };
    Fleet* myFleet = new Fleet(fleet, 6, shipList);
    myFleet->showFleet();

    return 0;
}