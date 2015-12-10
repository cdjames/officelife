/*********************************************************************
** Author: Collin James
** Date: 12/8/15
** Description: A struct for storing path information
*********************************************************************/
class Space;

struct Path
{
	bool active;
	Space* destination;
	Path(Space* dest = NULL, bool act = false)
	{ 
		active = act;
		destination = dest;
	}
};