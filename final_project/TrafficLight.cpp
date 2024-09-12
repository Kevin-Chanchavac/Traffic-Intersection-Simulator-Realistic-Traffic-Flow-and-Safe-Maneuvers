#include "TrafficLight.h"



void TrafficLight::lightChange(bool greenlight_Horizontal, Animator& anim) {
    if (greenlight_Horizontal == true) {
        anim.setLightNorthSouth(LightColor::red);
        anim.setLightEastWest(LightColor::green);
    } else if (greenlight_Horizontal == false) {
        anim.setLightNorthSouth(LightColor::green);
        anim.setLightEastWest(LightColor::red);
    }
}

void TrafficLight::setYellow(bool greenlight_Horizontal, Animator& anim, int& trafficlight_count, int& green_east_west, int& green_north_south) {
    if (greenlight_Horizontal == true) {
        if (trafficlight_count == green_east_west) {
            anim.setLightEastWest(LightColor::yellow); // if the ticks are equivalent to the last value of the green light, then change the light color to yellow
    
        } 
     if (greenlight_Horizontal == false) {
        if (trafficlight_count == green_north_south) {
            anim.setLightNorthSouth(LightColor::yellow); // if the ticks are equivalent to the last value of the green light, then change the light color to yellow
        }
        }
    }
}