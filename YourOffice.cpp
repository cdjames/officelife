#include "YourOffice.hpp"
// #include "Convo.hpp" 

int Space::shortcut = 0;

YourOffice::YourOffice(Worker* resident, Worker* visitor) : Space(resident, visitor)
{
	// setActions(); // move to children
	// setItems();	  // move to children
}
YourOffice::~YourOffice()
{}