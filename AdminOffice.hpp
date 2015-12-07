#ifndef ADMINOFFICE_HPP
#define ADMINOFFICE_HPP
#include "Worker.hpp"
#include "Space.hpp"

class AdminOffice : public Space
{
protected:

public:
	AdminOffice(Worker* resident = NULL, Worker* visitor = NULL);

	virtual ~AdminOffice();

	virtual int special(Worker* visitor){} // pure virtual

};

#endif