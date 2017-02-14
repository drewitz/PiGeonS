/* file crossratio.cpp
 * created 2017-02-10
 */

#include "crossratio.h"

clif crossratio(clif a, clif b, clif c, clif d){
	if (a.is_inf){
		return (b-d) * (b-c).inv();
	}
	if (b.is_inf){
		return (a-c) * (a-d).inv();
	}
	if (c.is_inf){
		return (a-d).inv() * (b-d);
	}
	if (d.is_inf){
		return (a-c) * (b-c).inv();
	}
	return (a-c) * (a-d).inv() * (b-d) * (b-c).inv();
}
