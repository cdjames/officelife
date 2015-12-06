#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "Worker.hpp"
#include "Space.hpp"
#include "YourOffice.hpp"
#include "FriendlyOffice.hpp"
#include "AdminOffice.hpp"
#include "Breakroom.hpp"

class Building
{
private:
	Worker* hero;
	std::map<std::string, Space*> offices;
	int time;
	Space* current_office;
	int found_items;
	bool stapler;
	bool printer;
	bool suspenders;
	bool shirt;
	bool cake;
	bool hint;
	bool freedom;
public:
	Building();
	~Building();
	void openingStory();
	void setUpPaths(Space *setup, 
			   		Space *one, Space *two, Space *three, Space *four, Space *five = NULL,
			   		bool onebool = true, bool twobool = true, bool threebool = true, bool fourbool = false, bool fivebool = false);
	int doTurn();
	void setUpOffices();
	int getTime();
	int subtractTime(int minutes);
	int displayMenu();
	int checkItems();
};

#endif