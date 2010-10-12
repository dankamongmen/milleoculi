#include <iostream>
#include <milleoculi.h>

Modnsctx::Modnsctx(){
	if(adns_init(&adns,adns_if_none,NULL)){
		throw ModnsctxException();
	}
}

Modnsctx::Modnsctx(const adns_initflags flags){
	if(adns_init(&adns,flags,NULL)){
		throw ModnsctxException();
	}
}

void Modnsctx::modns_lookup(const char *owner){
	// FIXME perform lookup!
	std::cerr << "FIXME " << owner << std::endl;
	throw ModnsctxException();
}

void Modnsctx::modns_lookup(const std::string &s){
	modns_lookup(s.c_str());
}
