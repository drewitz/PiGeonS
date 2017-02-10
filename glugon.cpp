/* tested with glucat-0.8.2     2017-01-20 */

#include "pentagon.h"

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

	Pentagon p(q1, q2);
        

        std::cout << "geodesics of the pentagon:" << std::endl << p;

	std::cout << std::endl;
	p.check_intersections();
	std::cout << std::endl;
}
