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
	srand(std::time(0)); // seed the random number generator used Creature die function
	Worker *secretary = new Secretary();
	Worker *itguy = new ITGuy();
	Worker *you = new You();
	// worker->listStats();
	// worker->readConvos();
	// Convo *tConvo = worker->getConversation();
	// std::cout << tConvo->active << std::endl;
	// std::cout << tConvo->message << std::endl;
	// std::cout << "pencil is " << worker->getItem("pencil") << std::endl;
	// std::cout << "pen is " << worker->getItem("pen") << std::endl;

	Space *secrOffice = new Space(secretary);
	Space *itOffice = new Space(itguy);
	Space *youroffice = new Space(you);
	Space *current = new Space(you);
	current = youroffice;
	std::cout << "now in " << current->getName() << std::endl;
	std::vector<Path*> paths;
	std::vector<std::string> names;
	names.push_back(itOffice->getName());
	names.push_back(secrOffice->getName());
	paths.push_back(new Path(itOffice, true));
	paths.push_back(new Path(secrOffice, false));
	youroffice->setPaths(names, paths);
	names.clear();
	paths.clear();
	names.push_back(youroffice->getName());
	names.push_back(secrOffice->getName());
	paths.push_back(new Path(youroffice, true));
	paths.push_back(new Path(secrOffice, false));
	itOffice->setPaths(names, paths);
	// std::cout << itOffice->getName() << ": \n";
	you->listStats();
	// space->addVisitor(you);
	current = current->travel(you);
	std::cout << "now in " << current->getName() << std::endl;
	// current = current->travel(you);
	// std::cout << "now in " << current->getName() << std::endl;

	current->converse(you);
	you->listStats();
	// itOffice->search(worker3);
	// worker3->listStats();
	// itguy->listStats();

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
