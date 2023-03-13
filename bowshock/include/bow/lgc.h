#if !defined(bow_hdr_lgc)
#define bow_hdr_lgc

#include <bow/bs.h>

#define bow_dist(x,y,z) sqrt(pow(x,0x2.0p0)+pow(y,0x2.0p0)+pow(z,0x2.0p0))

constexpr double bow_gravconst = 0x1.0p0; // gravitational constant

void bow_grav(bow_obj * obj,bow_obj const * par);
void bow_mv(  bow_obj * obj);

#endif
