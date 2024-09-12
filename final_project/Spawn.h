#include <vector>
#include "VehicleBase.h"
#include <random>
using namespace std;

class Spawn {
    public:
        void spawn(double& prob_direction, double& prob_car, double& prob_SUV, double& prob_turnright_car, double& prob_turnleft_car,
        double& prob_turnright_truck, double& prob_turnleft_truck, double& prob_turnright_SUV, double& prob_turnleft_SUV, vector<VehicleBase*>& directionvector, 
        vector<VehicleBase*>& vbs, mt19937& randomNumberGenerator, string& VehicleBaselane);
};