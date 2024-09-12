#include "Spawn.h"
using namespace std;
#include <random>


// probabilites used for spawning are based off the equations given in pdf using the logic behind the if statements ordering.
void Spawn::spawn(double& prob_direction, double& prob_car, double& prob_SUV, double& prob_turnright_car, double& prob_turnleft_car,
double& prob_turnright_truck, double& prob_turnleft_truck, double& prob_turnright_SUV, double& prob_turnleft_SUV, vector<VehicleBase*>& directionvector, 
vector<VehicleBase*>& vehicles, mt19937& randomNumberGenerator, string& VehicleBaselane) {
    uniform_real_distribution<double> rand_double(0.0,1.0);
    double randprob_direction = rand_double(randomNumberGenerator); 
    double randprob_cartype = rand_double(randomNumberGenerator);
    if(randprob_direction <= prob_direction){   // will spawn car if random prob for direction is less than input probability of direction used for each direction
        if(randprob_cartype < prob_car) {  // checks if random prob for cartype is less than car, implemented to follow equation of cartype probabilities creating car
            double randprob_turning = rand_double(randomNumberGenerator);
            if (randprob_turning < 1 - prob_turnright_car + prob_turnleft_car) { // spawns vehicles of straight
                if (directionvector[0] == nullptr){ 
                    if (VehicleBaselane == "north") { // this string will help differentiate creating vehicles going different directions
                        VehicleBase* northcar = new VehicleBase(VehicleType:: car, Direction:: north, TrafficSignal:: straight); 
                        vehicles.push_back(northcar); // this will keep memory of vehicles saved in a vector to be deallocated later
                        directionvector[0] = northcar; // reallocates memory
                    } else if (VehicleBaselane == "east") {
                        VehicleBase* eastcar = new VehicleBase(VehicleType:: car, Direction:: east, TrafficSignal:: straight);
                        vehicles.push_back(eastcar);
                        directionvector[0] = eastcar;
                    } else if (VehicleBaselane == "south") {
                        VehicleBase* southcar = new VehicleBase(VehicleType:: car, Direction:: south, TrafficSignal:: straight);
                        vehicles.push_back(southcar);
                        directionvector[0] = southcar;
                    } else if (VehicleBaselane == "west") {
                        VehicleBase* westcar = new VehicleBase(VehicleType:: car, Direction:: west, TrafficSignal:: straight);
                        vehicles.push_back(westcar);
                        directionvector[0] = westcar;
                    }
                }
            } else if (randprob_turning < 1 - prob_turnleft_car) {// spawns vehicles of right
                if (directionvector[0] == nullptr) {
                    if (VehicleBaselane == "north") { // this string will help differentiate creating vehicles going different directions
                        VehicleBase* northcar = new VehicleBase(VehicleType:: car,Direction:: north, TrafficSignal:: right); 
                        vehicles.push_back(northcar); 
                        directionvector[0] = northcar;
                    } else if (VehicleBaselane == "east") {
                        VehicleBase* eastcar = new VehicleBase(VehicleType:: car, Direction:: east, TrafficSignal:: right);
                        vehicles.push_back(eastcar);
                        directionvector[0] = eastcar;
                    } else if (VehicleBaselane == "south") {
                        VehicleBase* southcar = new VehicleBase(VehicleType:: car, Direction:: south, TrafficSignal:: right);
                        vehicles.push_back(southcar);
                        directionvector[0] = southcar;
                    } else if (VehicleBaselane == "west") {
                        VehicleBase* westcar = new VehicleBase(VehicleType:: car, Direction:: west, TrafficSignal:: right);
                        vehicles.push_back(westcar);
                        directionvector[0] = westcar;
                    }
                }
            } 
        } if (randprob_cartype < prob_car + prob_SUV) { //checks if random prob for cartype is less than car + suv, implemented to follow equation of cartype probabilities creatinhg SUV vehicle
            double randprob_turning = rand_double(randomNumberGenerator);
            if (randprob_turning < 1 - prob_turnright_SUV + prob_turnleft_SUV) {
                if (directionvector[0] == nullptr){
                    if (VehicleBaselane == "north") { // this string will help differentiate creating vehicles going different directions
                        VehicleBase* northsuv = new VehicleBase(VehicleType:: suv, Direction:: north, TrafficSignal:: straight); 
                        vehicles.push_back(northsuv);
                        directionvector[0] = northsuv;
                    } else if (VehicleBaselane == "east") {
                        VehicleBase* eastsuv = new VehicleBase(VehicleType:: suv, Direction:: east, TrafficSignal:: straight);
                        vehicles.push_back(eastsuv);
                        directionvector[0] = eastsuv;
                    } else if (VehicleBaselane == "south") {
                        VehicleBase* southsuv = new VehicleBase(VehicleType:: suv, Direction:: south, TrafficSignal:: straight);
                        vehicles.push_back(southsuv);
                        directionvector[0] = southsuv;
                    } else if (VehicleBaselane == "west") {
                        VehicleBase* westsuv = new VehicleBase(VehicleType:: suv, Direction:: west, TrafficSignal:: straight);
                        vehicles.push_back(westsuv);
                        directionvector[0] = westsuv;
                    }
                }
            } else if (randprob_turning < 1 - prob_turnleft_SUV) {
                if (directionvector[0] == nullptr) {
                    if (VehicleBaselane == "north") { // this string will help differentiate creating vehicles going different directions
                        VehicleBase* northsuv = new VehicleBase(VehicleType:: suv, Direction:: north, TrafficSignal:: right); 
                        vehicles.push_back(northsuv);
                        directionvector[0] = northsuv;
                    } else if (VehicleBaselane == "east") {
                        VehicleBase* eastsuv = new VehicleBase(VehicleType:: suv, Direction:: east, TrafficSignal:: right);
                        vehicles.push_back(eastsuv);
                        directionvector[0] = eastsuv;
                    } else if (VehicleBaselane == "south") {
                        VehicleBase* southsuv = new VehicleBase(VehicleType:: suv, Direction:: south, TrafficSignal:: right);
                        vehicles.push_back(southsuv);
                        directionvector[0] = southsuv;
                    } else if (VehicleBaselane == "west") {
                        VehicleBase* westsuv = new VehicleBase(VehicleType:: suv, Direction:: west, TrafficSignal:: right);
                        vehicles.push_back(westsuv);
                        directionvector[0] = westsuv;
                    }
                }
            }
        } if (randprob_cartype < 1) { //checks if random prob for cartype is less than 1, implemented to follow equation of cartype probabilities (truck) 
            double randprob_turning = rand_double(randomNumberGenerator);
            if (randprob_turning < 1 - prob_turnright_truck + prob_turnleft_truck) {
                if (directionvector[0] == nullptr){
                    if (VehicleBaselane == "north") { // this string will help differentiate creating vehicles going different directions
                        VehicleBase* northtruck = new VehicleBase(VehicleType::truck, Direction:: north, TrafficSignal:: straight); 
                        vehicles.push_back(northtruck);
                        directionvector[0] = northtruck;
                    } else if (VehicleBaselane == "east") {
                        VehicleBase* easttruck = new VehicleBase(VehicleType::truck, Direction:: east, TrafficSignal:: straight);
                        vehicles.push_back(easttruck);
                        directionvector[0] = easttruck;
                    } else if (VehicleBaselane == "south") {
                        VehicleBase* southtruck = new VehicleBase(VehicleType::truck, Direction:: south, TrafficSignal:: straight);
                        vehicles.push_back(southtruck);
                        directionvector[0] = southtruck;
                    } else if (VehicleBaselane == "west") {
                        VehicleBase* westtruck = new VehicleBase(VehicleType::truck, Direction:: west, TrafficSignal:: straight);
                        vehicles.push_back(westtruck);
                        directionvector[0] = westtruck;
                    }
                }
            } else if (randprob_turning < 1 - prob_turnleft_truck) {
                if (directionvector[0] == nullptr) {
                    if (VehicleBaselane == "north") {  // this string will help differentiate creating vehicles going different directions
                        VehicleBase* northtruck = new VehicleBase(VehicleType::truck, Direction:: north, TrafficSignal:: right); 
                        vehicles.push_back(northtruck);
                        directionvector[0] = northtruck;
                    } else if (VehicleBaselane == "east") {
                        VehicleBase* easttruck = new VehicleBase(VehicleType::truck, Direction:: east, TrafficSignal:: right);
                        vehicles.push_back(easttruck);
                        directionvector[0] = easttruck;
                    } else if (VehicleBaselane == "south") {
                        VehicleBase* southtruck = new VehicleBase(VehicleType::truck, Direction:: south, TrafficSignal:: right);
                        vehicles.push_back(southtruck);
                        directionvector[0] = southtruck;
                    } else if (VehicleBaselane == "west") {
                        VehicleBase* westtruck = new VehicleBase(VehicleType::truck, Direction:: west, TrafficSignal:: right);
                        vehicles.push_back(westtruck);
                        directionvector[0] = westtruck;
                    }
                }
            }
        }
    }
}