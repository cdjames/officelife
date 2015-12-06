#include "Utils.hpp"

void Utils::clearCin()
{
	std::cin.clear();
	std::cin.ignore(50, '\n');
}

bool Utils::cinFail()
{
	bool failed = false;
	if(std::cin.fail()) // check for bad input
	{
		clearCin(); // ignore the bad input
		failed = true;
	}
	return failed;
}