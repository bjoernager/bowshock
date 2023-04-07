// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/bs.h>

constexpr double bow_distMod = 0x1.16A5D2D360000000p037; // distance modifier (1 astronomical unit)
constexpr double bow_massMod = 0x1.91930A5E75F0C192p100; // mass modifier     (1 solar mass)
constexpr double bow_tmMod   = 0x1.0000000000000000p012; // time modifier     (1 second)

constexpr double bow_gravConstFac = (bow_massMod*(bow_tmMod*bow_tmMod))/((bow_distMod*bow_distMod*bow_distMod)); // inverse

constexpr double bow_gravConst = 0x1.258688101B4BB16Dp-34*bow_gravConstFac; // gravitational constant (s^2*m*t^2)

[[unsequenced]] double bow_shipMass(bow_ship id);

void bow_gravSys( bow_objRoot * sys);
void bow_gravObjs(bow_objRoot * objs,bow_objRoot const * sys);
void bow_mv(      bow_obj *     obj);
void bow_mvObjs(  bow_objRoot * root);

void bow_sim(bow_objRoot * sys,zap_i04 dur);
