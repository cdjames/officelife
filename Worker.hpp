/*********************************************************************
** Author: Collin James
** Date: 11/5/15 -- updated 11/20/15
** Description: An abstract base class for different game workers,
** with a default constructor, various getters, and a function for
** generating dice rolls. Contains pure virtual attack and defend
** functions; these need to be defined in derived classes.
*********************************************************************/
#ifndef WORKER_HPP
#define WORKER_HPP
#include "CharType.hpp" // enum enumerating Worker types
#include <cstdlib>	// for rand()
#include <string> 	// for listStats()

class Worker
{
protected:
	/* A struct for storing die values */
	struct DieVal
	{
		int num,
			sides;
		DieVal() { num = sides = 0; }
	};
	/* Main attributes */
	DieVal 	attack,			// store attack roll values
			defense;		// store defense roll values
	int 	armor;			// store armor value
	double	strength,		// store strength value
			orig_strength;	// store strength for revival purposes
	/* Status Booleans */
	bool 	is_dead,		
			attack_halved,
			is_knocked_out;
	/* Type of worker */
	CharType type;

	/*********************************************************************
	** Description: 
	** A generic value generator. Takes a DieVal struct and uses the 
	** values defined there for number of rolls and sides. Returns its roll
	*********************************************************************/
	virtual int rollDice(DieVal roll_data) const;

	/*********************************************************************
	** Description: 
	** Helper function for defend; Compute damage amount and return value.
	** Also subtracts damage from strength via getDamage()
	*********************************************************************/
	// virtual double inflictDamage(double attack_val, double defense_val);
	virtual double inflictDamage(double attack_val, bool halve_attack);

	/*********************************************************************
	** Description: 
	** Helper function for inflictDamage; subtract damage from strength 
	*********************************************************************/
	virtual double computeStrength(double damage);

	/*********************************************************************
	** Description: 
	** Helper function for attacks.  Receives a pointer to a Worker.
	** Generates passes an attack value to the defend function in its
	** target Worker. It returns the final damage to the calling function.
	*********************************************************************/
	virtual double doAttack(Worker* target, double attack_val, bool halve_attack=false);

public:
	/*********************************************************************
	** Description: 
	** Default constructor. Creates a worker with 0 for all stats. Sets
	** all Booleans to false.
	*********************************************************************/
	Worker(int att_num=0, 	int att_sides=0, 
			 int def_num=0, 	int def_sides=0, 	
			 int arm=0, 		double str=0, 	
			 CharType t=NONE
			);

	/*********************************************************************
	** Description: 
	** Default deconstructor. Left empty. Virtual, so derived classes can
	** call their own, but note that this will also be called
	*********************************************************************/
	virtual ~Worker();

	/*********************************************************************
	** Description: 
	** Pure virtual; undefined in Worker
	*********************************************************************/
	virtual double attacks(Worker* target) = 0; // will be pure virtual

	/*********************************************************************
	** Description: 
	** Pure virtual; undefined in Worker
	*********************************************************************/
	virtual double defend(double attack_val, CharType attacker, bool halve_attack = false) = 0;

	/* getters */

	/*********************************************************************
	** Description: 
	** Return true if dead and false if alive
	*********************************************************************/
	virtual bool isDead() const;

	/*********************************************************************
	** Description: 
	** Return true if knocked out and false if prescient
	*********************************************************************/
	virtual bool isKnockedOut() const;

	/*********************************************************************
	** Description: 
	** Return strength attribute (health)
	*********************************************************************/
	virtual double getStrength() const;

	/*********************************************************************
	** Description: 
	** Testing Function; Public access to rollDice(); return roll value
	*********************************************************************/
	virtual int getRoll(DieVal die) const;

	/*********************************************************************
	** Description: 
	** Testing Function; Return type via enum CharType
	*********************************************************************/
	virtual CharType getType() const;

	/*********************************************************************
	** Description: 
	** Testing function; List all attributes
	*********************************************************************/
	virtual void listStats() const; // testing

	/*********************************************************************
	** Description: 
	** Testing function; Reset strength and is_dead
	*********************************************************************/
	virtual void revive();

	/*********************************************************************
	** Description: 
	** Restore some health; (origHealth - health) ÷ 2 (or other factor).
	** Example: Original health 12 - current health 6 = 6÷2 = +3 to health
	** Returns updated health
	*********************************************************************/
	virtual int heal(int factor = 2);

	/*********************************************************************
	** Description: 
	** Kill the worker; send its full original strength to computeStrength()
	** ensuring death. 
	*********************************************************************/
	virtual void kill();

}; // class Worker

#endif