#define bow_sym "sav"

#include <bow/sav.h>

#include <flux/io.h>
#include <zap/mem.h>

void bow_cont(char const * const pth,bow_playdat * const playdatptr) {
	bow_log("loading save file at \"%s\"",pth);
	flux_fil * fil;
	flux_err err = flux_op(&fil,pth,flux_md_rd,flux_keep);
	if (err != flux_err_ok) {
		bow_logerr("unable to open save file \"%s\"",pth);
		goto new;
	}
	bow_savdat dat;
	err = flux_rd(&dat,fil,sizeof (dat),nullptr);
	if (err != flux_err_ok) {
		flux_cl(fil);
		if (err == flux_err_eof) {
			bow_logerr("corrupt save file at \"%s\"",pth);
		}
		else bow_logerr("unable to read file at \"%s\"",pth);
		goto new;
	}
	flux_cl(fil);
	if (dat.fmtver != bow_savfmtver) {
		bow_logerr("invalid format of save file at \"%s\"",pth);
		goto new;
	}
	bow_playdat playdat = {
		.sysid    = dat.sysid,
		.tm       = dat.tm,
		.ship.pos = dat.shippos,
		.ship.rot = dat.shiprot,
		.ship.vel = dat.shipvel,
	};
	zap_cp(playdat.nm,dat.cmdrnm,bow_cmdrnmlen);
	playdat.nm[bow_cmdrnmlen] = '\x0';
	bow_log("welcome back commander %s",playdat.nm);
	goto ret;
new:
	playdat = (bow_playdat) {
		.nm    = "Caelum\x0\x0\x0\x0\x0\x0\x0\x0\x0",
		.sysid = 0x0u,
		.tm    = 0x1E187E00000u, // 256 julian years after the Unix Epoch.
		.ship  = {
			.pos     = {
				.x = 0x0.0p0,
				.y = 0x0.0p0,
				.z = 0x0.0p0,
			},
			.vel     = {
				.x = 0x0.0p0,
				.y = 0x0.0p0,
				.z = 0x0.0p0,
			},
			.shiptyp = bow_ship_aq,
		},
	};
	bow_log("generated commander %s",playdat.nm);
ret:
	zap_cp(playdatptr,&playdat,sizeof (playdat));
}
