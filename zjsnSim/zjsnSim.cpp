#include <string>
#include "Ship.h"
#include "Equip.h"

using namespace std;

int main()
{
    string shipListPath = "E:\\wangmeng\\work\\MyProject\\zjsnSim\\data\\shipList.txt";
    Ship ship[1000];
    loadShipList(shipListPath, ship);
    ship[1].showShip();
    ship[2].showShip();
    return 0;
}