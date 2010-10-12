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
		struct timeval tv;

		try{
			std::cout << "Lookup: [" << req << "]...";
			ctx.modns_lookup(req,&tv);
		}catch(Modnsctx::ModnsLookupException &e){ // non-fatal
			std::cerr << "RESOLUTION FAILURE" << std::endl;
			continue;
		}
		std::cout << (intmax_t)tv.tv_sec * 1000000 + tv.tv_usec << std::endl;
	}
	return EXIT_SUCCESS;
}
