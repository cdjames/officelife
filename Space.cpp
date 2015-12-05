// struct Path
// 	{
// 		bool active{}
// 		Space* destination{}
// 		Path(Space* dest = NULL, act = false)
// 		{ 
// 			active = act{}
// 			destination = dest{}
// 		}
// 	}{}

// 	std::string name{}
// 	Worker* resident{}
// 	Worker* visitor{}
// 	std::map<std::string, Path> paths{}
// 	std::vector<std::string> items{}
// 	std::vector<std::string> actions{}
// bool takeItems;
#include <iostream>
#include "Space.hpp"

Space::Space(Worker* resident, Worker* visitor)
{
	this->resident = resident;
	this->visitor = visitor;
	this->can_take = true;
	std::cout << resident->getName() << std::endl;
	if(resident == NULL)
		this->name = "Break room";
	else if(resident->getName() == "You")
		this->name = resident->getName() + "r office";
	else 
		this->name = resident->getName() + "'s office";
	setItems();
}
Space::~Space()
{
	if(resident)
		delete resident;
	if(visitor)
		delete visitor;
}

void Space::converse(Worker* visitor)
{

}
void Space::travel()
{

}

void Space::search()
{
	std::set<std::string>::iterator it = this->items.begin();
	std::set<std::string>::iterator saved;
	std::cout << "This is what you see in the room..." << std::endl;

	for (it; it != this->items.end(); ++it)
		std::cout << "    • " << *it << std::endl;

	if(this->can_take)
	{
		std::cout << "Is there something that interests you?" << std::endl;
		int c, choice;
		for (it = this->items.begin(), c = 0; it != this->items.end(); ++it, c++)
		{
			std::cout << "    » Press " << c << " for " << *it << std::endl;
			saved = it;
		}

		intakeNum(choice, "enter your choice, or -1 to leave them.");
		
		switch(choice)
		{
			case -1:
				std::cout << "Yeah, probably shouldn't take anything..." << std::endl;
				break;
			default:
				std::cout << "You got the " << *saved << "!" << std::endl;
				// std::string save = *saved;
				this->visitor->addItem(*saved);
				this->resident->removeItem(*saved);
				this->taken_items.insert(*saved);
				this->items.erase(saved);
				break;
		}
	}

}

void Space::setItems(Worker* subject)
{
	// std::cout << this->resident->getName() << std::endl;
	if(this->resident)
		this->items = resident->getItems();
	else if(subject)
		this->items = resident->getItems();
}

bool Space::setPaths(std::vector<std::string> names, std::vector<Path*> paths)
{
	int namesize = names.size();
	int pathssize = paths.size();
	if(namesize != pathssize)
		return 0;
	else
	{
		for (int i = 0; i < namesize; i++)
			this->paths[names[i]] = *paths[i];
			// this->paths.insert(std::pair<std::string, Path>(names[i], paths[i]));
	}
}
std::string Space::getName()
{
	return this->name;
}
std::vector<std::string> Space::getActions()
{
	return this->actions;
}

void Space::addVisitor(Worker *visitor)
{
	this->visitor = visitor;
}

void Space::clearCin()
{
	std::cin.clear();
	std::cin.ignore(50, '\n');
}

bool Space::cinFail()
{
	bool failed = false;
	if(std::cin.fail()) // check for bad input
	{
		clearCin(); // ignore the bad input
		failed = true;
	}
	return failed;
}