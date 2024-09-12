//Justin Barrera and Kevin Chanchavac

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "Animator.h"
#include "VehicleBase.h"
#include "Lanes.h"
#include "Spawn.h"
#include "TrafficLight.h"
#include <map>
using namespace std;

int maximum_simulated_time = 0;
int number_of_sections_before_intersection = 0;
int green_north_south = 0;                 
int yellow_north_south = 0;                       
int green_east_west = 0;                       
int yellow_east_west = 0;
double prob_new_vehicle_northbound = 0.0;
double prob_new_vehicle_southbound = 0.0;
double prob_new_vehicle_eastbound = 0.0;
double prob_new_vehicle_westbound = 0.0;
double proportion_of_cars = 0.0;
double proportion_of_SUVs = 0.0;
double proportion_right_turn_cars = 0.0;
double proportion_left_turn_cars = 0.0;
double proportion_right_turn_SUVs = 0.0;
double proportion_left_turn_SUVs = 0.0;
double proportion_right_turn_trucks = 0.0;
double proportion_left_turn_trucks = 0.0;

map<string, double> input;

int main(int argc, char* argv[]) {
    
    if (argc < 3) {
        cerr << "Missing values in argv[1] and argv[2]" << endl;
      return 0;
    }

    char* initial_seed_char = argv[2];
    int initial_seed = atoi(initial_seed_char);
    ifstream infile(argv[1]);
    mt19937 randomNumberGenerator; // Mersenne twister
    uniform_real_distribution<double> rand_double(0.0,1.0);
    randomNumberGenerator.seed(initial_seed);
    string charinputname;
    double inputvalue;

    while(infile >> charinputname >> inputvalue) {
        string input_name = "";
        for (int i = 0; i < charinputname.length() - 1; i++) {
            char letter = charinputname[i];
            input_name += letter;
        }
        input.insert(pair<string, double>(input_name, inputvalue));
    }
    infile.close();

    maximum_simulated_time = input.at("maximum_simulated_time");
    number_of_sections_before_intersection = input.at("number_of_sections_before_intersection");
    green_north_south = input.at("green_north_south");
    yellow_north_south = input.at("yellow_north_south");
    green_east_west = input.at("green_east_west"); 
    yellow_east_west = input.at("yellow_east_west");
    prob_new_vehicle_northbound = input.at("prob_new_vehicle_northbound");         
    prob_new_vehicle_southbound = input.at("prob_new_vehicle_southbound");         
    prob_new_vehicle_eastbound =  input.at("prob_new_vehicle_eastbound");
    prob_new_vehicle_westbound = input.at("prob_new_vehicle_westbound");              
    proportion_of_cars =  input.at("proportion_of_cars");     
    proportion_of_SUVs = input.at("proportion_of_SUVs");                     
    proportion_right_turn_cars = input.at("proportion_right_turn_cars"); 
    proportion_left_turn_cars = input.at("proportion_left_turn_cars");                
    proportion_right_turn_SUVs = input.at("proportion_right_turn_SUVs");                
    proportion_left_turn_SUVs = input.at("proportion_left_turn_SUVs");                
    proportion_right_turn_trucks = input.at("proportion_right_turn_trucks");
    proportion_left_turn_trucks = input.at("proportion_left_turn_trucks");

    Animator::MAX_VEHICLE_COUNT = 999;  // vehicles will be displayed with three digits

    Animator anim(number_of_sections_before_intersection);

    // construct vectors of VehicleBase* of appropriate size, init to nullptr
    vector<VehicleBase*> westbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    vector<VehicleBase*> eastbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    vector<VehicleBase*> southbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    vector<VehicleBase*> northbound(number_of_sections_before_intersection * 2 + 2, nullptr);

    vector<VehicleBase*> vehicles;  
    bool greenlight_Horizontal = true;
    TrafficLight lights;
    lights.lightChange(greenlight_Horizontal, anim);

    anim.setVehiclesNorthbound(northbound);
    anim.setVehiclesWestbound(westbound);
    anim.setVehiclesSouthbound(southbound);
    anim.setVehiclesEastbound(eastbound);

  
    int draw = 0;
    anim.draw(draw);

    char click;

    cin.get(click);

    int simulation_count = 0;
    int trafficlight_count = 1;
    int directioncount = 0;
    string north = "north";
    string south = "south";
    string west = "west";
    string east = "east";
    Lanes trafficlane;
    Spawn carspawner;
    while (simulation_count < maximum_simulated_time) {
        // red is equal to opposite lights green + yellow time
        for (;trafficlight_count <  green_east_west + yellow_east_west; trafficlight_count++) { // these for loops control the time for each light.
            if (simulation_count != maximum_simulated_time) {
                trafficlane.lanesonRed(number_of_sections_before_intersection, southbound);
                trafficlane.lanesonRed(number_of_sections_before_intersection, northbound);
                trafficlane.lanesonGreen(number_of_sections_before_intersection, westbound, northbound, green_east_west, yellow_east_west, trafficlight_count, directioncount);
                trafficlane.lanesonGreen(number_of_sections_before_intersection, eastbound, southbound, green_east_west, yellow_east_west, trafficlight_count, directioncount);

                carspawner.spawn(prob_new_vehicle_westbound, proportion_of_cars, proportion_of_SUVs, proportion_right_turn_cars, proportion_left_turn_cars, proportion_right_turn_trucks, 
                proportion_left_turn_trucks,proportion_right_turn_SUVs, proportion_right_turn_SUVs, westbound, vehicles, randomNumberGenerator, west);
                carspawner.spawn(prob_new_vehicle_northbound, proportion_of_cars, proportion_of_SUVs, proportion_right_turn_cars, proportion_left_turn_cars, proportion_right_turn_trucks, 
                proportion_left_turn_trucks,proportion_right_turn_SUVs, proportion_right_turn_SUVs, northbound, vehicles, randomNumberGenerator, north);
                carspawner.spawn(prob_new_vehicle_southbound, proportion_of_cars, proportion_of_SUVs, proportion_right_turn_cars, proportion_left_turn_cars, proportion_right_turn_trucks, 
                proportion_left_turn_trucks,proportion_right_turn_SUVs, proportion_right_turn_SUVs, southbound, vehicles, randomNumberGenerator, south);
                carspawner.spawn(prob_new_vehicle_eastbound, proportion_of_cars, proportion_of_SUVs, proportion_right_turn_cars, proportion_left_turn_cars, proportion_right_turn_trucks, 
                proportion_left_turn_trucks,proportion_right_turn_SUVs, proportion_right_turn_SUVs, eastbound, vehicles, randomNumberGenerator, east);
                
                draw += 1;
                anim.setVehiclesNorthbound(northbound);
                anim.setVehiclesWestbound(westbound);
                anim.setVehiclesSouthbound(southbound);
                anim.setVehiclesEastbound(eastbound);

                anim.draw(draw);
                cin.get(click);
                if (trafficlight_count == green_east_west) {
                    anim.setLightEastWest(LightColor::yellow); // if the ticks are equivalent to the last value of the green light, then change the light color to yellow
                } 
                //lights.setYellow(greenlight_Horizontal, anim, trafficlight_count, green_east_west, green_north_south);
                simulation_count += 1;
            }    
        }
        trafficlight_count = 1;
        greenlight_Horizontal = false;
        lights.lightChange(greenlight_Horizontal, anim);
        for (trafficlight_count = 1; trafficlight_count <= green_north_south + yellow_north_south; trafficlight_count++) {
            if (simulation_count != maximum_simulated_time) {
                trafficlane.lanesonRed(number_of_sections_before_intersection, westbound);
                trafficlane.lanesonRed(number_of_sections_before_intersection, eastbound);
                trafficlane.lanesonGreen(number_of_sections_before_intersection, northbound, eastbound, green_north_south, yellow_north_south, trafficlight_count, directioncount);
                trafficlane.lanesonGreen(number_of_sections_before_intersection, southbound, westbound, green_north_south, yellow_north_south, trafficlight_count, directioncount);
                carspawner.spawn(prob_new_vehicle_westbound, proportion_of_cars, proportion_of_SUVs, proportion_right_turn_cars, proportion_left_turn_cars, proportion_right_turn_trucks, 
                proportion_left_turn_trucks,proportion_right_turn_SUVs, proportion_right_turn_SUVs, westbound, vehicles, randomNumberGenerator, west);
                carspawner.spawn(prob_new_vehicle_northbound, proportion_of_cars, proportion_of_SUVs, proportion_right_turn_cars, proportion_left_turn_cars, proportion_right_turn_trucks, 
                proportion_left_turn_trucks,proportion_right_turn_SUVs, proportion_right_turn_SUVs, northbound, vehicles, randomNumberGenerator, north);
                carspawner.spawn(prob_new_vehicle_southbound, proportion_of_cars, proportion_of_SUVs, proportion_right_turn_cars, proportion_left_turn_cars, proportion_right_turn_trucks, 
                proportion_left_turn_trucks,proportion_right_turn_SUVs, proportion_right_turn_SUVs, southbound, vehicles, randomNumberGenerator, south);
                carspawner.spawn(prob_new_vehicle_eastbound, proportion_of_cars, proportion_of_SUVs, proportion_right_turn_cars, proportion_left_turn_cars, proportion_right_turn_trucks, 
                proportion_left_turn_trucks,proportion_right_turn_SUVs, proportion_right_turn_SUVs, eastbound, vehicles, randomNumberGenerator, east);

                draw += 1;
                anim.setVehiclesNorthbound(northbound);
                anim.setVehiclesWestbound(westbound);
                anim.setVehiclesSouthbound(southbound);
                anim.setVehiclesEastbound(eastbound);

                anim.draw(draw);
                cin.get(click);
            
                if (trafficlight_count == green_north_south) {
                    anim.setLightNorthSouth(LightColor::yellow); // if the ticks are equivalent to the last value of the green light, then change the light color to yellow
                }
                //lights.setYellow(greenlight_Horizontal, anim, trafficlight_count, green_east_west, green_north_south);
                simulation_count += 1;
            }
        }
        trafficlight_count = 1;
        greenlight_Horizontal = true;
        lights.lightChange(greenlight_Horizontal, anim);
          
    } 

    // at the end of the while loop, deallocate and free all memory!
    for(double z = 0;  z < vehicles.size(); z++){
        delete vehicles[z];
    }
}


