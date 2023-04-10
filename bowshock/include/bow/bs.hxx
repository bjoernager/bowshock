// Copyright 2022-2023 Gabriel Jensen.

#pragma once

// flux is retarded and uses compound literals - even for C++. We override this nonsense with some value initialisations.
#include <flux/io.h>
#undef flux_disc
#undef flux_keep
#define flux_disc (::flux_priv_disc {._disc = true,})
#define flux_keep (::flux_priv_disc {._disc = false,})
// Note: flux will recieve better (C++) support in the future.

#ifndef bow_datDir
#error Data directory not specified!
#endif

#include <cstdio>
#include <zap/bs.hh> // We guarantee that this header is included.

static_assert(::zap::bytelen == 0x8u,"Bytes must contain exactly eight bits.");

#define bow_logRaw(msg,...) fprintf(stderr,msg __VA_OPT__(,) __VA_ARGS__)

#define bow_log(msg,...) bow_logRaw("\x1B[1m%s\x1B[0m: " msg "\n",__func__ __VA_OPT__(,) __VA_ARGS__)

#define bow_logErr(msg,...) bow_log("\x1B[38;5;197m[ERROR]\x1B[0m " msg __VA_OPT__(,) __VA_ARGS__)

#if bow_dbg
#define bow_logDbg(msg,...) bow_log(msg __VA_OPT__ (,) __VA_ARGS__)
#else
#define bow_logDbg(msg,...) ((void)0x0u)
#endif

#define bow_logXyz(xyz) bow_logDbg("%s: %.03f    %.03f    %.03f",#xyz,(xyz).x,(xyz).y,(xyz).z)

#define bow_setStrLen(ptr,len,str) ((void)(ptr = str,len = sizeof (str) - 0x1u))

namespace bow { 
	constexpr bool dbg = bow_dbg;

	constexpr ::zap::sz cmdrNmLen = 0xEu;
	
	enum struct stat : ::zap::i8 {
		ok  = 0x0u,
		err = 0x1u,
	};

	enum struct objTyp : ::zap::i8 {
		can,     // canister
		pl,      // player
		ship,    // ship
		star,    // star
		station, // station
		wrld,    // world (planet/moon)
	};

	enum struct wrld : ::zap::i8 {
		amm, // ammonium world
		gas, // gas giant
		ice, // icy world
		rck, // rocky world
		lav, // lava world
		wat, // water world
	};

	enum struct ship : ::zap::i8 {
		aq,   // aquila
		cas,  // cassiopeia
		cent, // centaurus
		cov,  // corvus
		cur,  // cursor
		eri,  // eridanus
		fal,  // falco
		lyra, // lyra
		tau,  // taurus
		ursa, // ursa
		vip,  // vipera
		// Remember maxShipId in sav
	};

	enum struct star : ::zap::i8 {
		a, // main sequence
		b, // main sequence
		c, // carbon
		f, // main sequence
		g, // main sequence
		k, // main sequence
		l, // brown dwarf
		m, // main sequence
		n, // neutron star
		o, // main sequence
		s, // carbon
		t, // brown dwarf
		w, // worm hole
		x, // black hole
		y, // brown dwarf
		z, // white hole
	};

	enum struct station : ::zap::i8 {
		station_glob, // globus
		station_orb,  // orbis
	};

	struct xyz {
		double x;
		double y;
		double z;
	};

	struct obj {
		::bow::objTyp typ;
		union {
			::bow::wrld    wrldTyp;
			::bow::ship    shipTyp;
			::bow::star    starTyp;
			::bow::station stationTyp;
		};
		::bow::xyz    pos;    // astronomical units
		::bow::xyz    rot;    // radians
		::bow::xyz    posVel; // astronomical units per second
		::bow::xyz    rotVel; // radians per second
		double        mass;   // kilograms
		::bow::obj *  next;
	};

	struct objRoot {
		::bow::obj * objs;
	};

	struct plDat {
		char    nm[::bow::cmdrNmLen+0x1u];
		::zap::i04 tm;
		::zap::i04 sysId;
		::bow::obj ship;
		float   zoom;
	};

	constexpr ::zap::i04 verMaj = 0x0u;
	constexpr ::zap::i04 verMin = 0xBu;
	constexpr ::zap::i04 verPat = 0x0u;

	char const * objTypStr(::bow::objTyp typ) noexcept;

	::zap::i04 rnd() noexcept;
}
