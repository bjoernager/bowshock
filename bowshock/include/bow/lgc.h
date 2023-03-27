#pragma once

#include <bow/bs.h>

#include <zap/bs.h>

constexpr double bow_distmod = 0x1p0; // distance modifier
constexpr double bow_massmod = 0x1p0; // mass modifier
constexpr double bow_tmmod   = 0x1p0; // time modifier

constexpr double bow_gravconst = 0x1.2589EFFFp-34 * (bow_distmod*bow_distmod*bow_distmod)/(bow_massmod*bow_tmmod*bow_tmmod); // gravitational constant (s^2*m*t^2)

bow_obj * bow_addobj(  bow_objroot *       root,bow_obj const * obj);
void      bow_freeobjs(bow_objroot const * root);

void bow_grav(    bow_obj *           obj, bow_obj * par);
void bow_gravobjs(bow_objroot const * root);
void bow_mv(      bow_obj *           obj);
void bow_mvobjs(  bow_obj *           objs);
