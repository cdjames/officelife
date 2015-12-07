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

	virtual int special(Worker* visitor); // pure virtual

};

#endif