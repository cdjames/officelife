/*********************************************************************
** Author: Collin James
** Date: 
** Description: 
*********************************************************************/
#include <string>

struct Convo
{
	bool active;
	std::string offer_item,
				message,
				answer,
				aff_retort,
				neg_retort;
	Convo() { active = true; }
};