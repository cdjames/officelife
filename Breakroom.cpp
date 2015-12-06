#include "Breakroom.hpp"
// #include "Convo.hpp" 

int Space::shortcut = 0;

Breakroom::Breakroom(Worker* resident, Worker* visitor) : Space(resident, visitor)
{
	// setActions(); // move to children
	// setItems();	  // move to children
}
Breakroom::~Breakroom()
{}