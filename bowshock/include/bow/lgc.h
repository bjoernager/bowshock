#if !defined(bow_hdr_lgc)
#define bow_hdr_lgc

#include <bow/bs.h>

constexpr double bow_gravconst = 0x1.0p-2; // gravitational constant

void bow_grav(bow_obj * obj,bow_obj const * par);
void bow_mv(  bow_obj * obj);

#endif
