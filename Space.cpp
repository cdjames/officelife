#include <stdexcept>
#include "Space.hpp"
// #include "Convo.hpp" 

int Space::shortcut = 0;

Space::Space(Worker* resident, Worker* visitor)
{
	this->resident = resident;
	this->visitor = visitor;
	this->from = NULL;
	this->can_take = false;
	// std::cout << resident->getName() << std::endl;
	if(resident == NULL)
		this->name = "Break room";
	else if(resident->getName() == "You")
		this->name = resident->getName() + "r office";
	else 
		this->name = resident->getName() + "'s office";
	setActions(); // move to children
	setItems();	  // move to children
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
	Convo* conversation = this->resident->getConversation();
	while(!conversation->active)
		conversation = this->resident->getConversation();
	int choice;
	// std::cout << "conversation active: " << conversation->active << std::endl;
	if(conversation->active)
	{
		std::string name = this->resident->getName();
		std::string item = conversation->offer_item;
		std::cout << name << " says:" << std::endl;
		std::cout << "     " << conversation->message << std::endl;
		std::cout << conversation->answer << std::endl;
		Utils::intakeNum(choice, "your choice.", 1, 0);
	
		switch(choice)
		{
			case 0:	// don't move
				std::cout << conversation->aff_retort << std::endl;
				break;
			case 1:	// don't move
				std::cout << conversation->neg_retort << std::endl;
				break;
		}
		if(item != "" && choice == 0)
		{
			std::cout << "You got the " << item << "!" << std::endl;
			visitor->addItem(item);
			resident->removeItem(item);
			this->removeItem(item);
			conversation->done = true;
			resident->moveInactiveConvo();
		}
	}
	else if(conversation->done)
		std::cout << "Can't you see I'm busy?" << std::endl;
}

void Space::removeItem(std::string item)
{
	std::set<std::string>::iterator iter;
	iter = this->items.find(item);
	if(iter == items.end())
		return;
	else
	{
		this->taken_items.insert(item);
		this->items.erase(iter);
		return;
	}
}

Space* Space::travel(Worker* visitor)
{
	std::map<std::string, Path>::iterator it = this->paths.begin();
	std::vector<std::map<std::string, Path >::iterator > savedpath;
	
	std::cout << "Where would you like to go?" << std::endl;
	/* display choices for user; loop through paths map and display active paths */
	int c = 0;
	for (it = this->paths.begin(); it != this->paths.end(); ++it)
	{
		if(it->second.active) // only do for active paths
		{
			std::cout << "    » Press " << c << " for " << it->first << std::endl;
			savedpath.push_back(it);	// save to use outside block
			c++;
		}
	}
	/* intake choice and return destination space, but only if there are active paths */
	int choice;
	if(savedpath.size() != 0)
	{
		Utils::intakeNum(choice, "your choice, or -1 to stay here.", savedpath.size()-1);
	
		switch(choice)
		{
			case -1:	// don't move
				std::cout << "Yeah, guess I should stay..." << std::endl;
				return this;
				break;
			default:	// move to a path
				/* start at beginning of paths map and move to chosen path */
				std::cout << "Trudging to " << savedpath[choice]->first << "." << std::endl;
				// std::cout << "Space.cpp line 121..." << std::endl;
				if(savedpath[choice]->first == "Hapless IT Guy's office"
					|| savedpath[choice]->first == "Overbearing Manager's office")
					Space::shortcut++;
				// std::cout << "shortcut: " << Space::shortcut << std::endl;
				if(Space::shortcut == 2)
				{
					// std::cout << "Space.cpp line 128..." << std::endl;
					if(this->paths["Hapless IT Guy's office"].destination->activatePath("Overbearing Manager's office"))
					{
						// std::cout << "Space.cpp line 131..." << std::endl;
						std::cout << "You can now access " << "Hapless IT Guy's office" << " directly from " 
								  << "Overbearing Manager's office" << "." << std::endl;

						this->paths["Overbearing Manager's office"].destination->activatePath("Hapless IT Guy's office");
						Space::shortcut++;
					}
				}
				// std::cout << "Space.cpp line 136..." << std::endl;
				/* make the current space active in previous space if it wasn't */
				if(this->from != NULL)
				{
					/* if the path wasn't already active, activate it and inform user */
					if(this->from->activatePath(savedpath[choice]->first))
					{
						std::cout << "You can now access " << savedpath[choice]->first << " directly from " 
								  << this->from->getName() << "." << std::endl;
						savedpath[choice]->second.destination->activatePath(this->from->getName());
					}
				}
				// std::cout << "Space.cpp line 148..." << std::endl;
				/* set this object as the "from" object in the destination space */
				savedpath[choice]->second.destination->setFrom(this);
				/* if there was a visitor, remove it */
				this->visitor = NULL;
				/* return a pointer to the destination space */
				return savedpath[choice]->second.destination;
				break;
		}
	}
	else
	{
		std::cout << "Oh, wait, you're stuck here." << std::endl;
		return this;
	}
}

bool Space::activatePath(std::string name)
{
	// std::cout << "path to activate: " << name << std::endl;

	std::map<std::string, Path>::iterator it = this->paths.find(name);
	if (it != this->paths.end() && it->second.active == false)
	{
		it->second.active = true;
		return true;
	}
	else
		return false;
}

void Space::setFrom(Space* from)
{
	this->from = from;
}

void Space::search(Worker* visitor)
{
	std::set<std::string>::iterator it = this->items.begin(),
									saveditem;
	if(this->items.size() == 0)
		std::cout << "Nothing in the room..." << std::endl;
	else
	{
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
				saveditem = it;	// save to use outside block
			}

			Utils::intakeNum(choice, "enter your choice, or -1 to leave them.", c);
			
			switch(choice)
			{
				case -1:
					std::cout << "Yeah, probably shouldn't take anything..." << std::endl;
					break;
				default:
					saveditem = this->items.begin();
					for (int i = 0; i < choice; i++)
						saveditem++;
					std::cout << "You got the " << *saveditem << "!" << std::endl;
					// std::string save = *saved;
					visitor->addItem(*saveditem);
					if(resident != visitor) // if not in your own office
						resident->removeItem(*saveditem);
					taken_items.insert(*saveditem);
					items.erase(saveditem);
					break;
			}
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

void Space::setActions(std::string action1, std::string action2, std::string action3, std::string action4, std::string action5)
{
	if(action1 != "")
		this->actions.push_back(action1);
	if(action2 != "")
		this->actions.push_back(action2);
	if(action3 != "")
		this->actions.push_back(action3);
	if(action4 != "")
		this->actions.push_back(action4);
	if(action5 != "")
		this->actions.push_back(action5);
}

std::string Space::getName()
{
	return this->name;
}

Worker* Space::getResident()
{
	return this->resident;
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

void Space::deItem()
{
	this->resident->removeItems();
}

void Space::setCanTake(bool can)
{
	this->can_take = can;
}