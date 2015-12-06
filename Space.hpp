#ifndef SPACE_HPP
#define SPACE_HPP
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include "Worker.hpp"
#include "Path.hpp"

class Space
{
protected:
	// struct Path
	// {
	// 	bool active;
	// 	Space* destination;
	// 	Path(Space* dest = NULL, bool act = false)
	// 	{ 
	// 		active = act;
	// 		destination = dest;
	// 	}
	// };

	std::string name;
	Worker* resident;
	Worker* visitor;
	Space* from;
	std::map<std::string, Path> paths;
	std::set<std::string> items;
	std::set<std::string> taken_items;
	std::vector<std::string> actions;
	bool can_take;

public:
	Space(Worker* resident = NULL, Worker* visitor = NULL);
	virtual ~Space();
	virtual void converse(Worker* visitor);
	virtual Space* travel(Worker* visitor);
	virtual void search(Worker* visitor);
	// virtual void special() = 0; // pure virtual
	virtual void special(){} // pure virtual

	virtual void setItems(Worker* subject = NULL);
	virtual std::vector<std::string> getActions();
	virtual bool setPaths(std::vector<std::string> names, std::vector<Path*> paths);
	virtual void setFrom(Space* from);
	virtual std::string getName();
	/*********************************************************************
	** Description: 
	** Intake a numeral and record it into a variable (with input checking)
	*********************************************************************/
	template <typename T>
	void intakeNum(T &num_items, std::string message, int upper = 1)
	{ 
		T imax = std::numeric_limits<T>::max(); // upper limit for T on system
		std::cout << "Please enter "<< message << std::endl;
		
		do{
			std::cin >> num_items;
			if(cinFail()) // some bad or strange input
				std::cout << "Please enter a correct value." << std::endl;
			else if (num_items < -1)
				std::cout << "Please enter a positive number." << std::endl;
			else if (num_items > imax)
				std::cout << "Please enter a lower number." << std::endl;

		} while (cinFail() || num_items < -1 || num_items > imax);

		clearCin();
		return;
	}

	virtual void clearCin();

	virtual bool cinFail();

	virtual void addVisitor(Worker *visitor);

	virtual bool activatePath(std::string name);

	virtual void removeItem(std::string item);

	virtual void setActions(std::string action1 = "search", std::string action2 = "talk", std::string action3 = "move", std::string action4 = "check your items", std::string action5 = "");
};

#endif