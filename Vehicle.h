#pragma once

#include <string>

class Vehicle
{
public:
	Vehicle(std::string vehicleName, int vehicleCapacity);
	int GetvehicleCapacity();
	std::string GetvehicleName();
private:
	std::string vehicleName;
	int vehicleCapacity;
};

