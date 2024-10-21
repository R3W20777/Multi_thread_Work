#pragma once

#include "Product.h"

class Factory
{
public:
	Factory(Product pr, int factoryItemPerHour);
	int GetfactoryItemPerHour();
private:
	int factoryItemPerHour;
	Product pr;
};

