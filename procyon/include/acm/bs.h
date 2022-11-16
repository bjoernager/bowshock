#if !defined(acm_hdr_bs)
#define acm_hdr_bs

#include <GLFW/glfw3.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <zap/bs.h>

#define acm_ver    ((uint_least64_t)+0x1)
#define acm_savver ((uint_least64_t)+0x1)

#define acm_plnmlen ((zap_sz)+0x10u)

#define acm_dflplnm ("Jameson\x0\x0\x0\x0\x0\x0\x0\x0")

#if defined(acm_dbg)
#define acm_log(...) (acm_dbglog(__VA_ARGS__))
#else
#define acm_log(...) ((void)0x0u)
#endif

typedef enum {
	acm_drv_h1,
	acm_drv_h2,
	acm_drv_h3,
	acm_drv_h4,
	acm_drv_h5,
	acm_drv_h6,
	acm_drv_h7,
	acm_drv_h8,
	acm_drv_m1,
	acm_drv_m2,
	acm_drv_m3,
	acm_drv_m4,
} acm_drv;

typedef enum {
	acm_shipid_add,
	acm_shipid_ana,
	acm_shipid_asp,
	acm_shipid_boa,
	acm_shipid_cob,
	acm_shipid_con,
	acm_shipid_cou,
	acm_shipid_cyg,
	acm_shipid_dov,
	acm_shipid_eag,
	acm_shipid_falc,
	acm_shipid_fer,
	acm_shipid_frei,
	acm_shipid_geck,
	acm_shipid_haul,
	acm_shipid_hawk,
	acm_shipid_keel,
	acm_shipid_kes,
	acm_shipid_krait,
	acm_shipid_lift,
	acm_shipid_lion,
	acm_shipid_mamba,
	acm_shipid_moray,
	acm_shipid_osp,
	acm_shipid_pan,
	acm_shipid_puma,
	acm_shipid_py,
	acm_shipid_shut,
	acm_shipid_side,
	acm_shipid_tran,
	acm_shipid_vip,
	acm_shipid_vult,
} acm_shipid;

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
	acm_drv    drv;
	acm_shipid id;
} acm_ship;

typedef struct {
	char           nm[acm_plnmlen + 0x1u];
	uint_least16_t heat;
	acm_objpos     pos;
	uint_least64_t selsys;
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

             void acm_dbglog(char const *      fmt,...);
             void acm_init(  void);
[[noreturn]] void acm_exit(  acm_stat          stat);

#endif
