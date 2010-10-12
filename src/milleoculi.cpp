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
