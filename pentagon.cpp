#include "pentagon.h"
#include "crossratio.h"

#include "cmath"
#include "iostream"

#define CHECK false

using namespace std;

clif my_sqrt(clif x){
        clif my_root;
        my_root = (x + glucat::abs(x));
        my_root /= sqrt(2*(x[0] + glucat::abs(x)));
        return my_root;
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

                cout << endl;
                cout << "### Check ---> "
                     << root << " == " << my_root << " ???" << endl;
                cout << endl;
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
                cout << endl;
                cout << "### Check ---> "
                     << root * (one + d) / (one  - d) * root
                     << " == " << 1 << " ???" << endl;
                cout << endl;
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
	// root isn't necessarily in the same subalgebra... raise issue?
        //root = glucat::sqrt(d_prime);
        root = my_sqrt(d_prime);

        y_temp = root*y*root;

        return - (one + y_temp).inv() * (one - y_temp);
}

Geod get_last(Geod g){
	/* get the common perpendicular between (-1, 1) and g = (c, d) */
        clif temp, img_c;
        img_c = psi(g.end, g.start);
        temp = my_sqrt(img_c);

	if (CHECK) {
		cout << endl << "check crossratio:" << endl
		     << crossratio(1,img_c,-temp, temp) << endl;
	}

	return Geod(psi_inv(g.end, temp), psi_inv(g.end, -temp));
}

Pentagon::Pentagon(vector<clif> s){
	/* "metadata-stuff" */
	n_sides = s.size() + 3;
	sides.reserve(n_sides);

        /* starting geodesics */
	sides.push_back(Geod(-1,1));
	sides.push_back(Geod(0,0)); 

        /* first calculated geodesic */
	sides.push_back(Geod(-s[0], s[0]));

        /* second calculated geodesic */
	sides.push_back(Geod(phi(s[0],-s[1]), phi(s[0], s[1])));

        /* now S4 is the common perpendicular to S0 and S3 */
	sides.push_back(get_last(sides.back()));
}

ostream& operator<<(ostream& os, const Pentagon& p){
	int i = -1;
	for (Geod g : p.sides) {
		i++;
		os << " S" << i << " = " << g << endl;
	}
	os << "  --   orientation of S" << i << " might be inverted" << endl;
	return os;
}

void Pentagon::check_intersections(){
	Geod S0, S_third_last, S_second_last, S_last;
	S0 = sides.at(0);
	S_third_last = sides.at(n_sides-3);
	S_second_last = sides.at(n_sides-2);
	S_last = sides.back();
	cout << "This should not be roughly 0" << endl;
	cout << S_last.get_intersection_with_s0();
	cout << endl;
	cout << "The following two lines should not be equal:" << endl;
	cout << S_last.get_intersection(S_second_last);
	cout << endl;
	cout << S_second_last.get_intersection(S_third_last);
}
