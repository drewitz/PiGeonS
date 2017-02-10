/* file crossratio.h
 * created 2017-02-10
 *
 * defines cross ratio of 4 clifford numbers
 * maybe further helper functions in the future?
 */

#ifndef CROSSRATIO_H_INCLUDED
#define CROSSRATIO_H_INCLUDED

#include "glucat/glucat.h"
/* need the tuning.h file before glucat_imp.h
 * 
 * compare README file distributed with glucat
 * */
#include "tuning.h"
#include "glucat/glucat_imp.h"

typedef glucat::matrix_multi<double> clif;

clif crossratio(clif a, clif b, clif c, clif d);

#endif // CROSSRATIO_H_INCLUDED
