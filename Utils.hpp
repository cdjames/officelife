#ifndef UTILS_HPP
#define UTILS_HPP
#include <limits>
#include <iostream>

class Utils
{
private:
	
public:
	static void clearCin();

	static bool cinFail();

	/*********************************************************************
	** Description: 
	** Intake a numeral and record it into a variable (with input checking)
	*********************************************************************/
	template <typename T>
	static void intakeNum(T &num_items, std::string message, int upper = -1)
	{ 
		T max = (upper == -1) ? std::numeric_limits<T>::max() : upper; // upper limit for T on system
		std::cout << "Please enter "<< message << std::endl;
		
		do{
			std::cin >> num_items;
			if(Utils::cinFail()) // some bad or strange input
				std::cout << "Please enter a correct value." << std::endl;
			else if (num_items < -1)
				std::cout << "Please enter a positive number." << std::endl;
			else if (num_items > max)
				std::cout << "Please enter a lower number." << std::endl;

		} while (Utils::cinFail() || num_items < -1 || num_items > max);

		Utils::clearCin();
		return;
	}
};

#endif