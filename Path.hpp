// #include "Space.hpp"
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