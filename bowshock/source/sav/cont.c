// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.h>

#include <flux/io.h>
#include <inttypes.h>
#include <zap/mem.h>

void bow_cont(bow_plDat * const pldatptr,char const * const pth) {
	bow_log("loading save file at \"%s\"",pth);

	flux_fil * fil;
	flux_err err = flux_op(&fil,pth,flux_md_rd,flux_keep);
	
	unlikely (err) {
		bow_logErr("unable to open save file \"%s\"",pth);
		goto new;
	}

	zap_i8 rawdat[bow_savLen];
	err = flux_rd(rawdat,fil,bow_savLen,nullptr);
	
	unlikely (err) {
		flux_cl(fil);
		
		if (err == flux_err_eof) bow_logErr("corrupt save file at \"%s\"",pth);
		else bow_logErr("unable to read file at \"%s\"",pth);
		
		goto new;
	}
	
	flux_cl(fil);
	
	bow_savDat dat;
	
	bow_decSav(&dat,rawdat);
	
	unlikely (dat.fmtVer != bow_savVer) {
		bow_logErr("invalid format (%" PRIX64 " of save file at \"%s\"",dat.fmtVer,pth);
		
		goto new;
	}
	unlikely (dat.shipTyp > bow_maxShipId) {
		bow_logErr("invalid ship type (%" PRIX8 ")",dat.shipTyp);
		
		goto new;
	}

	bow_plDat pldat = {
		.tm            = dat.tm,
		.sysId         = dat.sysId,
		.ship.shipTyp  = (bow_ship)dat.shipTyp,
		.ship.pos.x    = dat.shipPosX,
		.ship.pos.y    = dat.shipPosY,
		.ship.pos.z    = dat.shipPosZ,
		.ship.rot.x    = dat.shipRotX,
		.ship.rot.y    = dat.shipRotY,
		.ship.rot.z    = dat.shipRotZ,
		.ship.posVel.x = dat.shipPosVelX,
		.ship.posVel.y = dat.shipPosVelY,
		.ship.posVel.z = dat.shipPosVelZ,
		.ship.rotVel.x = dat.shipRotVelX,
		.ship.rotVel.y = dat.shipRotVelY,
		.ship.rotVel.z = dat.shipRotVelZ,
	};
	zap_cp(pldat.nm,dat.cmdrNm,bow_cmdrNmLen);
	pldat.nm[bow_cmdrNmLen] = '\x00';
	
	bow_log("welcome back, commander %s",pldat.nm);
	
	bow_genDat(&pldat);
	
	zap_cp(pldatptr,&pldat,sizeof (pldat));
	
	return;

new:
	bow_new(pldatptr);
}
