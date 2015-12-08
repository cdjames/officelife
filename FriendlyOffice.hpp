#ifndef FO_HPP
#define FO_HPP
#include "Worker.hpp"
#include "Space.hpp"
// #include <string>

class FriendlyOffice : public Space
{
protected:
	std::vector<std::string> compliments;
	std::vector<std::string> replies;
	bool gotEsteem;

	void readCompliments(std::string fname = "compliments");

public:
	FriendlyOffice(Worker* resident = NULL, Worker* visitor = NULL);

	virtual ~FriendlyOffice();

	virtual int special(Worker* visitor); // pure virtual

};

#endif