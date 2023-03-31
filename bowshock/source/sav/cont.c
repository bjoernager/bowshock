// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>
#include <bow/sav.h>

#include <flux/io.h>
#include <inttypes.h>
#include <zap/mem.h>

static void bow_decsav(bow_savdat * buf,zap_i8 * dat) {
	dat = zap_cp(&buf->fmtver,     dat,0x8u).src;
	dat = zap_cp(&buf->cmdrnm,     dat,bow_cmdrnmlen).src;
	dat = zap_cp(&buf->tm,         dat,0x8u).src;
	dat = zap_cp(&buf->sysid,      dat,0x8u).src;
	dat = zap_cp(&buf->shiptyp,    dat,0x1u).src;
	dat = zap_cp(&buf->shipposx,   dat,0x8u).src;
	dat = zap_cp(&buf->shipposy,   dat,0x8u).src;
	dat = zap_cp(&buf->shipposz,   dat,0x8u).src;
	dat = zap_cp(&buf->shiprotx,   dat,0x8u).src;
	dat = zap_cp(&buf->shiproty,   dat,0x8u).src;
	dat = zap_cp(&buf->shiprotz,   dat,0x8u).src;
	dat = zap_cp(&buf->shipposvelx,dat,0x8u).src;
	dat = zap_cp(&buf->shipposvely,dat,0x8u).src;
	dat = zap_cp(&buf->shipposvelz,dat,0x8u).src;
	dat = zap_cp(&buf->shiprotvelx,dat,0x8u).src;
	dat = zap_cp(&buf->shiprotvely,dat,0x8u).src;
	dat = zap_cp(&buf->shiprotvelz,dat,0x8u).src;
}

void bow_cont(bow_playdat * const playdatptr,char const * const pth) {
	bow_log("loading save file at \"%s\"",pth);
	flux_fil * fil;
	flux_err err = flux_op(&fil,pth,flux_md_rd,flux_keep);
	if (err) {
		bow_logerr("unable to open save file \"%s\"",pth);
		goto new;
	}
	zap_i8 rawdat[bow_savlen];
	err = flux_rd(rawdat,fil,bow_savlen,nullptr);
	if (err) {
		flux_cl(fil);
		if (err == flux_err_eof) bow_logerr("corrupt save file at \"%s\"",pth);
		else bow_logerr("unable to read file at \"%s\"",pth);
		goto new;
	}
	flux_cl(fil);
	bow_savdat dat;
	bow_decsav(&dat,rawdat);
	if (dat.fmtver != bow_savver) {
		bow_logerr("invalid format (%" PRIX64 " of save file at \"%s\"",dat.fmtver,pth);
		goto new;
	}
	if (dat.shiptyp > (zap_i8)bow_ship_ursa) {
		bow_logerr("invalid ship type (%" PRIX8 ")",dat.shiptyp);
		goto new;
	}
	bow_playdat playdat = {
		.tm            = dat.tm,
		.sysid         = dat.sysid,
		.ship.shiptyp  = (bow_ship)dat.shiptyp,
		.ship.pos.x    = dat.shipposx,
		.ship.pos.y    = dat.shipposy,
		.ship.pos.z    = dat.shipposz,
		.ship.rot.x    = dat.shiprotx,
		.ship.rot.y    = dat.shiproty,
		.ship.rot.z    = dat.shiprotz,
		.ship.posvel.x = dat.shipposvelx,
		.ship.posvel.y = dat.shipposvely,
		.ship.posvel.z = dat.shipposvelz,
		.ship.rotvel.x = dat.shiprotvelx,
		.ship.rotvel.y = dat.shiprotvely,
		.ship.rotvel.z = dat.shiprotvelz,
	};
	zap_cp(playdat.nm,dat.cmdrnm,bow_cmdrnmlen);
	playdat.nm[bow_cmdrnmlen] = '\x0';
	bow_log("welcome back, commander %s",playdat.nm);
	bow_gendat(&playdat);
	zap_cp(playdatptr,&playdat,sizeof (playdat));
	return;
new:
	bow_rstart(playdatptr);
}
