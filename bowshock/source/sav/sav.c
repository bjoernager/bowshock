#define bow_sym "sav"

#include <bow/sav.h>

#include <flux/io.h>
#include <zap/mem.h>

static void bow_encsav(zap_i8 * buf,bow_playdat const * const playdat) {
	buf = zap_cp(buf,(zap_i04[0x1u]) {bow_savver},0x8u).dest;          // fmtver
	buf = zap_cp(buf,playdat->nm,                 bow_cmdrnmlen).dest; // cmdrnm
	buf = zap_cp(buf,&playdat->tm,                0x8u).dest;          // tm
	buf = zap_cp(buf,&playdat->sysid,             0x8u).dest;          // sysid
	buf = zap_cp(buf,&playdat->ship.shiptyp,      0x1u).dest;          // shiptyp
	buf = zap_cp(buf,&playdat->ship.pos.x,        0x8u).dest;          // shipposx
	buf = zap_cp(buf,&playdat->ship.pos.y,        0x8u).dest;          // shipposy
	buf = zap_cp(buf,&playdat->ship.pos.z,        0x8u).dest;          // shipposz
	buf = zap_cp(buf,&playdat->ship.rot.x,        0x8u).dest;          // shiprotx
	buf = zap_cp(buf,&playdat->ship.rot.y,        0x8u).dest;          // shiproty
	buf = zap_cp(buf,&playdat->ship.rot.z,        0x8u).dest;          // shiprotz
	buf = zap_cp(buf,&playdat->ship.posvel.x,     0x8u).dest;          // shipposvelx
	buf = zap_cp(buf,&playdat->ship.posvel.y,     0x8u).dest;          // shipposvely
	buf = zap_cp(buf,&playdat->ship.posvel.z,     0x8u).dest;          // shipposvelz
	buf = zap_cp(buf,&playdat->ship.rotvel.x,     0x8u).dest;          // shiprotvelx
	buf = zap_cp(buf,&playdat->ship.rotvel.y,     0x8u).dest;          // shiprotvely
	      zap_cp(buf,&playdat->ship.rotvel.z,     0x8u);               // shiprotvelz
}

void bow_sav(char const * const pth,bow_playdat const * const playdat) {
	bow_log("saving commander %s at \"%s\"",playdat->nm,pth);
	flux_fil * fil;
	flux_err err = flux_mkfil(&fil,pth,0644);
	if (err) {
		if (err != flux_err_exist) {
			bow_logerr("unable to open save file \"%s\"",pth);
			bow_quit(bow_stat_err);
		}
		err = flux_op(&fil,pth,flux_md_wr,flux_disc);
		if (err) {
			bow_logerr("unable to create save file \"%s\"",pth);
			bow_quit(bow_stat_err);
		}
	}
	zap_i8 dat[bow_savlen];
	bow_encsav(dat,playdat);
	flux_wr(fil,dat,bow_savlen);
	flux_cl(fil);
}
