// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#define constexpr static const

#define _POSIX_C_SOURCE 200112l

#if __STDC_VERSION__ <= 201710
#error ISO/IEC 9899:2023 is required!
#endif

//#if __STDC_IEC_60559_BFP__ < 202311
//#error ISO/IEC 60559:2020 is required!
//#endif

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

#define bow_rawlog(msg,...) fprintf(stderr,msg __VA_OPT__(,) __VA_ARGS__)

#define bow_log(msg,...) bow_rawlog("\x1B[1m%s\x1B[0m: " msg "\n",__func__ __VA_OPT__(,) __VA_ARGS__)

#define bow_logerr(msg,...) bow_log("\x1B[38;5;197m[ERROR]\x1B[0m " msg __VA_OPT__(,) __VA_ARGS__)

#if bow_dbg
#define bow_dbglog(msg,...) bow_log(msg __VA_OPT__ (,) __VA_ARGS__)
#else
#define bow_dbglog(msg,...) ((void)0x0u)
#endif

#define bow_logxyz(xyz) bow_dbglog("%.03f    %.03f    %.03f",(xyz).x,(xyz).y,(xyz).z)

constexpr zap_i04 bow_vermaj = 0x0u;
constexpr zap_i04 bow_vermin = 0x8u;
constexpr zap_i04 bow_verpat = 0x1u;

#define bow_cmdrnmlen ((zap_sz)0xEu)

typedef enum {
	bow_stat_ok  = 0x0u,
	bow_stat_err = 0x1u,
} bow_stat;

typedef struct {
	double x;
	double y;
	double z;
} bow_xyz;

typedef struct bow_impl_obj bow_obj;

typedef struct bow_impl_objroot bow_objroot;

typedef struct bow_impl_playdat bow_playdat;

typedef struct bow_impl_gfxdat bow_gfxdat;

extern sig_atomic_t volatile bow_gotintr;

char const * bow_getsavpth(void);
bool         bow_getquot(  char const * * quot,char const * * src,zap_i8 id);

bow_stat bow_loop(bow_gfxdat * gfxdat,bow_playdat * playdat);

[[noreturn]] void bow_help(char const * prognm);

[[noreturn]] void bow_abrt(void);
[[noreturn]] void bow_quit(bow_gfxdat * gfxdat,bow_stat stat);
