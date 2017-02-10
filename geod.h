/* geod.h
 * created 2017-02-09
 */

#ifndef GEOD_H_INCLUDED
#define GEOD_H_INCLUDED

#include "glucat/glucat.h"
/* need the tuning.h file before glucat_imp.h
 * 
 * compare README file distributed with glucat
 * */
#include "tuning.h"
#include "glucat/glucat_imp.h"

typedef glucat::matrix_multi<double> clif;

class Geod{
	/* describes a geodesic in upper half space
	 * takes start and end as points in the boundary
	 * if start == end, it is of the form (a, infty)
	 * [so far take this as the default direction	           ]
	 * [an additional mechanism could be implemented to make   ]
	 * [the opposite direction possible. e.g.:                 ]
	 * [self.orientation = +/- 1                               ]
	 */
	public:
		clif start;
		clif end;
		Geod(clif a, clif b);
		bool check_one();
		clif get_intersection_with_s0();
		clif get_intersection(Geod g);
		friend std::ostream& operator<<(std::ostream& os, const Geod& g);
};

#endif // GEOD_H_INCLUDED
