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
	this->from = NULL;
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
	if(from)
		delete from;
}

void Space::converse(Worker* visitor)
{

}
Space* Space::travel(Worker* visitor)
{
	std::map<std::string, Path>::iterator it = this->paths.begin(),
									saved;
	std::cout << "Where would you like to go?" << std::endl;
	for (it; it != this->paths.end(); ++it)
		std::cout << "    • " << it->first << std::endl;
	int c, choice;
	for (it = this->paths.begin(), c = 0; it != this->paths.end(); ++it, c++)
	{
		std::cout << "    » Press " << c << " for " << it->first << std::endl;
		saved = it;	// save to use outside block
	}

	intakeNum(choice, "enter your choice, or -1 to leave them.");
	
	switch(choice)
	{
		case -1:
			std::cout << "Yeah, guess I should stay..." << std::endl;
			return NULL;
			break;
		default:
			saved = this->paths.begin();
			for (int i = 0; i < choice; i++)
				saved++;
			std::cout << "Trudging to " << saved->first << "." << std::endl;
			
			/* make the current space active if not */
			if(this->from)
			{
				this->from->activatePath(saved->first);
			}
			saved->second.destination->setFrom(this);
			this->visitor = NULL;
			return saved->second.destination;
			break;
	}
}

void Space::activatePath(std::string name)
{
	std::cout << "path to activate: " << name << std::endl;
}

bool Space::setFrom(Space* from)
{
	this->from = from;
}

void Space::search(Worker* visitor)
{
	std::set<std::string>::iterator it = this->items.begin(),
									saved;
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
			saved = it;	// save to use outside block
		}

		intakeNum(choice, "enter your choice, or -1 to leave them.");
		
		switch(choice)
		{
			case -1:
				std::cout << "Yeah, probably shouldn't take anything..." << std::endl;
				break;
			default:
				saved = this->items.begin();
				for (int i = 0; i < choice; i++)
					saved++;
				std::cout << "You got the " << *saved << "!" << std::endl;
				// std::string save = *saved;
				visitor->addItem(*saved);
				resident->removeItem(*saved);
				taken_items.insert(*saved);
				items.erase(saved);
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