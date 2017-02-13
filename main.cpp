/* tested with glucat-0.8.2     2017-01-20 */

#include "polygon.h"

using namespace std;

int main(){
	cout << "########## Calculate a Pentagon ##########" << endl
	     << "not very elaborately..." << endl
	     << endl;

	// initialise parameters
	vector<clif> s {
		clif("2{-1}"),
		clif("2{-2}")
	};

	// print parameters
	cout << "Using the parameters:" << endl;
	int i = 0;
	for (clif q : s) {
		i++;
		cout << "    q" << i << " = " << q << endl;
	}
	cout << endl;

	// calculate polygon
	Polygon p(s);

	// print polygon
	cout << "geodesics of the polygon:" << endl << p;

	cout << endl;
	p.check_intersections();
	cout << endl << endl;
	p.print_cross_ratios();
	cout << endl;
}
