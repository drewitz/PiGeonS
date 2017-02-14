#include "cpctclif.h"

CpctClif::CpctClif(const char* input) : clif(input){
	is_inf = false;
};

CpctClif::CpctClif(const char* input, bool inf) : clif(input){
	is_inf = inf;
};

CpctClif::CpctClif(bool inf) : clif("0"){
	is_inf = inf;
};

CpctClif::CpctClif() : clif(){
	is_inf = false;
};

ostream& operator<<(ostream& os, const CpctClif& c){
	if(c.is_inf){
		os << "oo";
	} else {
		const clif& cc = c;
		os << cc;
	}
	return os;
}
