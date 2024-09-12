Kevin Chanchavac and Justin Barrera
Professor Szajda
Software Systems
December 2, 2022

Objective- Create vehicles and have them move up a lane and out a lane correctly. Following the logic of actual traffic intersections correctly.

We broke down the design of our code into the following pieces:

1. A makefile takes in TrafficSimulator.cpp,TrafficSimulator.h, VehicleBase.cpp, VehicleBase.h, TrafficLight.cpp, TrafficLight.h, Animator.cpp, Animator.h, Lanes.cpp, Lanes.h. Spawn.cpp, and Spawn.h and compiles all the files.

2.  Header files that declare the functions needed for our code.

3. Files listed below:

TrafficSimulator.cpp:
	In TrafficSimulator we declare everything that should be on screen from time ZERO. First up we declare empty variables that will hold inputted information later. To do this we store in a map the information from the input file. Then we put the values that were put in the map onto the empty variables we declared earlier. We then set the size of each vector by direction (Westbound, eastbound…etc) then we set all of the values in the vector to be empty. We then used TrafficLights just to set the horizontal lights to be green at click zero. We also declared the size of cars to be displayed as three digits. We then set into animator the vectors we created earlier by direction (ex: anim.setVehiclesNorthbound(northbound);). We then signal to the animator to draw everything at time zero. After declaring key int and string variables we start a while loop which will run as long as the simulation time is less than the inputted max simulation time. In this while loop we have two for loops the first for loop helps cars navigate east to west or west to east when the lights are yellow or green and then there is a click the time is shifted for the following by one: draw, simulation_count. Once the ticks are equivalent to the last value of the green light, then change the light color to yellow using animator. The second for loop is coded exactly the same, the only difference is that it controls cars from North to South or the other way around. Once we exit the while loop, we deallocate and free all memory.


VehicleBase.h:
VehicleBase(VehicleType type, Direction originalDirection, TrafficSignal signal);
      VehicleBase(const VehicleBase& other);
      VehicleBase& operator = (const VehicleBase& other); // copy assignment
      VehicleBase(VehicleBase&& other)noexcept; // move constructor
      VehicleBase& operator = (VehicleBase&& other)noexcept; // move assignment
      ~VehicleBase();

      inline int getVehicleID() const { return this->vehicleID; }

      inline VehicleType getVehicleType() const { return this->vehicleType; }
      inline Direction   getVehicleOriginalDirection() const { return this->vehicleDirection; }
      inline TrafficSignal getVehicleTurn() const {return this->turning; }

VehicleBase.cpp:
	The biggest change we added to Vehicle Base is the enum class Traffic Signal, which declare what direction the vehicle is turning.
	We construct a vehicle base object using the enum classes created in vehicleBase.h with the constructor method. We can set the values of another vehicle base object using the copy assignment method. We can declare another object the values of another vehicle base object using the copy constructor method. We can set the values of another vehicle base object using the move assignment method. We can declare another object the values of another vehicle base object using the move constructor method.



TrafficLight.cpp:
	In this file there are two void functions declared Light_Change and Set_Yellow. The first function helps keep everything logical for example when the boolean greenlight_Horizontal is true the lights east to west are set to green and north to south are set to red. On the other hand if greenlight_Horizontal is False then east to west lights are set to red and North to South lights are green. In the other function Set_Yellow it checks if greenlight_Horizontal is True or False and if it's True then it checks if trafficlight_count == green_east_west , if it is True then the lights East to West are set to Yellow. On the other hand if the boolean is false then it checks if trafficlight_count == green_north_south and if it is True then the lights North to South are set to yellow. 

Trafficlight.h:
	This file just helps set the interface that will be used when calling on the void functions in TrafficLight.cpp.


Animator.cpp: 
This class is intended to provide a text-based graphical interface for animating the traffic intersection simulation from CMSC 240.






Lanes.h:
Functions:
void lanesonRed(int& halfsize, vector<VehicleBase*>& directionvector);
    void lanesonGreen(int& halfsize, vector<VehicleBase*>& directionvector, vector<VehicleBase*>& perpendicularvector, int& green, int& yellow, int& trafficlight_count, int& directioncount);


Lanes.cpp:
	Logic:

	We created two functions to control the flow of the lanes. The function (lanesonRed) follows the idea of how an actual lane in traffic works. If there is an element at the last index of the direction vector, move it off the map. The vehicles after the red light will continue to move up by 1 and then spawn off the map. In order to do this. We used a for loop that will after every click, iterate through entirely to move the element in the index prior to the current index, then set the index prior to null. We also check the edge case of there even being an element at those indices to control segfault errors. Without this if statement, the vector could try setting a vector with a value in it to another element which messes up the logic of vehicle flow. There is another for loop for the indices before the red light, that iterate the same way as the first for loop but the cars stop at the red light and wait till go. To control the length of a vehicle and ensure its the right ID, we use if/nested if statements to set the index prior to the element of the current index. We first check if there for nullptrs because if we run these statements and index is null a segfault occurs. Then, for each vehicletype, we check if the element prior and current are not equal, and if they aren’t we set them equal for the vehicle’s length. So when a car spawned as it moves up by one index, it will set directionvector[0] to value of value of the vehicle spawned.

For the function (lanesongreen), The logic above is also used except that we consider the intersection for the vehicles. First we look at length of a vehicle and we calculate that by checking the element before the intersection’s vehicle ID and comparing it to all elements in that lane but the traffic light. If the vehicle is a vehicle that turns right we make an if statement that will set the vehicle to the perpendicular vector. For this all to be true, we created booleans that depend on either or not there is enough time to turn right or go straight, We did this by comparing the length of the car plus the how long it takes to turn right or straight to the amount of time left for that direction’s green light and yellow light signal. After this the logic from the first function is applied but in between the two for loops, we either do/ don’t move the vehicles up one index based off the booleans we created to control intersection flow.

	
Spawn.h: 
Function:
 void spawn(double& prob_direction, double& prob_car, double& prob_SUV, double &prob_turnright_car, double& prob_turnleft_car, double& prob_turnright_truck, double& prob_turnleft_truck, double& prob_turnright_SUV, double& prob_turnleft_SUV, vector<VehicleBase*>& directionvector, vector<VehicleBase*>& vbs, mt19937& randomNumberGenerator, string& VehicleBaselane);

Spawn.cpp:
Logic: 

In the spawn function we take in every probability from the input file, the vector of the direction the vehicles are going in, a vector to hold the vehicles created for memory deallocation, the random number generator, and a string to differentiate each vehicle’s direction.
We first make random probabilities to compare to direction probabilities, vehicle probabilities, and turning probabilities. Using if statements, we first compare the probability of a vehicle even spawning for the direction vector given. In three nested if, we then start comparing whether or not the vehicle is a car/suv/truck in that order. The purpose of doing this is to follow the logic of the equation that 1 = pc + pt +ps, in a way that the computer understands. Once it chooses a vehicle, the function dives in another if/elseif statement that will determinate the creation of vehicles with TrafficSignal enum class either straight or right. Within those ifs statement, we then compare using a input string that has the car’s direction and create the actual vehicle and spawns it at the first element of the direction vector.

