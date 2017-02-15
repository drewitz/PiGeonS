#ifndef CPCTCLIF_H_INCLUDED
#define CPCTCLIF_H_INCLUDED

#include "clif.h"
#include "iostream"
#include "string"

#define PRETTYPRINT

using namespace std;

class CpctClif: public clif {
	public:
		bool is_inf;

		CpctClif(int input);
		CpctClif(const char* input);
		CpctClif(const char* input, bool inf);
		CpctClif(bool inf);
		CpctClif(clif cinput);
		CpctClif();

		friend ostream& operator<<(ostream& os, const CpctClif& c);
};

#endif // CPCTCLIF_H_INCLUDED
