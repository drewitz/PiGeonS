#include "cpctclif.h"

CpctClif::CpctClif(int input) : clif(input){
	is_inf = false;
};

CpctClif::CpctClif(const char* input) : clif(input){
	is_inf = false;
};

CpctClif::CpctClif(const char* input, bool inf) : clif(input){
	is_inf = inf;
};

CpctClif::CpctClif(bool inf) : clif("0"){
	is_inf = inf;
};

CpctClif::CpctClif(clif cinput) : clif(cinput){
	is_inf = false;
};

CpctClif::CpctClif() : clif(){
	is_inf = false;
};

ostream& operator<<(ostream& os, const CpctClif& c){
	if(c.is_inf){
		os << "oo";
	} else {
		clif cc = c;
#ifdef PRETTYPRINT
		clif dest(0);
		for (int i = 0; i > - GENERATORS; i--){
			dest = dest + cc[{i}]*clif("{"+to_string(i)+"}");
		}
		cc = dest;
#endif // PRETTYPRINT
		os << cc;
	}
	return os;
}
