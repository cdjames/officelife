#include "Building.hpp"
#include "Secretary.hpp"
#include "Billy.hpp"
#include "ITGuy.hpp"
#include "You.hpp"
#include "Manager.hpp"
#include "Stranger.hpp"
#include "Utils.hpp"

Building::Building()
{
	this->hero = new You();
	this->time = 480;
	setUpOffices();
	openingStory();
}
Building::~Building()
{
	if(hero != NULL)
		delete hero;
}
void Building::openingStory()
{
	std::cout << "Game Story Here" << std::endl;
}

int Building::checkItems()
{
	std::set<std::string>::iterator iter;
	std::set<std::string> hero_items = this->hero->getItems();
	iter = hero_items.find("Personal Freedom");
	if(iter != items.end())
		return 0;

	iter = hero_items.find("HP LaserJet Printer");
	if(iter != items.end())
		return 0;
}
int Building::doTurn()
{

	int result = 1,
		menu;
	menu = displayMenu();
	switch(menu)
	{
		case 1:
			// search
			this->current_office->search(this->hero);
			break;
		case 2:
			// converse
			this->current_office->converse(this->hero);
			break;
		case 3:
			// travel
			this->current_office = this->current_office->travel(this->hero);
			break;
		case 4:
			// check items
			this->hero->listStats();
			break;
		case 5:
			// special
			break;
		default:
			std::cout << "Are you sure you want to quit?" << std::endl;
			Utils::intakeNum(menu, "0 to quit or 1 to continue", 1);
			switch(menu)
			{
				case 0:
					// quit
					result = 2;
					break;
				case 2:
					doTurn(); // continue game
					break;
			}
			break;
	}
	return result;
}
void Building::setUpOffices()
{
	Space* youroffice = new Space(this->hero);
	Space* breakroom = new Space(new Stranger());
	Space* secretary = new Space(new Secretary());
	Space* itguy = new Space(new ITGuy());
	Space* manager = new Space(new Manager());
	Space* billy = new Space(new Billy());

	setUpPaths(youroffice, manager, itguy, breakroom, secretary, billy);
	setUpPaths(breakroom, youroffice, manager, itguy, secretary, billy, true, true, true, true, true);
	setUpPaths(secretary, manager, billy, breakroom, youroffice, NULL);
	setUpPaths(itguy, youroffice, billy, breakroom, manager, NULL);
	setUpPaths(manager, secretary, youroffice, breakroom, itguy, NULL);
	setUpPaths(billy, secretary, itguy, breakroom, youroffice, NULL);

	offices["You"] = youroffice;
	offices["Breakroom"] = breakroom;
	offices["Helpful Secretary"] = secretary;
	offices["Hapless IT Guy"] = itguy;
	offices["Overbearing Manager"] = manager;
	offices["Billy from Receiving"] = billy;

	this->current_office = youroffice;
}
void Building::setUpPaths(Space *setup, 
						  Space *one, Space *two, Space *three, Space *four, Space *five,
						  bool onebool, bool twobool, bool threebool, bool fourbool, bool fivebool)
{
	std::vector<Path*> paths;
	std::vector<std::string> names;
	if(one != NULL)
	{
		names.push_back(one->getName());
		paths.push_back(new Path(one, onebool));		
	}

	if(two != NULL)
	{
		names.push_back(two->getName());
		paths.push_back(new Path(two, twobool));
	}

	if(three != NULL)
	{
		names.push_back(three->getName());
		paths.push_back(new Path(three, threebool));
	}

	if(four != NULL)
	{
		names.push_back(four->getName());
		paths.push_back(new Path(four, fourbool));
	}

	if(five != NULL) 
	{
		names.push_back(five->getName());
		paths.push_back(new Path(five, fivebool));
	}		

	setup->setPaths(names, paths);
}
int Building::getTime()
{
	return this->time;
}
int Building::subtractTime(int minutes)
{
	this->time -= minutes;
	return getTime();
}
int Building::displayMenu()
{
	std::vector<std::string> actions = this->current_office->getActions();
	int input = -1,
		size = actions.size();

	std::cout << std::endl;
	std::cout << "You're in " << this->current_office->getName() << ". Choose an action:" << std::endl;
	for (int i = 0; i < size; i++)
	{
		if(actions[i] != "")
		{
			std::cout << "   " << i+1 << " - " << actions[i] << std::endl;	
		}
	}
	std::cout << "   0 - Quit game (there is no saving!)" << std::endl;

	std::cin >> input;

	/* test for bad input and loop until good */
	while(input < 0 || input > size || Utils::cinFail())
	{
		std::cout << "Please enter numbers between 0 and " << size << "." << std::endl;
		Utils::clearCin(); // clear cin, otherwise endless loop!
		input = displayMenu(); // run menu again
	}

	return input;
}