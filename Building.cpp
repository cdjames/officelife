#include "Building.hpp"
#include "Secretary.hpp"
#include "Billy.hpp"
#include "ITGuy.hpp"
#include "You.hpp"
#include "Manager.hpp"
#include "Stranger.hpp"
#include "YourOffice.hpp"
#include "Utils.hpp"

Building::Building()
{
	this->hero = new You();
	this->time = 480;
	setUpOffices();
	openingStory();
	this->found_items = 0;
	this->stapler = this->printer = this->suspenders = this->freedom = false;
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
	if(iter != hero_items.end())
		return 0;

	else if(this->found_items < 3)
	{
		if(!this->printer)
		{
			iter = hero_items.find("HP LaserJet Printer");
			if(iter != hero_items.end())
			{
				std::cout << "Found printer" << std::endl;
				this->printer = true;
				this->found_items++;
			}
		}
		
		if(!this->stapler)
		{
			iter = hero_items.find("Red Swingline Stapler");
			if(iter != hero_items.end())
			{
				std::cout << "Found stapler" << std::endl;
				this->stapler = true;
				this->found_items++;
			}
		}
		
		if(!this->suspenders)
		{
			iter = hero_items.find("Chotchkie's suspenders");
			if(iter != hero_items.end())
			{
				std::cout << "Found suspenders" << std::endl;
				this->offices["Helpful Secretary"]->getResident()->setConvosActive();
				this->suspenders = true;
				this->found_items++;
			}
		}

		if(!this->shirt)
		{
			iter = hero_items.find("Hawaiian shirt");
			if(iter != hero_items.end())
			{
				this->offices["Hapless IT Guy"]->getResident()->setConvosActive();
			}
		}

		if(!this->cake)
		{
			iter = hero_items.find("cake");
			if(iter != hero_items.end())
			{
				this->offices["Billy from Receiving"]->getResident()->setConvosActive();
			}
		}

		if(!this->hint)
		{
			iter = hero_items.find("hint");
			if(iter != hero_items.end())
			{
				this->offices["Overbearing Manager"]->setCanTake();
			}
		}
	}
	else if(!freedom)
	{
		// iter = hero_items.find("Personal Freedom");
		// if(iter != hero_items.end())
		// {
			this->offices["Breakroom"]->getResident()->setConvosActive();	
		// }
	}
	return 1;
}

int Building::doTurn()
{

	int result = checkItems(),
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
	Space* youroffice = new YourOffice(this->hero);
	Space* breakroom = new Breakroom(new Stranger());
	Space* secretary = new FriendlyOffice(new Secretary());
	Space* itguy = new AdminOffice(new ITGuy());
	Space* manager = new AdminOffice(new Manager());
	Space* billy = new FriendlyOffice(new Billy());

	youroffice->deItem();
	youroffice->setCanTake();

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