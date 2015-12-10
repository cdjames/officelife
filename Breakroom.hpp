/*********************************************************************
** Author: Collin James
** Date: 12/8/15
** Description: A specialized Space w/ eating
*********************************************************************/
#ifndef BR_HPP
#define BR_HPP
#include "Worker.hpp"
#include "Space.hpp"

class Breakroom : public Space
{
protected:

public:
	Breakroom(Worker* resident = NULL, Worker* visitor = NULL);

	virtual ~Breakroom();

	virtual int special(Worker* visitor);

};

#endif