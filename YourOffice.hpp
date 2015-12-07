#ifndef YOUROFFICE_HPP
#define YOUROFFICE_HPP
#include "Worker.hpp"
#include "Space.hpp"

class YourOffice : public Space
{
protected:
	bool gotREM;

public:
	YourOffice(Worker* resident = NULL, Worker* visitor = NULL);

	virtual ~YourOffice();

	virtual int special(Worker* visitor);

	// virtual void deItem();
};

#endif