#include "YourOffice.hpp"
// #include "Convo.hpp" 

YourOffice::YourOffice(Worker* resident, Worker* visitor) : Space(resident, visitor)
{
	// setActions(); // move to children
	// setItems();	  // move to children
}
YourOffice::~YourOffice()
{}

// void YourOffice::deItem()
// {
// 	this->resident->removeItems();
// }