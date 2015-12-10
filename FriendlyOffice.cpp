/*********************************************************************
** Author: Collin James
** Date: 12/8/15
** Description: A specialized Space w/ compliments
*********************************************************************/
#include "FriendlyOffice.hpp"
#include <fstream>
#include <sstream>
// #include "Convo.hpp" 

FriendlyOffice::FriendlyOffice(Worker* resident, Worker* visitor) : Space(resident, visitor)
{
	// setActions(); // move to children
	// setItems();	  // move to children
	readCompliments();
	this->actions.push_back("compliment");
	this->gotEsteem = false;
}
FriendlyOffice::~FriendlyOffice()
{}

int FriendlyOffice::special(Worker* visitor)
{
	int size = this->compliments.size(),
		time = 5;
	if(size > 0)
	{
		/* get a random number between 0 and vector length*/
		int num = (size < 2) ? 0 : (rand() % size);
		std::cout << "    You: " << this->compliments[num] << std::endl;
		std::cout << "    " << this->resident->getName() << ": " << this->replies[num] << std::endl;
		std::cout << "Wow, you feel better about yourself." << std::endl;
		if(!gotEsteem)
		{
			visitor->addItem("Self Esteem");
			visitor->heal();
			this->gotEsteem = true;
		}
	}
	else
		std::cout << "Actually, your self-esteem isn't high enough to give compliments." << std::endl;

	return time;
}

void FriendlyOffice::readCompliments(std::string fname)
{
	std::string file_name = fname;
	file_name += ".csv";

	std::ifstream inputFile;
	inputFile.open(file_name.c_str());
	if (!inputFile)
		std::cout << "Error opening input file " << name << "." << std::endl;
	else
	{
		std::string line;
		while(std::getline(inputFile, line))
		{
			std::istringstream sLine(line);
			std::string field;
			int count = 0;
			while (getline(sLine, field, '^'))
			{
				if(count == 0)
					this->compliments.push_back(field);
				else
					this->replies.push_back(field);
				count++;
			}
		}
	}
	/* testing */
	// for (int i = 0; i < this->compliments.size(); i++)
	// {
	// 	std::cout << this->compliments[i] << std::endl;
	// }
}