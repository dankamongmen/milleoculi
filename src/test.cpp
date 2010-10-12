#include <ios>
#include <string>
#include <cstdlib>
#include <iostream>
#include <milleoculi.h>

int main(void){
	std::string req;
	Modnsctx ctx;

	std::cout << "Performing lookups (one per line, ^D to end)..." << std::endl;
	while(getline(std::cin,req)){
		try{
			std::cout << "Lookup: [" << req << "]" << std::endl;
			ctx.modns_lookup(req);
		}catch(Modnsctx::ModnsLookupException &e){ // continue
			std::cerr << "Error resolving [" << req << "]" << std::endl;
		}
	}
	// FIXME wait for all lookups to proceed
	std::cout << "All tests succeeded!" << std::endl;
	return EXIT_SUCCESS;
}
