/*********************************************************************
** Author: Collin James
** Date: 11/5/15
** Description: A class for Managers that inherits from Worker.
*********************************************************************/
#ifndef MANAGER_HPP
#define MANAGER_HPP
// #include "CharType.hpp" // included in Worker.hpp
#include "Worker.hpp"

class Manager : public Worker
{
protected:
	// all inherited from Worker
public:
	/*********************************************************************
	** Description: 
	** Default constructor. Will pass these values to Worker constructor.
	** Set default attributes here.
	*********************************************************************/
	Manager(int att_num=6, 	int att_sides=15, 
			  int def_num=6,	int def_sides=15, 	
			  int arm=20, 	double str=30, 		
			  CharType t=MANAGER
			 );

	/*********************************************************************
	** Description: 
	** A function for initiating attacks. Rolls dice and calls doAttack().
	**
	** SAME IN REPTILE, BLUEMEN, SHADOW! Have them inherit from Manager
	** to avoid duplicating
	*********************************************************************/
	virtual double attacks(Worker* target);

	/*********************************************************************
	** Description: 
	** A function for initiating defense. Returns damage amount via 
	** inflictDamage();
	**
	** SAME IN REPTILE, BLUEMEN, GOBLIN! Have them inherit from Manager
	** to avoid duplicating
	*********************************************************************/
	virtual double defend(double attack_val, CharType attacker, bool halve_attack = false);

	virtual void removeItems(){}
};

#endif