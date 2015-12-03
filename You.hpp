/*********************************************************************
** Author: Collin James
** Date: 11/5/15
** Description: A class for Yous that inherits from Worker.
*********************************************************************/
#ifndef YOU_HPP
#define YOU_HPP
// #include "CharType.hpp" // included in Worker.hpp
#include "Worker.hpp"

class You : public Worker
{
protected:
	bool profdevelopment;
public:
	/*********************************************************************
	** Description: 
	** Default constructor. Will pass these values to Worker constructor.
	** Set default attributes here.
	*********************************************************************/
	You(int att_num=2, 	int att_sides=15, 
			  int def_num=2,	int def_sides=15, 	
			  int arm=15, 	double str=25, 		
			  CharType t=YOU
			 );

	/*********************************************************************
	** Description: 
	** A function for initiating attacks. Rolls dice and calls doAttack().
	**
	** SAME IN REPTILE, BLUEMEN, SHADOW! Have them inherit from You
	** to avoid duplicating
	*********************************************************************/
	virtual double attacks(Worker* target);

	/*********************************************************************
	** Description: 
	** A function for initiating defense. Returns damage amount via 
	** inflictDamage();
	**
	** SAME IN REPTILE, BLUEMEN, GOBLIN! Have them inherit from You
	** to avoid duplicating
	*********************************************************************/
	virtual double defend(double attack_val, CharType attacker, bool halve_attack = false);
};

#endif