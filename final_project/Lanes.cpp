#include "Lanes.h"
using namespace std;


void Lanes::lanesonRed(int& halfsize, vector<VehicleBase*>& directionvector) {
    if (directionvector[(halfsize * 2) + 1] != nullptr) { //move cars off map
        directionvector[(halfsize * 2) + 1] = nullptr;
    }

    for (int secondhalf = (halfsize * 2) + 1; secondhalf >= halfsize + 2; secondhalf--){ //move cars to stop light on red
        if (directionvector[secondhalf] == nullptr) { // check if the last square behind light is null
            directionvector[secondhalf] = directionvector[secondhalf - 1]; // set next square to prior square
            directionvector[secondhalf - 1] = nullptr; // set the prior sqaure to null to check loop right.
        }
    }

    for (int firsthalf = halfsize - 1; firsthalf >= 1; firsthalf--){ //move cars to stop light on red
        if (directionvector[firsthalf] == nullptr) { // check if the last square behind light is null
            directionvector[firsthalf] = directionvector[firsthalf - 1]; // set next square to prior square
            directionvector[firsthalf - 1] = nullptr; // set the prior sqaure to null to check loop right.
        }
    }

    if (directionvector[1] != nullptr) { // segfaults happen because of null pointer
        if (directionvector[1]->getVehicleType() == VehicleType::car && (directionvector[2] == nullptr || directionvector[2]->getVehicleID() != directionvector[1]->getVehicleID())){
            directionvector[0] = directionvector[1]; // set to one prior due to the fact this function is ran thrrough a for loop
        } else if (directionvector[1]->getVehicleType() == VehicleType::suv && (directionvector[3] == nullptr || directionvector[3]->getVehicleID() != directionvector[1]->getVehicleID())) {
            directionvector[0] = directionvector[1]; // set to one prior due to the fact this function is ran thrrough a for loop
        } else if(directionvector[1]->getVehicleType() == VehicleType::truck && (directionvector[4] == nullptr || directionvector[4]->getVehicleID() != directionvector[1]->getVehicleID())) {
            directionvector[0] = directionvector[1]; // set to one prior due to the fact this function is ran thrrough a for loop
        }
    }
    
}
void Lanes::lanesonGreen(int& halfsize, vector<VehicleBase*>& directionvector, vector<VehicleBase*>& perpendicularvector, int& green, int& yellow, int& trafficlight_count, int& directioncount) {
    // we find the car length by checking each element before the traffic light and comparing it to the element literally before the traffic light
    directioncount = 0;
    for(int i = 0; i < halfsize; i++){
        if(directionvector[i] == nullptr){
            continue;
        }
        if( directionvector[halfsize - 1] == nullptr){
            continue;
        }
        else if( directionvector[i]->getVehicleID() ==  directionvector[halfsize - 1]->getVehicleID()){
            directioncount += 1;
        }
    }

    // if statement will not run until there is a vehicle is in the intersection.
    if( directionvector[halfsize] != nullptr && (directionvector[halfsize]->getVehicleTurn() == TrafficSignal::right) && (perpendicularvector[halfsize + 2] == nullptr)){
        perpendicularvector[halfsize + 2] = directionvector[halfsize];
        directionvector[halfsize] = nullptr;
    }

    // we create booleans to use later in the code to move the vehicles into the intersection. we compare the length of vehicle to the time left in the green light.
    bool turn_right = true;
    if(directionvector[halfsize - 1] != nullptr &&  directionvector[halfsize - 1]->getVehicleTurn() == TrafficSignal::right && (directioncount + 1 <= ((green + yellow) - trafficlight_count))){
        turn_right = true;
    } else {
        turn_right = false;
    }
    bool go_straight = true;
    if(directionvector[halfsize - 1] != nullptr &&  directionvector[halfsize - 1]->getVehicleTurn() == TrafficSignal::straight && (directioncount + 2 <= ((green + yellow) - trafficlight_count))){
        go_straight = true;
    } else{
        go_straight = false;
    }

    if (directionvector[(halfsize * 2) + 1] != nullptr) { //move cars off map
        directionvector[(halfsize * 2) + 1] = nullptr;
    }

    //  ORDER IS SUPER IMPORTANT, IT IS IMPORTANT TO REMEMBER THAT 
 
    for (int secondhalf = (halfsize * 2) + 1; secondhalf >= halfsize + 1; secondhalf--){ //move cars to stop light on red
        if (directionvector[secondhalf] == nullptr) { // check if the last square behind light is null
            directionvector[secondhalf] = directionvector[secondhalf - 1]; // set next square to prior square
            directionvector[secondhalf - 1] = nullptr; // set the prior sqaure to null to check loop right.
        }
    }

    // this condition takes care of an element within the for loop for the secondhalf of the vector. these if statements are true, it will move the vehicle into the intersection.
    if(directionvector[halfsize-1] != nullptr && (turn_right == true) && (directionvector[halfsize-1]->getVehicleTurn() == TrafficSignal::right)){
        directionvector[halfsize] = directionvector[halfsize - 1];
        directionvector[halfsize - 1] = nullptr;
    }

    if(directionvector[halfsize-1] != nullptr && (go_straight == true) && (directionvector[halfsize-1]->getVehicleTurn() == TrafficSignal::straight)){
        directionvector[halfsize] = directionvector[halfsize - 1];
        directionvector[halfsize - 1] = nullptr;
    }

    for (int firsthalf = halfsize - 1; firsthalf >= 1; firsthalf--){ //move cars to stop light on red
        if (directionvector[firsthalf] == nullptr) { // check if the last square behind light is null
            directionvector[firsthalf] = directionvector[firsthalf - 1]; // set next square to prior square
            directionvector[firsthalf - 1] = nullptr; // set the prior sqaure to null to check loop right.
        }
    }

    if (directionvector[1] != nullptr) { // segfaults happen because of null pointer
        if (directionvector[1]->getVehicleType() == VehicleType::car && (directionvector[2] == nullptr || directionvector[2]->getVehicleID() != directionvector[1]->getVehicleID())){
            directionvector[0] = directionvector[1]; // set to one prior due to the fact this function is ran thrrough a for loop
        } else if (directionvector[1]->getVehicleType() == VehicleType::suv && (directionvector[3] == nullptr || directionvector[3]->getVehicleID() != directionvector[1]->getVehicleID())) {
            directionvector[0] = directionvector[1]; // set to one prior due to the fact this function is ran thrrough a for loop
        } else if(directionvector[1]->getVehicleType() == VehicleType::truck && (directionvector[4] == nullptr || directionvector[4]->getVehicleID() != directionvector[1]->getVehicleID())) {
            directionvector[0] = directionvector[1]; // set to one prior due to the fact this function is ran thrrough a for loop
        }
    }
}