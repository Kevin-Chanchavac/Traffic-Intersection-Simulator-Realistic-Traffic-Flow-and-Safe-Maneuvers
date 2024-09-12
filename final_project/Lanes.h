
#include <vector>
#include "VehicleBase.h"
using namespace std;

class Lanes {
    public:
    void lanesonRed(int& halfsize, vector<VehicleBase*>& directionvector);
    void lanesonGreen(int& halfsize, vector<VehicleBase*>& directionvector, vector<VehicleBase*>& perpendicularvector, int& green, int& yellow, int& trafficlight_count, int& directioncount);
};