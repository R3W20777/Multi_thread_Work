#pragma once

#include <string>

class Vehicle
{
public:
	Vehicle(std::string vehicleName, int vehicleCapacity);
	int GetvehicleCapacity();
private:
	std::string vehicleName;
	int vehicleCapacity;
};

