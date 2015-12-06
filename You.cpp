/*********************************************************************
** Author: Collin James
** Date: 12/3/15
** Description: A class for Yous that inherits from Worker.
**
** Implementation file 
*********************************************************************/
#include "You.hpp" // please see for function descriptions
#include <iostream>		// for status messages

/* Note that default values are sent to Worker's constructor */
You::You(int att_num, 	int att_sides, 
					 int def_num, 	int def_sides, 	
					 int arm, 		double str, 	
					 CharType t
					) : Worker(att_num, att_sides, def_num, def_sides, arm, str, t)
{
	profdevelopment = false;
}

double You::attacks(Worker* target)
{
	if(profdevelopment)
	{
		double attack_val = rollDice(attack),
		damage;
		/* uncomment to display status message! */
		// std::cout << "******* Goblin achilles achieved! *******" << std::endl;
		damage = doAttack(target, attack_val, true); // pass true for "halve_attack" boolean
		// halved++;
	
		return damage;
	}
	
	/* 	doAttack() will pass rollDice() output to target defend function
		which will inflict the damage */
	else
		return doAttack(target, rollDice(attack));
}

double You::defend(double attack_val, CharType attacker, bool halve_attack)
{
	if(profdevelopment)
	{
		double 	special = (1 + rand() % 2), // random between 1 and 2 (50% chance)
				damage = 0;

		if(special == 1) // disappear!
		{
			damage = 0;
			// disappeared++; // keep track of disappearances
			/* uncomment to display status message! */
			// std::cout << "* ** * Shadow disappeared! * ** *" << std::endl;
		}
		else // normal defense
			damage = inflictDamage(attack_val, halve_attack);

		return damage;
	}
	/* inflictDamage() will return an double and take care of subtracting from strength */
	else
		return inflictDamage(attack_val, halve_attack);
}

void You::removeItems()
{
		this->items.clear();
}
