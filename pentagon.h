/* file: pentagon.h
 * created: 2017-02-10
 */

#ifndef PENTAGON_H_INCLUDED
#define PENTAGON_H_INCLUDED

#include "geod.h"

#include "vector"

using namespace std;

class Pentagon{
	public:
		// adapt for general number of dimensions...
		int n_sides; // number of sides

		vector<Geod> sides; // vector of sides
		Pentagon(vector<clif> s);
		void check_intersections();

		// friends
		friend clif my_sqrt(clif x);
		friend clif crossratio(clif a, clif b, clif c, clif d);
		friend clif phi(clif q, clif x);
		friend clif psi(clif d, clif x);
		friend clif psi_inv(clif d, clif y);
		friend Geod get_last(Geod g);
		friend ostream& operator<<(ostream& os, const Pentagon& p);
};

#endif // PENTAGON_H_INCLUDED
