#if !defined(acm_hdr_bs)
#define acm_hdr_bs

#include <GLFW/glfw3.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <zap/bs.h>

#define acm_ver    ((uint_least64_t)+0x0)
#define acm_savver ((uint_least64_t)+0x0)

#define acm_plnmlen ((zap_sz)+0x10u)

#define acm_dflplnm ("Jameson\x0\x0\x0\x0\x0\x0\x0\x0")

#if defined(acm_dbg)
#define acm_log(...) (acm_dbglog(__VA_ARGS__))
#else
#define acm_log(...) ((void)0x0u)
#endif

typedef enum {
	acm_ship_add,
	acm_ship_ana,
	acm_ship_asp,
	acm_ship_boa,
	acm_ship_cob,
	acm_ship_con,
	acm_ship_cou,
	acm_ship_cyg,
	acm_ship_dov,
	acm_ship_eag,
	acm_ship_falc,
	acm_ship_fer,
	acm_ship_frei,
	acm_ship_geck,
	acm_ship_haul,
	acm_ship_hawk,
	acm_ship_keel,
	acm_ship_kes,
	acm_ship_krait,
	acm_ship_lift,
	acm_ship_lion,
	acm_ship_mamba,
	acm_ship_moray,
	acm_ship_osp,
	acm_ship_pan,
	acm_ship_puma,
	acm_ship_py,
	acm_ship_shut,
	acm_ship_side,
	acm_ship_tran,
	acm_ship_vip,
	acm_ship_vult,
} acm_ship;

typedef enum {
	acm_stat_err,
	acm_stat_ok,
} acm_stat;

typedef struct {
	uint_least64_t rx; /* Rotation data */
	uint_least64_t ry;
	uint_least64_t rz;
	uint_least64_t px; /* Position data */
	uint_least64_t py;
	uint_least64_t pz;
	uint_least64_t vx; /* Velocity data */
	uint_least64_t vy;
	uint_least64_t vz;
} acm_objpos;

typedef struct {
	acm_objpos pos;
} acm_obj;

typedef struct {
	char           nm[acm_plnmlen + 0x1u];
	uint_least16_t heat;
	acm_objpos     pos;
	acm_ship       ship;
	uint_least64_t tm;
} acm_pldat;

extern struct {
	bool         gfxisinit;
	acm_pldat    pldat;
	char const * savloc;
	GLFWwindow * win;
} acm_dat;

extern sig_atomic_t volatile acm_gotintr;

             void         acm_cont(  acm_pldat *       pldat);
             void         acm_dbglog(char const *      fmt,...);
             void         acm_init(  void);
[[noreturn]] void         acm_exit(  acm_stat          stat);
             void         acm_sav(   acm_pldat const * pldat);
             char const * acm_shipnm(acm_ship          ship);

#endif
