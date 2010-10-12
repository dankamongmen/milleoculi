#ifndef MILLEOCULI
#define MILLEOCULI

// We use the asynchronous DNS resolver library of Ian Jackson et al.
#include <adns.h>
#include <stdexcept>

class Modnsctx { // Wraps C-ADNS, providing C++/sort functionality

public:
	Modnsctx();
	Modnsctx(const adns_initflags flags);

	// synchronous, for now
	void modns_lookup(const char *owner);
	void modns_lookup(const std::string &s);

	// FIXME encode errno into this
	class ModnsException : std::exception {};

	// FIXME encode adns_status into this
	class ModnsLookupException : ModnsException {};

private:
	adns_state adns;

};

#endif
