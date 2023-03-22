#define bow_sym "sav"

#include <bow/sav.h>

#include <flux/io.h>
#include <zap/mem.h>

void bow_sav(char const * const pth,bow_playdat const * const playdatptr) {
	bow_log("saving commander %s at \"%s\"",playdatptr->nm,pth);
	flux_fil * fil;
	flux_err err = flux_mkfil(&fil,pth,0644);
	if (err != flux_err_ok) {
		if (err != flux_err_exist) {
			bow_logerr("unable to open save file \"%s\"",pth);
			bow_quit(bow_stat_err);
		}
		err = flux_op(&fil,pth,flux_md_wr,flux_disc);
		if (err != flux_err_ok) {
			bow_logerr("unable to create save file \"%s\"",pth);
			bow_quit(bow_stat_err);
		}
	}
	bow_playdat playdat;
	zap_cp(&playdat,playdatptr,sizeof (playdat));
	bow_savdat dat = {
		.fmtver  = bow_savfmtver,
		.sysid   = playdat.sysid,
		.tm      = playdat.tm,
		.shiptyp = playdat.ship.shiptyp,
		.shippos = playdat.ship.pos,
		.shiprot = playdat.ship.rot,
		.shipvel = playdat.ship.vel,
	};
	zap_cp(dat.cmdrnm,playdat.nm,bow_cmdrnmlen);
	flux_wr(fil,&dat,sizeof (dat));
	flux_cl(fil);
}
