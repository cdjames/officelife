#ifndef YOUROFFICE_HPP
#define YOUROFFICE_HPP
#include "Worker.hpp"
#include "Space.hpp"

class YourOffice : public Space
{
protected:

public:
	YourOffice(Worker* resident = NULL, Worker* visitor = NULL);

	virtual ~YourOffice();

	virtual void special(){} // pure virtual

	// virtual void deItem();
};

#endif