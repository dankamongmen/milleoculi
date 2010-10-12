#include <ios>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <milleoculi.h>

typedef struct result { // suitable for a linked list
	char *arec;
	uintmax_t looktime;
	struct result *next;
} result;

static result *
create_result(const std::string &arec,const uintmax_t rtime){
	result *r;

	if( (r = (result *)malloc(sizeof(*r))) ){
		if((r->arec = strdup(arec.c_str())) == NULL){
			free(r);
			return NULL;
		}
		r->looktime = rtime;
	}
	return r;
}

static void
destroy_list(result **r){
	result *tmp;

	while( (tmp = *r) ){
		*r = tmp->next;
		free(tmp->arec);
		free(tmp);
	}
}

static void
sort_into_list(result **list,result *r){
	while(*list){
		if(r->looktime < (*list)->looktime){
			break;
		}
		list = &(*list)->next;
	}
	r->next = *list;
	*list = r;
}

static void
dump_list(const result *r){
	int i = 0;

	while(r){
		std::cout << r->arec << ": " << r->looktime << "us" << std::endl;
		r = r->next;
		++i;
	}
	std::cout << "Sorted " << i << " result" << (i == 1 ? "." : "s.") << std::endl;
}

// FIXME can leak on failure -- bad form, but doesn't matter inside main()
int main(void){
	result *list = NULL;
	std::string req;
	Modnsctx ctx;

	std::cout << "Performing lookups (one per line, ^D to end)..." << std::endl;
	while(getline(std::cin,req)){
		struct timeval tv;
		uintmax_t rtime;
		result *r;

		try{
			std::cout << "Lookup: [" << req << "]...";
			ctx.modns_lookup(req,&tv);
		}catch(Modnsctx::ModnsLookupException &e){ // non-fatal
			std::cerr << "RESOLUTION FAILURE" << std::endl;
			continue;
		}
		rtime = (intmax_t)tv.tv_sec * 1000000 + tv.tv_usec;
		if((r = create_result(req,rtime)) == NULL){
			destroy_list(&list);
			return EXIT_FAILURE;
		}
		std::cout << rtime << std::endl;
		sort_into_list(&list,r);
	}
	dump_list(list);
	destroy_list(&list);
	return EXIT_SUCCESS;
}
