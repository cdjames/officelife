#include "Utils.hpp"

void Utils::clearCin()
{
	std::cin.clear();
	std::cin.ignore(50, '\n');
}

bool Utils::cinFail()
{
	bool failed = false;
	if(std::cin.fail()) // check for bad input
	{
		clearCin(); // ignore the bad input
		failed = true;
	}
	return failed;
}
/* using ideas found here: http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c */
int Utils::currentYear()
{
	time_t thetime = time(0);   // get current time
    struct tm * now = localtime( & thetime ); // convert to local time
    return now->tm_year + 1900;
    // std::cout << "year: " << now->tm_year << std::endl;
    // return now->tm_year;

}

/* using ideas from: http://www.cplusplus.com/articles/D9j2Nwbp/ */
std::string Utils::intToString(int num)
{
	std::string result;          // string which will contain the result
	std::ostringstream convert;   // stream used for the conversion
	convert << num;      // insert the textual representation of 'Number' in the characters in the stream
	result = convert.str();
	return result;
}