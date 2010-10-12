#include <ios>
#include <string>
#include <cstdlib>
#include <iostream>
#include <milleoculi.h>

int main(void){
	std::string req;

	std::cout << "Performing lookups (one per line, ^D to end)..." << std::endl;
	try{
		while(getline(std::cin,req)){
			std::cout << "Lookup: [" << req << "]" << std::endl;
			// FIXME queue lookup
		}
	}catch(std::ios_base::failure &e){
		std::cerr << "Error reading input!" << std::endl;
		return EXIT_FAILURE;
	}
	// FIXME wait for all lookups to proceed
	std::cout << "All tests succeeded!" << std::endl;
	return EXIT_SUCCESS;
}
