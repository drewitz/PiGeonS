/* clif.h
 * created 2017-02-13
 *
 * just for importing glucat in the same manner for every file
 */

#ifndef CLIF_H_INCLUDED
#define CLIF_H_INCLUDED

#include "glucat/glucat.h"
/* need the tuning.h file before glucat_imp.h
 * 
 * compare README file distributed with glucat
 * */
#include "tuning.h"
#include "glucat/glucat_imp.h"

// number of generators
#define GENERATORS 4

typedef glucat::framed_multi<double,-GENERATORS,3> clif;

#endif // CLIF_H_INCLUDED
