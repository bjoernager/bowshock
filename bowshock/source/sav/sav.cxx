// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.hxx>
#include <bow/sav.hxx>

#include <flux/io.h>
#include <zap/mem.hh>

void ::bow::sav(char const * const pth,::bow::plDat const & plDat) noexcept {
	bow_log("saving commander %s at \"%s\"",plDat.nm,pth);
	
	::flux_fil * fil;
	::flux_err err = ::flux_mkfil(&fil,pth,0644);
	
	if (err) [[unlikely]] {
		if (err != ::flux_err_exist) [[unlikely]] {
			bow_logErr("unable to open save file \"%s\"",pth);
			::bow::abrt();
		}
	
		err = ::flux_op(&fil,pth,::flux_md_wr,flux_disc);
		if (err) [[unlikely]] {
			bow_logErr("unable to create save file \"%s\"",pth);
			::bow::abrt();
		}
	}
	
	::zap::i8 dat[::bow::savLen];

	::bow::savDat savDat = {
		.fmtVer      = ::bow::savVer,
		.tm          = plDat.tm,
		.sysId       = plDat.sysId,
		.shipTyp     = static_cast<::zap::i8>(plDat.ship.shipTyp),
		.shipPosX    = plDat.ship.pos.x,
		.shipPosY    = plDat.ship.pos.y,
		.shipPosZ    = plDat.ship.pos.z,
		.shipRotX    = plDat.ship.rot.x,
		.shipRotY    = plDat.ship.rot.y,
		.shipRotZ    = plDat.ship.rot.z,
		.shipPosVelX = plDat.ship.posVel.x,
		.shipPosVelY = plDat.ship.posVel.y,
		.shipPosVelZ = plDat.ship.posVel.z,
		.shipRotVelX = plDat.ship.rotVel.x,
		.shipRotVelY = plDat.ship.rotVel.y,
		.shipRotVelZ = plDat.ship.rotVel.z,
	};
	::zap::cp(savDat.cmdrNm,plDat.nm,sizeof (savDat.cmdrNm));

	::bow::encSav(dat,savDat);
	
	::flux_wr(fil,dat,::bow::savLen);
	::flux_cl(fil);
}
