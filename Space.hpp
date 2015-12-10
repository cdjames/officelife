/*********************************************************************
** Author: Collin James
** Date: 12/8/15
** Description: A class that mimics an office space
*********************************************************************/
#ifndef SPACE_HPP
#define SPACE_HPP
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include "Worker.hpp"
#include "Path.hpp"
#include "Utils.hpp"

class Space
{
protected:
	std::string name;
	Worker* resident;
	Worker* visitor;
	Space* from;
	std::map<std::string, Path> paths;
	std::set<std::string> items;
	std::set<std::string> taken_items;
	std::vector<std::string> actions;
	std::string worker_names[7];// holds names of workers
	bool can_take;
	bool unlock_shortcut;
	int itvisits;
	int bossvisits;

public:
	Space(Worker* resident = NULL, Worker* visitor = NULL);
	virtual ~Space();
	virtual void converse(Worker* visitor);
	virtual Space* travel(Worker* visitor);
	virtual std::string search(Worker* visitor);
	virtual int special(Worker* visitor) = 0; // pure virtual
	virtual void setItems(Worker* subject = NULL);
	virtual std::vector<std::string> getActions();
	virtual bool setPaths(std::vector<std::string> names, std::vector<Path*> paths);
	virtual void setFrom(Space* from);
	virtual std::string getName();
	virtual Worker* getResident();
	virtual void addVisitor(Worker *visitor);
	virtual bool activatePath(std::string name);
	virtual void removeItem(std::string item);
	virtual void setActions(std::string action1 = "search", std::string action2 = "talk", std::string action3 = "move", std::string action4 = "check your items", std::string action5 = "reveal goal", std::string action6 = "");
	virtual void deItem();
	virtual void setCanTake(bool can = true);
};

#endif