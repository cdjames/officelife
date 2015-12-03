/*********************************************************************
** Author: Collin James
** Date: 11/5/15
** Description: A class for Itguys that inherits from Worker.
*********************************************************************/
#ifndef ITGUY_HPP
#define ITGUY_HPP
// #include "CharType.hpp" // included in Worker.hpp
#include "Worker.hpp"

class ITGuy : public Worker
{
protected:
	// all inherited from Worker
public:
	/*********************************************************************
	** Description: 
	** Default constructor. Will pass these values to Worker constructor.
	** Set default attributes here.
	*********************************************************************/
	ITGuy(int att_num=1, 	int att_sides=6, 
			  int def_num=1,	int def_sides=6, 	
			  int arm=3, 	double str=10, 		
			  CharType t=ITGUY
			 );

	/*********************************************************************
	** Description: 
	** A function for initiating attacks. Rolls dice and calls doAttack().
	**
	** SAME IN REPTILE, BLUEMEN, SHADOW! Have them inherit from Itguy
	** to avoid duplicating
	*********************************************************************/
	virtual double attacks(Worker* target);

	/*********************************************************************
	** Description: 
	** A function for initiating defense. Returns damage amount via 
	** inflictDamage();
	**
	** SAME IN REPTILE, BLUEMEN, GOBLIN! Have them inherit from Itguy
	** to avoid duplicating
	*********************************************************************/
	virtual double defend(double attack_val, CharType attacker, bool halve_attack = false);
};

#endif