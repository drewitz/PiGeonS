/* tested with glucat-0.8.2     2017-01-20 */

#include "pentagon.h"

using namespace std;

int main(){
	cout << "########## Calculate a Pentagon ##########" << endl
		  << "not very elaborately..." << endl
	          << endl;

	clif q1("1+{-1}");
	clif q2("1+{-2}");

	cout << "Using the parameters:" << endl
	     << "    q1 = " << q1 << endl
	     << "    q2 = " << q2 << endl
	     << endl;

	vector<clif> s {q1, q2};
	Pentagon p(s);
        

        cout << "geodesics of the pentagon:" << endl << p;

	cout << endl;
	p.check_intersections();
	cout << endl << endl;
	p.print_cross_ratios();
	cout << endl;
}
