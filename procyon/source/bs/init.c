#include <acm/gfx.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <zap/mem.h>

sig_atomic_t volatile acm_gotintr;

typeof (acm_dat) acm_dat;

static char * acm_getsavloc(void) {
	char const * const hmdir = getenv("HOME");
	if (hmdir == nullptr) {
		fprintf(stderr,"Unable to get home directory (HOME not set)\n");
		acm_exit(acm_stat_err);
	}
	char const * const savfilnm    = ".procyon-save";
	zap_sz       const hmdirlen    = zap_strlen(hmdir);
	zap_sz       const savfilnmlen = zap_strlen(savfilnm);
	zap_sz       const savloclen   = hmdirlen + 0x1u + savfilnmlen;
	char *             savloc      = malloc(savloclen + 0x1u);
	if (savloc == nullptr) {
		fprintf(stderr,"Unable allocate memory\n");
		acm_exit(acm_stat_err);
	}
	zap_memcp(hmdir,hmdirlen,savloc);
	savloc[hmdirlen] = '/';
	zap_memcp(savfilnm,savfilnmlen,savloc + hmdirlen + 0x1u);
	savloc[savloclen] = 0x0u;
	return savloc;
}

static void acm_intrhandl(int const _sig) {
	signal(_sig,acm_intrhandl); /* Ignore the return value. */
	acm_gotintr = 0x1;
}

void acm_init(void) {
	acm_gotintr       = 0x0;
	acm_dat.gfxisinit = false;
	acm_dat.win       = nullptr;
	acm_log("Initialising data\n");
	acm_dat.savloc = acm_getsavloc();
	acm_log("Initialising signal handlers\n");
	if (signal(SIGINT,acm_intrhandl) == SIG_ERR) {
		fprintf(stderr,"Unable to set SIGINT handler\n");
		acm_exit(acm_stat_err);
	}
	acm_initgfx();
}
