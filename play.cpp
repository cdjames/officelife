/*********************************************************************
** Author: Collin James
** Date: 
** Description: 
*********************************************************************/

#include <iostream>
#include <iomanip>
#include <stdlib.h>		// for srand()
#include <ctime>		// for time()
#include <vector>
#include "Worker.hpp"
#include "Secretary.hpp"
#include "Billy.hpp"
#include "ITGuy.hpp"
#include "You.hpp"
#include "Manager.hpp"
#include "Space.hpp"
// #include "Path.hpp"


int main()
{
	// srand(std::time(0)); // seed the random number generator used Creature die function
	Worker *worker = new Secretary();
	Worker *worker2 = new ITGuy();
	Worker *worker3 = new You();
	// worker->listStats();
	// worker->readConvos();
	// Convo *tConvo = worker->getConversation();
	// std::cout << tConvo->active << std::endl;
	// std::cout << tConvo->message << std::endl;
	// std::cout << "pencil is " << worker->getItem("pencil") << std::endl;
	// std::cout << "pen is " << worker->getItem("pen") << std::endl;

	Space *space = new Space(worker);
	Space *space2 = new Space(worker2);
	Space *space3 = new Space(worker3);
	std::vector<Path*> paths;
	std::vector<std::string> names;
	names.push_back(space2->getName());
	names.push_back(space3->getName());
	paths.push_back(new Path(space2, true));
	paths.push_back(new Path(space3, true));
	space->setPaths(names, paths);
	// std::cout << space2->getName() << ": \n";
	// space2->search();

	// tConvo->active = false;
	// std::cout << tConvo->active << std::endl;
	// worker->moveInactiveConvo();
	// std::cout << tConvo->message << std::endl;
	// // Convo *tConvo2 = worker->getConversation();
	// tConvo = worker->getConversation();
	// std::cout << tConvo->message << std::endl;
	// tConvo->active = false;
	// worker->moveInactiveConvo();
	// tConvo = worker->getConversation();
	// std::cout << "\"" << tConvo->message << "\"" << std::endl;

	// delete tConvo;
}
