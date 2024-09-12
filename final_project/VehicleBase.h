#ifndef __VEHICLE_BASE_H__
#define __VEHICLE_BASE_H__

// enum: see http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-enum
enum class Direction   {north, south, east, west};
enum class VehicleType {car, suv, truck};
enum class LightColor  {green, yellow, red};
enum class TrafficSignal {straight, right, left};

class VehicleBase
{
   public:
      static int vehicleCount;

   private:
      int         vehicleID;
      VehicleType vehicleType;
      Direction   vehicleDirection;
      TrafficSignal turning;

   public:
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
};

#endif
