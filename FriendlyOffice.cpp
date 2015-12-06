#include "FriendlyOffice.hpp"
// #include "Convo.hpp" 

FriendlyOffice::FriendlyOffice(Worker* resident, Worker* visitor) : Space(resident, visitor)
{
	// setActions(); // move to children
	// setItems();	  // move to children
}
FriendlyOffice::~FriendlyOffice()
{}