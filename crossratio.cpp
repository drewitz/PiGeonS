/* file crossratio.cpp
 * created 2017-02-10
 */

#include "crossratio.h"

clif crossratio(CpctClif a, CpctClif b, CpctClif c, CpctClif d){
	clif aclif(a);
	clif bclif(b);
	clif cclif(c);
	clif dclif(d);

	if (a.is_inf){
		return (bclif-dclif) * (bclif-cclif).inv();
	}
	if (b.is_inf){
		return (aclif-cclif) * (aclif-dclif).inv();
	}
	if (c.is_inf){
		return (aclif-dclif).inv() * (bclif-dclif);
	}
	if (d.is_inf){
		return (aclif-cclif) * (bclif-cclif).inv();
	}
	return (aclif-cclif) * (aclif-dclif).inv() * (bclif-dclif) * (bclif-cclif).inv();
}
