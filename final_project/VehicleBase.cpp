#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;

VehicleBase::VehicleBase(VehicleType type, Direction direction, TrafficSignal signal)
    : vehicleID(VehicleBase::vehicleCount++), 
      vehicleType(type),
      vehicleDirection(direction),
      turning(signal)
{}

VehicleBase::VehicleBase(const VehicleBase& other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
      turning(other.turning)
{}

VehicleBase& VehicleBase::operator =(const VehicleBase& other){
  if (this == &other) {
    return *this;
  }

  vehicleID = other.vehicleID;
  vehicleDirection = other.vehicleDirection;
  turning = other.turning;
  return *this;
}

VehicleBase::VehicleBase(VehicleBase&& other)noexcept{
  vehicleID = other.vehicleID;
  vehicleDirection = other.vehicleDirection;
  turning = other.turning;

  other.vehicleID = 0;
  other.vehicleDirection = Direction::north;
  other.turning = TrafficSignal::straight;
}


VehicleBase& VehicleBase::operator = (VehicleBase&& other)noexcept{ // move assignment
  if(this == &other){
      return *this;
    }
    vehicleID = other.vehicleID;
    vehicleDirection = other.vehicleDirection;
    turning = other.turning;

    other.vehicleID = 0;
    other.vehicleDirection = Direction::north;
    other.turning = TrafficSignal::straight;
    return *this;
}

VehicleBase::~VehicleBase() {
}

#endif
