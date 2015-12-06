#include "AdminOffice.hpp"
// #include "Convo.hpp" 

AdminOffice::AdminOffice(Worker* resident, Worker* visitor) : Space(resident, visitor)
{
	// setActions(); // move to children
	// setItems();	  // move to children
}
AdminOffice::~AdminOffice()
{}