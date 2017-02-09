/* tested with glucat-0.8.2     2017-01-20 */

#include "geod.cpp"

#include "cmath"

#define CHECK false

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
