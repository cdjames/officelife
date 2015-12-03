/*********************************************************************
** Author: Collin James
** Date: 
** Description: 
*********************************************************************/

#include <iostream>
#include <iomanip>
#include <stdlib.h>		// for srand()
#include <ctime>		// for time()
#include "Worker.hpp"


int main()
{
	srand(std::time(0)); // seed the random number generator used Creature die function
	Worker worker;
	worker.listStats();
	worker.readConvos();
	Convo *tConvo = worker.getConversation();
	std::cout << tConvo->active << std::endl;
	std::cout << tConvo->message << std::endl;
	tConvo->active = false;
	std::cout << tConvo->active << std::endl;
	worker.moveInactiveConvo();
	std::cout << tConvo->message << std::endl;
	// Convo *tConvo2 = worker.getConversation();
	tConvo = worker.getConversation();
	std::cout << tConvo->message << std::endl;
	tConvo->active = false;
	worker.moveInactiveConvo();
	tConvo = worker.getConversation();
	std::cout << "\"" << tConvo->message << "\"" << std::endl;

	// delete tConvo;
}
