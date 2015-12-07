#include "Breakroom.hpp"
// #include "Convo.hpp" 

Breakroom::Breakroom(Worker* resident, Worker* visitor) : Space(resident, visitor)
{
	// setActions(); // move to children
	// setItems();	  // move to children
	this->actions.push_back("eat");
	this->name = "the Breakroom";
}
Breakroom::~Breakroom()
{}

int Breakroom::special(Worker* visitor)
{
	int choice,
		time = 5,
		c = 0;
	std::set<std::string> items = visitor->getItems();
	std::vector<std::string> saveditems;
	std::cout << "Hungry?" << std::endl;
	// if(this->items.size() != 0)
	// {
		// std::cout << "\nYour food: " << std::endl;

	for (std::set<std::string>::iterator it = items.begin(); it != items.end(); ++it)
	{
		if(*it == "granola" || *it == "cake")
		{
			std::cout << "    • " << *it << " (press " << c << " to eat)" << std::endl;
			saveditems.push_back(*it);
			c++;
		}
	}

	if(saveditems.size() != 0)
	{
		Utils::intakeNum(choice, "your choice or -1 to cancel.", items.size()-1, -1);

		switch(choice)
		{
			case -1:	// don't eat
				std::cout << "(Right, no time for that.)" << std::endl;
				break;
			default: // eat
				std::cout << "You ate the " << saveditems[choice] << ". Now you feel sluggish." << std::endl;
				std::cout << "(Was that a good idea?)" << std::endl;
				visitor->removeItem(saveditems[choice]);
				time = 15;
				break;
		}
	} 
	else
		std::cout << "\nYou don't have any food." << std::endl;
	
	return time;
}