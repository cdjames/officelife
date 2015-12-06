#ifndef FO_HPP
#define FO_HPP
#include "Worker.hpp"
#include "Space.hpp"

class FriendlyOffice : public Space
{
protected:

public:
	FriendlyOffice(Worker* resident = NULL, Worker* visitor = NULL);

	virtual ~FriendlyOffice();

	virtual void special(){} // pure virtual

};

#endif