#include "Factory.h"

Factory::Factory(std::string factoryName, Product pr, int factoryItemPerHour)
	:factoryName(factoryName), pr(pr), factoryItemPerHour(factoryItemPerHour)
{
}

int Factory::GetfactoryItemPerHour()
{
	return factoryItemPerHour;
}

std::string Factory::GetfactoryName()
{
	return factoryName;
}
