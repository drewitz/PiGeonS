/* tested with glucat-0.8.2     2017-01-20 */

#include "glucat/glucat.h"
/* need the tuning.h file before glucat_imp.h
 * 
 * compare README file distributed with glucat
 * */
#include "tuning.h"
#include "glucat/glucat_imp.h"

#include "ostream"
#include "cmath"

#define CHECK false

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
};

bool is_small(double x){
	/* this is pretty fucked up... */
	return abs(x) < 0.1;
}

Geod::Geod(clif a, clif b){
	start = a;
	end = b;
}

clif Geod::get_intersection_with_s0() {
	/* so far only intersection with -1,1 */
	clif direction;
	direction = end - start;
	int i;
	if(direction[-1] != 0){
		i = -1;
	} else {
		if(direction[-2] != 0){
			i = -2;
		} else {
			std::cout << std::endl
				  << "Noe geht nicht" << std::endl;
		}
	}

	double b;
	b = direction[i];

	double s;
	s = -start[i]/b;

	clif intersection;
	intersection = start + direction*clif(s);
	return intersection;
}

clif Geod::get_intersection(Geod g) {
	/* solve for intersection of self = (a,b) and g = (c, d)
	 * i.e. solve for t (or s) in
	 * 	a + t (b-a)  = c + s (d-c)
	 *
	 * i.e. solve the SLE
	 * [  |    |  ] [ t ]   [  |  ]
	 * [ b-a  c-d ] [   ] = [ c-a ]
	 * [  |    |  ] [ s ]   [  |  ]
	 */
	clif m1, m2, v;
	m1 = end - start;
	m2 = g.start - g.end;
	v  = g.start - start;
	/* so far only in 2 dimensions? */
	/* get 2x2 non-singular submatrix to be solved */
	bool found;
	found = false;
	int dimMax = -2;
	int i = 0;
	int j = -1;
	double a,b,c,d;
	while (j >= dimMax){
		//std::cout << std::endl << "i = " << i << "  and j = " << j << std::endl;
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
	if (not found) {std::cout << "wtf";}

	double t;
	t = (d * v[i] - b * v[j])/(a*d-b*c);

	return start + t*(end - start);
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
		std::cout << "check yourself ? " << start << " to " << end
			  << std::endl;
		return false;
	}
}

std::ostream& operator<<(std::ostream& os, const Geod& g){
	if(g.start == g.end){
		os << g.start << " -- infty";
	} else {
		os << g.start << " -- " << g.end;
	}
	return os;
}

clif my_sqrt(clif x){
        clif my_root;
        my_root = (x + glucat::abs(x));
        my_root /= sqrt(2*(x[0] + glucat::abs(x)));
        return my_root;
}

clif crossratio(clif a, clif b, clif c, clif d){
        return (a-c) * (a-d).inv() * (b-d) * (b-c).inv();
}

clif phi(clif q, clif x){
        /* Isometry phi_q of the form
         * x |---> sqrt(-q) * (1+x) * (1-x)^-1 * sqrt(-q)
         *
         *  -1 |---> 0
         *   1 |---> inf
         *   0 |---> -q
         * inf |--->  q
         */
        clif root;
        //root = glucat::sqrt(-q);
        root = my_sqrt(-q);

        /* check the sqrt with our definition */
        if(CHECK){
                clif my_root;
                my_root = (-q + glucat::abs(q)); 
                my_root /= sqrt(2*(-q[0] + glucat::abs(q)));

                std::cout << std::endl;
                std::cout << "### Check ---> "
                          << root << " == " << my_root << " ???" << std::endl;
                std::cout << std::endl;
        }

        clif one(1);
        return root * (one + x) * (one - x).inv() * root;
}

clif psi(clif d, clif x){
        /* Isometry psi of the form
         * x |---> .... * (1+x) * (1-x)^-1 * ....
         *
         *  -1 |---> 0
         *   1 |---> inf
         *   d |---> 1
         * 
         * This is needed to calculate the common perpendicular between
         * S0 = (-1, 1) and S{p-2} = (c, d)
         */

        clif d_prime;
        clif one(1);
        clif root;

        d_prime = (one + d) / (one - d);
        //root = glucat::sqrt(one / d_prime);
        root = my_sqrt(one / d_prime);

        if(CHECK){
                std::cout << std::endl;
                std::cout << "### Check ---> "
                          << root * (one + d) / (one  - d) * root
                          << " == " << 1 << " ???" << std::endl;
                std::cout << std::endl;
        }

        return root * ((one + x) * (one - x).inv()) * root;
}

clif psi_inv(clif d, clif y){
        /* inverse of x |--> psi(d,x) */
        clif d_prime;
        clif one(1);
        clif root;
        clif y_temp;

        d_prime = (one + d) / (one - d);
        //root = glucat::sqrt(d_prime);
        root = my_sqrt(d_prime);

        y_temp = root*y*root;
        std::cout << std::endl << y_temp << std::endl;

        return - (one + y_temp).inv() * (one - y_temp);
}

Geod get_last(Geod g){
	/* get the common perpendicular between (-1, 1) and g = (c, d) */
        clif temp, img_c;
        img_c = psi(g.end, g.start);
        temp = my_sqrt(img_c);

	if (CHECK) {
		std::cout << std::endl << "check crossratio:" << std::endl
			  << crossratio(1,img_c,-temp, temp) << std::endl;
	}

	return Geod(psi_inv(g.end, temp), psi_inv(g.end, -temp));
}

int main(){
	std::cout << "########## Calculate a Pentagon ##########" << std::endl
		  << "not very elaborately..." << std::endl
	          << std::endl;

	clif q1("1+{-1}");
	clif q2("1+{-2}");

	std::cout << "Using the parameters:" << std::endl
		  << "    q1 = " << q1 << std::endl
		  << "    q2 = " << q2 << std::endl
	          << std::endl;

        /* starting geodesics */
	Geod S0(-1,1);
	Geod S1(0,0); 

        /* first calculated geodesic */
	Geod S2(-q1, q1);

        /* second calculated geodesic */
	Geod S3(phi(q1,-q2), phi(q1, q2));

        /* now S4 is the common perpendicular to S0 and S3 */
	Geod S4 = get_last(S3);
        

        std::cout << "geodesics so far:" << std::endl
                  << "  S0 = " << S0 << std::endl
                  << "  S1 = " << S1 << std::endl
                  << "  S2 = " << S2 << std::endl
                  << "  S3 = " << S3 << std::endl
                  << "  S4 = " << S4 << std::endl
                  << "  --   orientation of S4 might be inverted" << std::endl;

	//std::cout << S4.check_one();
	std::cout << std::endl;
	std::cout << "This should not be roughly 0" << std::endl;
	std::cout << S4.get_intersection_with_s0();
	std::cout << std::endl;
	std::cout << "The following two lines should not be equal:" << std::endl;
	std::cout << S4.get_intersection(S3);
	std::cout << std::endl;
	std::cout << S3.get_intersection(S2);
	std::cout << std::endl;
}
