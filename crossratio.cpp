/* file crossratio.cpp
 * created 2017-02-10
 */

clif crossratio(clif a, clif b, clif c, clif d){
        return (a-c) * (a-d).inv() * (b-d) * (b-c).inv();
}