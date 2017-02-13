/* geod.h
 * created 2017-02-09
 */

#ifndef GEOD_H_INCLUDED
#define GEOD_H_INCLUDED

#include "clif.h"

using namespace std;

class Geod{
	/* describes a geodesic in upper half space
	 * takes start and end as points in the boundary
	 * if start == end, it is of the form (a, infty)
	 * [so far take this as the default direction              ]
	 * [an additional mechanism could be implemented to make   ]
	 * [the opposite direction possible. e.g.:                 ]
	 * [self.orientation = +/- 1                               ]
	 * TODO you should really implement the infty properly...
	 */
	public:
		clif start;
		clif end;
		Geod(); // needed to create array of geodesics
		Geod(clif a, clif b);
		bool check_one();
		clif get_intersection_with_s0();
		clif get_intersection(Geod g);
		clif double_bridge_cross_ratio(Geod a, Geod b);

		friend ostream& operator<<(ostream& os, const Geod& g);
};

#endif // GEOD_H_INCLUDED
