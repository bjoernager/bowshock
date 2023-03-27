#pragma once

#define constexpr static const

#define _POSIX_C_SOURCE 200112l

#if __STDC_VERSION__ <= 201710
#error ISO/IEC 9899:2023 is required!
#endif

//#if __STDC_IEC_60559_BFP__ < 202311
//#error ISO/IEC 60559:2020 is required!
//#endif

#pragma STDC FP_CONTRACT ON

#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <zap/bs.h>

static_assert(CHAR_BIT == 0x8,"Bytes must contain exactly eight bits.");

static_assert(sizeof (zap_i01) == 0x2u);
static_assert(sizeof (zap_i02) == 0x4u);
static_assert(sizeof (zap_i04) == 0x8u);

static_assert(sizeof (float)  == 0x4u);
static_assert(sizeof (double) == 0x8u);

#if !defined(bow_sym)
#error symbol not defined
#endif

#define bow_rawlog(msg,...) fprintf(stderr,msg __VA_OPT__(,) __VA_ARGS__)

#define bow_log(msg,...) bow_rawlog("\x1B[1m%s\x1B[0m: " msg "\n",bow_sym __VA_OPT__(,) __VA_ARGS__)

#define bow_logerr(msg,...) bow_log("\x1B[38;5;197m[ERROR]\x1B[0m " msg __VA_OPT__(,) __VA_ARGS__)

#if bow_dbg
#define bow_dbglog(msg,...) bow_log(msg __VA_OPT__ (,) __VA_ARGS__)

#define bow_logxyz(xyz) bow_rawlog("x: %f\ny: %f\nz: %f\n\n",xyz.x,xyz.y,xyz.z)
#else
#define bow_dbglog(msg,...) ((void)0x0u)

#define bow_logxyz(xyz) ((void)0x0u)
#endif

constexpr zap_i04 bow_vermaj = 0x0u;
constexpr zap_i04 bow_vermin = 0x7u;

#define bow_cmdrnmlen ((zap_sz)0xEu)

typedef enum {
	bow_stat_ok  = 0x0u,
	bow_stat_err = 0x1u,
} bow_stat;

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

typedef struct {
	double x;
	double y;
	double z;
} bow_xyz;

typedef struct bow_priv_obj bow_obj;

struct bow_priv_obj {
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

typedef struct {
	bow_obj * objs;
} bow_objroot;

typedef struct {
	char    nm[bow_cmdrnmlen+0x1u];
	zap_i04 tm;
	zap_i04 sysid;
	bow_obj ship;
} bow_playdat;

extern sig_atomic_t volatile bow_gotintr;

void bow_gendat( bow_playdat * playdat);
void bow_initdat(bow_playdat * playdat,char const * * savpth);

[[noreturn]] void bow_quit(bow_stat stat);
