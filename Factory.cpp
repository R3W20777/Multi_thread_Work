#include "Factory.h"

Factory::Factory(Product pr, int factoryItemPerHour)
	:pr(pr), factoryItemPerHour(factoryItemPerHour)
{
}

int Factory::GetfactoryItemPerHour()
{
	return factoryItemPerHour;
}
