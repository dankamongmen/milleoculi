#ifndef MILLEOCULI
#define MILLEOCULI

// We use the asynchronous DNS resolver library of Ian Jackson et al.
#include <adns.h>
#include <stdexcept>
#include <sys/time.h> // SVR4 / 4.3BSD / POSIX.1, fair enough

class Modnsctx { // Wraps C-ADNS, providing C++/timing functionality

public:
	// Hide at least the naming, if not the actual details, of the
	// backing implementation...
	typedef adns_initflags modns_initflags;

	Modnsctx();
	Modnsctx(const modns_initflags flags);

	~Modnsctx();

	// synchronous, for now
	void modns_lookup(const char *owner,struct timeval *);
	void modns_lookup(const std::string &s,struct timeval *);

	// FIXME encode errno into this
	class ModnsException : std::exception {};

	// FIXME encode adns_status into this
	class ModnsLookupException : ModnsException {};

private:
	adns_state adns;

};

#endif
