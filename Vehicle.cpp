#include "Vehicle.h"

Vehicle::Vehicle(std::string vehicleName, int vehicleCapacity)
	:vehicleName(vehicleName), vehicleCapacity(vehicleCapacity)
{
}

int Vehicle::GetvehicleCapacity()
{
	return vehicleCapacity;
}
