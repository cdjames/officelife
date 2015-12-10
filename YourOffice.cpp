/*********************************************************************
** Author: Collin James
** Date: 12/8/15
** Description: A specialized Space w/ napping
*********************************************************************/
#include "YourOffice.hpp"

YourOffice::YourOffice(Worker* resident, Worker* visitor) : Space(resident, visitor)
{
	gotREM = false;
	this->actions.push_back("nap");
}
YourOffice::~YourOffice()
{}

int YourOffice::special(Worker* visitor)
{
	int choice,
		time = 5;
	std::cout << "Take a nap?" << std::endl;
	Utils::intakeNum(choice, "0 for yes and 1 for no.", 1, 0);

	switch(choice)
	{
		case 0:	// nap
			std::cout << "(Oh man, I feel great!)" << std::endl;
			visitor->heal(3, false);
			if(!gotREM)
			{
				this->resident->addItem("REM cycles");
				this->gotREM = true;
			}
			time = 45;
			break;
		default: // nap
			std::cout << "(Right, no time for that.)" << std::endl;
			break;
	}
	return time;
}