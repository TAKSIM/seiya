#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"

int main()
{
	using namespace boost::gregorian;
	using namespace boost::posix_time;

	std::cout << "Hello world!" << std::endl;
	while (true)
	{
		ptime now = second_clock::local_time();
		date today = now.date();
		std::cout << to_simple_string(now) << std::endl;
		std::cout << to_iso_string(now) << std::endl;
		
	}
	

	return 0;
}