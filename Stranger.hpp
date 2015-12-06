/*********************************************************************
** Author: Collin James
** Date: 11/5/15
** Description: A class for Strangers that inherits from Worker.
*********************************************************************/
#ifndef STRANGER_HPP
#define STRANGER_HPP
// #include "CharType.hpp" // included in Worker.hpp
#include "Worker.hpp"

class Stranger : public Worker
{
protected:
	// all inherited from Worker
public:
	/*********************************************************************
	** Description: 
	** Default constructor. Will pass these values to Worker constructor.
	** Set default attributes here.
	*********************************************************************/
	Stranger(int att_num=50, 	int att_sides=2000, 
			  int def_num=50,	int def_sides=2000, 	
			  int arm=1000, 	double str=20000, 		
			  CharType t=STRANGER
			 );

	/*********************************************************************
	** Description: 
	** A function for initiating attacks. Rolls dice and calls doAttack().
	**
	** SAME IN REPTILE, BLUEMEN, SHADOW! Have them inherit from Stranger
	** to avoid duplicating
	*********************************************************************/
	virtual double attacks(Worker* target);

	/*********************************************************************
	** Description: 
	** A function for initiating defense. Returns damage amount via 
	** inflictDamage();
	**
	** SAME IN REPTILE, BLUEMEN, GOBLIN! Have them inherit from Stranger
	** to avoid duplicating
	*********************************************************************/
	virtual double defend(double attack_val, CharType attacker, bool halve_attack = false);

	virtual void removeItems(){}
};

#endif