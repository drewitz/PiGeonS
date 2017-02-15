/* geod.cpp
 * created 2017-02-09
 */

#include "geod.h"
#include "crossratio.h"

#include "iostream"

using namespace std;

bool is_small(double x){
	/* this is pretty fucked up... */
	return abs(x) < 0.1;
}

Geod::Geod(){}

Geod::Geod(CpctClif a, CpctClif b){
	start = a;
	end = b;
}

clif Geod::get_intersection_with_s0() {
	/* so far only intersection with -1,1 */
	if (start.is_inf or end.is_inf){
		// TODO check whether there is an intersection
		cout << "NEEDS TO BE PROPERLY IMPLEMENTED!!!" << endl
		     << "IT'S PROBABLY 0" << endl << endl;
		return clif(0);
	}
	clif direction;
	direction = clif(end) - clif(start);
	int i;
	if(direction[-1] != 0){
		i = -1;
	} else {
		if(direction[-2] != 0){
			i = -2;
		} else {
			cout << endl
			     << "Noe geht nicht" << endl;
		}
	}

	double b;
	b = direction[i];

	double s;
	s = -start[i]/b;

	clif intersection;
	intersection = clif(start) + direction*clif(s);
	return intersection;
}

clif Geod::get_intersection(Geod g) {
	/* solve for intersection of self = (a,b) and g = (c, d)
	 * i.e. solve for t (or s) in
	 *      a + t (b-a)  = c + s (d-c)
	 *
	 * i.e. solve the SLE
	 * [  |    |  ] [ t ]   [  |  ]
	 * [ b-a  c-d ] [   ] = [ c-a ]
	 * [  |    |  ] [ s ]   [  |  ]
	 */
	// TODO check for infinity...
	clif ga(g.start);
	clif gb(g.end);
	clif startclif(start);
	clif endclif(end);

	clif m1, m2, v;
	m1 = endclif - startclif;
	m2 = ga - gb;
	v  = ga - startclif;
	/* so far only in 2 dimensions? */
	/* get 2x2 non-singular submatrix to be solved */
	bool found;
	found = false;
	int dimMax = -2;
	int i = 0;
	int j = -1;
	double a,b,c,d;
	while (j >= dimMax){
		//cout << endl << "i = " << i << "  and j = " << j << endl;
		/* matrix as
		 * [ a  b ]
		 * [ c  d ]
		 */
		a = m1[i];
		b = m2[i];
		c = m1[j];
		d = m2[j];
		if (not is_small(a*d - b*c)){
			found = true;
			break;
		}

		i--;
		if ( i == j){
			i = 0;
			j--;
		}
	};
	if (not found) {cout << "wtf";}

	double t;
	t = (d * v[i] - b * v[j])/(a*d-b*c);

	return startclif + t*(endclif - startclif);
}

bool Geod::check_one() {
	/* checks whether this geodesic goes through the
	 * intersection of (-1, 1) and (0, inf)
	 */

	if(start == end) {
		return true;
	}
	if(start == 0 | end == 0) {
		return false;
	}
	clif temp;
	temp = start / end;
	if(temp == temp[0]) {
		return temp[0] < 0 ;
	} else {
		cout << "check yourself ? " << start << " to " << end
		     << endl;
		return false;
	}
}

ostream& operator<<(ostream& os, const Geod& g){
	os << g.start << " -- " << g.end;
	return os;
}

clif Geod::double_bridge_cross_ratio(Geod a, Geod b){
	/* calculates the cross ratio of the double bridge
	 * a, self, b
	 */
	// TODO CHECKTHIS!!!
	// TODO take care of infinity...
	return crossratio(end, start, a.end, b.end);
}
