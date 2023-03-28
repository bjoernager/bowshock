// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/bs.h>

#include <zap/bs.h>

typedef enum {
	bow_objtyp_can,     // canister
	bow_objtyp_play,    // player
	bow_objtyp_sat,     // satellite (moon)
	bow_objtyp_ship,    // ship
	bow_objtyp_star,    // star
	bow_objtyp_station, // station
	bow_objtyp_wrld,    // world (planet)
} bow_objtyp;

typedef enum {
	bow_wrld_amm, // ammonium world
	bow_wrld_gas, // gas giant
	bow_wrld_ice, // icy world
	bow_wrld_rck, // rocky world
	bow_wrld_lav, // lava world
	bow_wrld_wat, // water world
} bow_wrld;

typedef enum {
	bow_ship_aq,   // aquila
	bow_ship_cas,  // cassiopeia
	bow_ship_cent, // centaurus
	bow_ship_eri,  // eridanus
	bow_ship_lyra, // lyra
	bow_ship_tau,  // taurus
	bow_ship_ursa, // ursa
} bow_ship;

typedef enum {
	bow_star_a, // main sequence
	bow_star_b, // main sequence
	bow_star_c, // carbon
	bow_star_f, // main sequence
	bow_star_g, // main sequence
	bow_star_k, // main sequence
	bow_star_l, // brown dwarf
	bow_star_m, // main sequence
	bow_star_n, // neutron star
	bow_star_o, // main sequence
	bow_star_s, // carbon
	bow_star_t, // brown dwarf
	bow_star_w, // worm hole
	bow_star_x, // black hole
	bow_star_y, // brown dwarf
	bow_star_z, // white hole
} bow_star;

typedef enum {
	bow_station_cor, // coriolis
} bow_station;

struct bow_impl_obj {
	bow_objtyp typ;
	bow_xyz    pos;
	bow_xyz    rot; // radians
	bow_xyz    posvel;
	bow_xyz    rotvel;
	double     mass;
	union {
		bow_wrld    wrldtyp;
		bow_ship    shiptyp;
		bow_star    startyp;
		bow_station stationtyp;
	};
	bow_obj *  next;
};

struct bow_impl_objroot {
	bow_obj * objs;
};

struct bow_impl_playdat {
	char    nm[bow_cmdrnmlen+0x1u];
	zap_i04 tm;
	zap_i04 sysid;
	bow_obj ship;
};

constexpr double bow_tmmod = 0x1p-14; // time modifier

constexpr double bow_gravconst = 0x1.2589EFFFp-34/(bow_tmmod*bow_tmmod); // gravitational constant (s^2*m*t^2)

bow_obj * bow_addobj(  bow_objroot *       root,bow_obj const * obj);
void      bow_freeobjs(bow_objroot const * root);

void bow_grav(    bow_obj *           obj, bow_obj * par);
void bow_gravobjs(bow_objroot const * root);
void bow_mv(      bow_obj *           obj);
void bow_mvobjs(  bow_obj *           objs);
