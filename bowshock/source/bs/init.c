#define bow_sym "init"

#include <bow/gfx.h>
#include <bow/sav.h>

#include <flux.h>
#include <inttypes.h>
#include <stdlib.h>

bow_stat bow_loop(bow_playdat * playdat);

[[noreturn]] void bow_init(void) {
	char const * savpth;
	bow_playdat playdat;
	bow_rawlog("\x1B[0m\x1B[1mBowshock\x1B[0m %" PRIX64 " \u2013 Copyright 2022\u20102023, \x1B[1mGabriel Jensen\x1B[0m.\n\n",bow_ver);
	bow_log("initialising");
	bow_initdat(&playdat,&savpth);
	bow_initgfx();
	bow_loop(&playdat);
	bow_sav(savpth,&playdat);
	bow_quit(bow_stat_ok);
}

int main(void) {
	bow_init();
}
