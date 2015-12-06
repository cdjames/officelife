#include "AdminOffice.hpp"
// #include "Convo.hpp" 

int Space::shortcut = 0;

AdminOffice::AdminOffice(Worker* resident, Worker* visitor) : Space(resident, visitor)
{
	// setActions(); // move to children
	// setItems();	  // move to children
}
AdminOffice::~AdminOffice()
{}