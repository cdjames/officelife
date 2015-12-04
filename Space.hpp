#ifndef SPACE_HPP
#define SPACE_HPP
#include <string>
#include <map>
#include <vector>
#include <set>
#include "Worker.hpp"
#include "Path.hpp"

class Space
{
private:
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
	std::map<std::string, Path> paths;
	std::set<std::string> items;
	std::vector<std::string> actions;
	bool takeItems;

public:
	Space(Worker* resident = NULL, Worker* visitor = NULL);
	virtual ~Space();
	virtual void converse(Worker* visitor);
	virtual void travel();
	virtual void search();
	// virtual void special() = 0; // pure virtual
	virtual void special(){} // pure virtual

	virtual void setItems(Worker* subject = NULL);
	virtual std::vector<std::string> getActions();
	virtual bool setPaths(std::vector<std::string> names, std::vector<Path*> paths);
	virtual std::string getName();


};

#endif