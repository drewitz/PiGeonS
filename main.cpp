/* tested with glucat-0.8.2     2017-01-20 */

#include "polygon.h"

using namespace std;

int main(int argc, char* argv[]){
	// invoke programme as
	// ./glugon q1 q2 ... q_p

	// initialise parameters
	vector<clif> s;
	s.reserve(argc-1);
	for(int i = 1; i < argc; i++){
		s.push_back(clif(argv[i]));
	}

	cout << "########## Calculate a " << s.size() + 3 << "-gon ##########"
	     << endl;
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
