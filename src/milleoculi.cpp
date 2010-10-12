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

void Modnsctx::modns_lookup(const char *owner){
	adns_answer *answer = NULL;

	if(adns_synchronous(adns,owner,adns_r_a,adns_qf_none,&answer)){
		throw ModnsLookupException();
	}
	// std::cerr << "ERROR " << answer->status << std::endl;
	if(answer->status > adns_s_max_localfail){
		throw ModnsLookupException();
	}else if(answer->status){
		throw ModnsException();
	}
}

void Modnsctx::modns_lookup(const std::string &s){
	modns_lookup(s.c_str());
}
