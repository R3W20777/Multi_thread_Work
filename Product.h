#pragma once

#include <string>

class Product
{
public:
	Product(std::string productName, int productWeight, std::string productPackagingType);
private:
	std::string productName, productPackagingType;
	double productWeight;
};

