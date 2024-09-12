#include "Animator.h"



class TrafficLight  {
    public:
    void lightChange(bool greenlight_Horizontal, Animator& anim);
    void setYellow(bool greenlight_Horizontal, Animator& anim, int& trafficlight_count, int& green_east_west, int& green_north_south);
};