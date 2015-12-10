/*********************************************************************
** Author: Collin James
** Date: 12/8/15
** Description: A class to set up offices and handle game logic
*********************************************************************/
#include "Building.hpp"
#include "Secretary.hpp"
#include "Billy.hpp"
#include "ITGuy.hpp"
#include "You.hpp"
#include "Manager.hpp"
#include "Stranger.hpp"
#include "YourOffice.hpp"
#include "Utils.hpp"
// #include <sstream>

Building::Building()
{
	this->hero = new You();
	this->time = 480;
	setUpOffices();
	openingStory();
	this->found_items = 0;
	this->stapler = this->printer = this->suspenders = this->allitems = false;
}

Building::~Building()
{
	if(hero != NULL)
		delete hero;
}

void Building::openingStory()
{
	std::string opening = 
		"\n    You are a nondescript office worker in an average office in the United States. Your days are haunted";
		opening += 
		" by an overbearing boss and a hapless IT guy. However, the office secretary is very helpful, and Billy from";
		opening += 
		" Receiving gets you free stuff sometimes.";
		opening += 
		"\n    Every day you silently wonder: \"How did I get here? What is the purpose of my life?\" You don't have";
		opening += 
		" the answers to these questions, but it seems to you that you could find them if only you could achieve... \n";
		opening += 
		"                            Personal Freedom®\n";
		opening += 
		"\nYou are in your office...";
	std::cout << opening << std::endl;
}

void Building::endingStory()
{
	int year = Utils::currentYear();
	std::string ending = 
		"\n    It turns out that the \"Stranger\" in the breakroom was an actor from 1999's classic Office Space.";
		ending +=
		" He had been looking for the three items you sold him for ";
		// std::cout << Utils::currentYear()-1999; 
		// std::cout << year; 
		ending+= Utils::intToString(year-1999); 
		ending+= " years.\n";
		ending +=
		"    In his ecstacy at finding the items, he agreed to buy them from you for $10 million, granting you";
		ending +=
		" the freedom to pursue whichever interests you desired. You promptly quit your job, bought an island and";
		ending +=
		" an airplane, and received your pilot's license. On your way to your personal island, you crashed your plane";
		ending +=
		" into a blue whale somewhere between here and Micronesia, killing both the whale and yourself.\n";
		ending +=
		"    It turns out that, even with $10 million dollars, a person still dies and doesn't get to fulfill all of";
		ending +=
		" his or her dreams. But at least you won this game. May you rest in peace.\n";
	std::cout << ending << std::endl;
}

int Building::checkItems()
{
	std::set<std::string>::iterator iter;
	std::set<std::string> hero_items = this->hero->getItems();
	iter = hero_items.find("Personal Freedom");
	if(iter != hero_items.end())
		return 0;
	else if(getTime() <= 0)
		return -1;
	/* game isn't over, so if the user hasn't found all key items yet, do a check */
	else if(this->found_items < 3)
	{
		if(!this->printer)
		{
			iter = hero_items.find("HP LaserJet Printer");
			if(iter != hero_items.end())
				foundKeyItem("", this->printer, 0, true, "Hmm, I wonder...");
		}
		
		if(!this->stapler)
		{
			iter = hero_items.find("Red Swingline Stapler");
			if(iter != hero_items.end())
				foundKeyItem("", this->stapler, 0, true, "Hmm, I wonder...");
		}
		
		if(!this->suspenders)
		{
			iter = hero_items.find("Chotchkie's suspenders");
			if(iter != hero_items.end())
				foundKeyItem("Helpful Secretary", this->suspenders, 1, true, "I bet Sue would love to see these...");
		}

		if(!this->shirt)
		{
			iter = hero_items.find("Hawaiian shirt");
			if(iter != hero_items.end())
				foundKeyItem("Hapless IT Guy", this->shirt);
		}

		if(!this->cake)
		{
			iter = hero_items.find("cake");
			if(iter != hero_items.end())
				foundKeyItem("Billy from Receiving", this->cake);
		}

		if(!this->hint)
		{
			iter = hero_items.find("hint");
			if(iter != hero_items.end())
				foundKeyItem("Overbearing Manager", this->hint, 2);
		}
	}
	else if(!allitems)
		foundKeyItem("Breakroom", this->allitems, 1, false, "");

	/* check for end of game again */
	iter = hero_items.find("Personal Freedom");
	if(iter != hero_items.end())
		return 0; // game is won!
	else if(getTime() <= 0)
		return -1; // time is up
	else
		return 1; // continue game
}

void Building::foundKeyItem(std::string officename, bool &founditem, int type, bool increment, std::string message)
{
	std::cout << message << std::endl;
	switch(type)
	{
		case 1: 
			this->offices[officename]->getResident()->setConvosActive();
			break;
		case 2:
			this->offices[officename]->setCanTake();
			break;
		default: // 0, number besides 1 or 2
			break;
	}
	
	founditem = true;
	if(increment)
		this->found_items++;
}

int Building::doTurn()
{
	int result = checkItems(),
		menu,
		special;

	std::cout << "There are " << getTime() << " minutes remaining (do the math)" << std::endl;
	menu = displayMenu();
	switch(menu)
	{
		case 1:
			// search
			this->current_office->search(this->hero);
			subtractTime(10);
			break;
		case 2:
			// converse
			this->current_office->converse(this->hero);
			subtractTime(15);
			break;
		case 3:
			// travel
			this->current_office = this->current_office->travel(this->hero);
			subtractTime(5);
			break;
		case 4:
			// check user items
			this->hero->listStats();
			subtractTime(5);
			break;
		case 5:
			// print goal of game
			std::cout << "Sell 3 Office Space-themed items to the Stranger.	" << std::endl;
			subtractTime(240);
			break;
		case 6:
			// special
			special = this->current_office->special(this->hero);
			subtractTime(special);
			break;
		default:
			std::cout << "Are you sure you want to quit?" << std::endl;
			Utils::intakeNum(menu, "0 to quit or 1 to continue", 1, 0);
			switch(menu)
			{
				case 0:
					// quit
					result = 2;
					break;
				case 1:
					doTurn(); // continue game
					break;
			}
			break;
	}
	if(result != 2)
		result = checkItems();
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
	std::cout << "You wasted " << minutes << " minutes of your life." << std::endl;
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