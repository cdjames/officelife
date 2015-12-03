/*********************************************************************
** Author: Collin James
** Date: 12/3/15
** Description: A class for Managers that inherits from Worker.
**
** Implementation file 
*********************************************************************/
#include "Manager.hpp" // please see for function descriptions
#include <iostream>		// for status messages

/* Note that default values are sent to Worker's constructor */
Manager::Manager(int att_num, 	int att_sides, 
					 int def_num, 	int def_sides, 	
					 int arm, 		double str, 	
					 CharType t
					) : Worker(att_num, att_sides, def_num, def_sides, arm, str, t)
{}

double Manager::attacks(Worker* target)
{
	/* 	doAttack() will pass rollDice() output to target defend function
		which will inflict the damage */
	return doAttack(target, rollDice(attack));
}

double Manager::defend(double attack_val, CharType attacker, bool halve_attack)
{
	/* inflictDamage() will return an double and take care of subtracting from strength */
	return inflictDamage(attack_val, halve_attack);
}
