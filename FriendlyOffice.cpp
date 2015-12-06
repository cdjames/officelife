#include "FriendlyOffice.hpp"
// #include "Convo.hpp" 

int Space::shortcut = 0;

FriendlyOffice::FriendlyOffice(Worker* resident, Worker* visitor) : Space(resident, visitor)
{
	// setActions(); // move to children
	// setItems();	  // move to children
}
FriendlyOffice::~FriendlyOffice()
{}