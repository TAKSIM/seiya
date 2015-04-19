#include "configs.hpp"

int main()
{
	
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