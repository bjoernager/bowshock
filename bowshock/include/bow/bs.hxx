// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#ifndef bow_datdir
#error Data directory not specified!
#endif

#include <cstdio>
#include <zp/bs> // We guarantee that this header is included.

static_assert(::zp::bytelen == 0x8u,"Bytes must contain exactly eight bits.");

#define bow_lograw(msg,...) fprintf(stderr,msg __VA_OPT__(,) __VA_ARGS__)

#define bow_log(msg,...) bow_lograw("\x1B[1m%s\x1B[0m: " msg "\n",__func__ __VA_OPT__(,) __VA_ARGS__)

#define bow_logerr(msg,...) bow_log("\x1B[38;5;197m[ERROR]\x1B[0m " msg __VA_OPT__(,) __VA_ARGS__)

#if bow_dbg
#define bow_logdbg(msg,...) bow_log(msg __VA_OPT__ (,) __VA_ARGS__)
#else
#define bow_logdbg(msg,...) ((void)0x0u)
#endif

#define bow_logxyz(xyz) bow_logdbg("%s: %.03f    %.03f    %.03f",#xyz,(xyz).x,(xyz).y,(xyz).z)

#define bow_setstrlen(ptr,len,str) ((void)(ptr = str,len = sizeof (str)-0x1u))

namespace bow { 
	constexpr ::zp::i04 vermaj = 0x0u;
	constexpr ::zp::i04 vermin = 0xCu;
	constexpr ::zp::i04 verpat = 0x0u;

	constexpr auto dbg = bow_dbg;

	constexpr ::zp::siz cmdnamlen = 0xEu;

	enum struct cnd : ::zp::i8 {
		err, // error
		oky, // okay
	};

	enum struct objtyp : ::zp::i8 {
		can, // canister
		ply, // player
		shp, // ship
		tar, // star
		stn, // station
		wrl, // world (planet/moon)
	};

	enum struct wrl : ::zp::i8 {
		amm, // ammonium world
		gas, // gas giant
		ice, // icy world
		rck, // rocky world
		lav, // lava world
		wat, // water world
	};

	enum struct shp : ::zp::i8 {
		aqu, // aquila
		cas, // cassiopeia
		cen, // centaurus
		cov, // corvus
		cur, // cursor
		eri, // eridanus
		fal, // falco
		lyr, // lyra
		tau, // taurus
		urs, // ursa
		vip, // vipera
		// Remember maxshpid in sav
	};

	enum struct tar : ::zp::i8 {
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

	enum struct stn : ::zp::i8 {
		stn_glb, // globus
		stn_orb, // orbis
	};

	struct xyz {
		double x;
		double y;
		double z;
	};

	struct obj {
		::bow::objtyp typ;
		union {
			::bow::wrl wrldTyp;
			::bow::shp shptyp;
			::bow::tar tartyp;
			::bow::stn stnTyp;
		};
		::bow::xyz   pos;    // astronomical units
		::bow::xyz   rot;    // radians
		::bow::xyz   posVel; // astronomical units per second
		::bow::xyz   rotVel; // radians per second
		double       mas;    // kilograms
		::bow::obj * nxt;
	};

	struct objroot {
		::bow::obj * objs;
	};

	struct pldat {
		char       nam[::bow::cmdnamlen+0x1u];
		::zp::i04  tim;
		::zp::i04  sysidt;
		::bow::obj shp;
		float      zom;
	};

	auto objtypstr(::bow::objtyp typ) noexcept -> char const *;

	auto rnd() noexcept -> ::zp::i04;
}
