#include "AdminOffice.hpp"
// #include "Convo.hpp" 

AdminOffice::AdminOffice(Worker* resident, Worker* visitor) : Space(resident, visitor)
{
	this->actions.push_back("fight!");
	stoleItem = false;
}
AdminOffice::~AdminOffice()
{}

int AdminOffice::special(Worker* visitor)
{
	int time = this->doRound(visitor, this->resident);
	return time;
}

int AdminOffice::doRound(Worker* visitor, Worker* resident)
{
	int visitor_damage, resident_damage; 
	int time = 5;
	visitor_damage = resident_damage = 0;	// set damage at 0
	CharType visitor_type = visitor->getType(),	// worker types
		 	 resident_type = resident->getType();
	std::string visitor_name = this->worker_names[visitor_type],	// names of workers
				resident_name = this->worker_names[resident_type];
	
	/* make sure fight can take place */
	if(visitor->isDead())
		std::cout << "    " << "Your morale is way too low for that." << std::endl;	
	else if(resident->isDead())
		std::cout << "    " << resident_name << " appears to be knocked out." << std::endl;	
	/* increment rounds and declare start of fight*/
	else
	{
		std::cout << "\nOffice fight! " << visitor_name << " vs " << resident_name << std::endl;

		/* carry out attacks while the opponents are still alive */
		while (!visitor->isDead() && !resident->isDead())
		{
			/* check again for life before attacking; Player 1 attack! */
			if(!visitor->isDead())
			{
				resident_damage = visitor->attacks(resident);
				std::cout << visitor_name << " inflict " << resident_damage << " damage on " << resident_name << "." << std::endl;
				std::cout << resident_name << "'s strength: " << resident->getStrength() << std::endl;
			}
			/* check again for life before attacking; Player 1 attack! */
			if(!resident->isDead())
			{
				visitor_damage = resident->attacks(visitor);
				std::cout << resident_name << " inflicts " << visitor_damage << " damage on " << visitor_name << "." << std::endl;
				std::cout << visitor_name << "r strength: " << visitor->getStrength() << std::endl;
			}
		}

		/* fight is over, so add bonus points for kills and move dead workers to standings */
		if(resident->isDead()) // get an item (so do a search)
		{

			visitor->heal();
			visitor->revive();
			std::cout << "    You won! " << resident_name << " has been temporarily knocked out." << std::endl;
			if(!this->stoleItem)
			{
				/* make room searchable */
				this->setCanTake(true);
				/* search the room? */
				std::string gotitem = this->search(visitor);
				/* erase the conversation related to the item */
				if(gotitem != "")
				{
					std::vector<Convo>* conversations = this->resident->getAllConversations();
					for (int i = 0; i < conversations->size(); i++)
					{
						if((*conversations)[i].offer_item == gotitem)
						{
							(*conversations)[i].done = true;
							this->resident->moveInactiveConvo();
						}
					}
					this->stoleItem = true;
				}
			}
			
			time = 30;
			this->setCanTake(false);
			resident->revive();
		}
		else if(visitor->isDead())
		{
			resident->revive();
			this->setCanTake(false);
			std::cout << "    " << resident_name << " demoralized " << visitor_name << "." << std::endl;
			std::cout << "    " << "Go back to you the break room and grab a bite to cheer up." << std::endl;
			time = 60;
		}
	}
	return time;
}