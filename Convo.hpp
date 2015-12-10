/*********************************************************************
** Author: Collin James
** Date: 12/8/15
** Description: A struct to hold conversation information
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