/*********************************************************************
** Author: Collin James
** Date: 
** Description: 
*********************************************************************/
#include <string>

struct Convo
{
	bool active;
	bool done;
	std::string offer_item,
				need_item,
				message,
				answer,
				aff_retort,
				neg_retort;
	Convo() { active = true; done = false; }
};