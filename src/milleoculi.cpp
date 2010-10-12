#include <iostream>
#include <milleoculi.h>

Modnsctx::Modnsctx(){
	if(adns_init(&adns,adns_if_none,NULL)){
		throw ModnsException();
	}
}

Modnsctx::Modnsctx(const adns_initflags flags){
	if(adns_init(&adns,flags,NULL)){
		throw ModnsException();
	}
}

Modnsctx::~Modnsctx(){
	adns_finish(adns);
}

// minuend \min"u*end\, n. [L. minuendus to be diminished, fr. minuere to
// lessen, diminish. See {Minish}.] (Arith.) In the process of subtraction, the
// number from which another number (the subtrahend) is to be subtracted, to
// find the difference.
void timeval_subtract(struct timeval *elapsed,const struct timeval *minuend,
			const struct timeval *subtrahend){
	*elapsed = *minuend;
	if(elapsed->tv_usec < subtrahend->tv_usec){
		int nsec = (subtrahend->tv_usec - elapsed->tv_usec) / 100000 + 1;

		elapsed->tv_usec += 1000000 * nsec;
		elapsed->tv_sec -= nsec;
	}
	if(elapsed->tv_usec - subtrahend->tv_usec > 1000000){
		int nsec = (elapsed->tv_usec - subtrahend->tv_usec) / 1000000;

		elapsed->tv_usec -= 1000000 * nsec;
		elapsed->tv_sec += nsec;
	}
	elapsed->tv_sec -= subtrahend->tv_sec;
	elapsed->tv_usec -= subtrahend->tv_usec;
}

void Modnsctx::modns_lookup(const char *owner,struct timeval *res){
	adns_answer *answer = NULL;
	struct timeval tvp,tv;

	if(gettimeofday(&tv,NULL)){
		throw ModnsException();
	}
	if(adns_synchronous(adns,owner,adns_r_a,adns_qf_none,&answer)){
		throw ModnsLookupException();
	}
	if(gettimeofday(&tvp,NULL)){
		throw ModnsException();
	}
	// std::cerr << "ERROR " << answer->status << std::endl;
	if(answer->status > adns_s_max_localfail){
		throw ModnsLookupException();
	}else if(answer->status){
		throw ModnsException();
	}
	timeval_subtract(res,&tvp,&tv);
}

void Modnsctx::modns_lookup(const std::string &s,struct timeval *res){
	modns_lookup(s.c_str(),res);
}
