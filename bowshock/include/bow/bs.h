// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#ifdef bow_c2xCompat
#include <bow/c2x.h>
#endif

#ifndef bow_datDir
#error Data directory not specified!
#endif

#if defined(__GNUC__) || defined(__clang__)
#define likely(  expr) if (__builtin_expect((bool)(expr),true))
#define unlikely(expr) if (__builtin_expect((bool)(expr),false))
#else
#define likely(  expr) if ((expr))
#define unlikely(expr) if ((expr))
#endif

#if defined(__clang__)
#define assume(expr) ((void)__builtin_assume((expr)))
#elifdef (_MSC_VER)
#define assume(expr) ((void)__assume((expr)))
#else
#define assume(expr) ((void)0x0u)
#endif

#include <stdio.h>
#include <zap/bs.h> // This header is guaranteed to be included.

static_assert(zap_bytelen == 0x8u,"Bytes must contain exactly eight bits.");

static_assert(sizeof (zap_i8)  == 0x1u);
static_assert(sizeof (zap_i01) == 0x2u);
static_assert(sizeof (zap_i02) == 0x4u);
static_assert(sizeof (zap_i04) == 0x8u);

static_assert(sizeof (float)  == 0x4u);
static_assert(sizeof (double) == 0x8u);

#define bow_rawlog(msg,...) fprintf(stderr,msg __VA_OPT__(,) __VA_ARGS__)

#define bow_log(msg,...) bow_rawlog("\x1B[1m%s\x1B[0m: " msg "\n",__func__ __VA_OPT__(,) __VA_ARGS__)

#define bow_logErr(msg,...) bow_log("\x1B[38;5;197m[ERROR]\x1B[0m " msg __VA_OPT__(,) __VA_ARGS__)

#ifdef bow_dbg
#define bow_dbgLog(msg,...) bow_log(msg __VA_OPT__ (,) __VA_ARGS__)
#else
#define bow_dbgLog(msg,...) ((void)0x0u)
#endif

#define bow_logXyz(xyz) bow_dbgLog("%.03f    %.03f    %.03f",(xyz).x,(xyz).y,(xyz).z)

#define bow_setStrLen(ptr,len,str) ((void)(ptr = str,len = sizeof (str) - 0x1u))

#define bow_cmdrNmLen ((zap_sz)0xEu)

typedef enum : zap_i8 {
	bow_stat_ok  = 0x0u,
	bow_stat_err = 0x1u,
} bow_stat;

typedef struct {
	double x;
	double y;
	double z;
} bow_xyz;

typedef enum : zap_i8 {
	bow_objTyp_can,     // canister
	bow_objTyp_pl,      // player
	bow_objTyp_ship,    // ship
	bow_objTyp_star,    // star
	bow_objTyp_station, // station
	bow_objTyp_wrld,    // world (planet/moon)
} bow_objTyp;

typedef enum : zap_i8 {
	bow_wrld_amm, // ammonium world
	bow_wrld_gas, // gas giant
	bow_wrld_ice, // icy world
	bow_wrld_rck, // rocky world
	bow_wrld_lav, // lava world
	bow_wrld_wat, // water world
} bow_wrld;

typedef enum : zap_i8 {
	bow_ship_aq,   // aquila
	bow_ship_cas,  // cassiopeia
	bow_ship_cent, // centaurus
	bow_ship_cov,  // corvus
	bow_ship_cur,  // cursor
	bow_ship_eri,  // eridanus
	bow_ship_fal,  // falco
	bow_ship_lyra, // lyra
	bow_ship_tau,  // taurus
	bow_ship_ursa, // ursa
	bow_ship_vip,  // vipera
	// Remember bow_maxShipId
} bow_ship;

typedef enum : zap_i8 {
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

typedef enum : zap_i8 {
	bow_station_glob, // globus
	bow_station_orb,  // orbis
} bow_station;

typedef struct bow_implObj bow_obj;

struct bow_implObj {
	bow_objTyp typ;
	bow_xyz    pos;    // astronomical units
	bow_xyz    rot;    // radians
	bow_xyz    posVel; // astronomical units per second
	bow_xyz    rotVel; // radians per second
	double     mass;   // kilograms
	union {
		bow_wrld    wrldTyp;
		bow_ship    shipTyp;
		bow_star    starTyp;
		bow_station stationTyp;
	};
	bow_obj *  next;
};

typedef struct {
	bow_obj * objs;
} bow_objRoot;

typedef struct {
	char    nm[bow_cmdrNmLen+0x1u];
	zap_i04 tm;
	zap_i04 sysId;
	bow_obj ship;
	float   zoom;
} bow_plDat;

constexpr zap_i04 bow_verMaj = 0x0u;
constexpr zap_i04 bow_verMin = 0xAu;
constexpr zap_i04 bow_verPat = 0x0u;

char const * bow_objTypStr(bow_objTyp typ);

zap_i04 bow_rnd(void);
