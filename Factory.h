#pragma once

#include "Product.h"

class Factory
{
public:
	Factory(std::string factoryName, Product pr, int factoryItemPerHour);
	int GetfactoryItemPerHour();
	std::string GetfactoryName();
	int factoryCapacity = 0;
private:
	std::string factoryName;
	int factoryItemPerHour;
	Product pr;
};

