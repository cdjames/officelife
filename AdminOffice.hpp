/*********************************************************************
** Author: Collin James
** Date: 12/8/15
** Description: A specialized Space w/ fighting
*********************************************************************/
#ifndef ADMINOFFICE_HPP
#define ADMINOFFICE_HPP
#include "Worker.hpp"
#include "Space.hpp"

class AdminOffice : public Space
{
protected:
	int doRound(Worker* visitor, Worker* resident);
	bool stoleItem;

public:
	AdminOffice(Worker* resident = NULL, Worker* visitor = NULL);

	virtual ~AdminOffice();

	virtual int special(Worker* visitor); // pure virtual

};

#endif