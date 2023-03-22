#if !defined(bow_hdr_lgc)
#define bow_hdr_lgc

#include <bow/bs.h>

constexpr double bow_timemod = 0x1p-10; // time modifier

constexpr double bow_gravconst = 0x1p0 * bow_timemod; // gravitational constant

void bow_grav(bow_obj * obj,bow_obj const * par);
void bow_mv(  bow_obj * obj);

#endif
