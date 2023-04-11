// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.hxx>

#include <cinttypes>
#include <flux/io.hh>
#include <zap/mem.hh>

void ::bow::cont(::bow::plDat & plDat,char const * const pth) noexcept {
	bow_log("loading save file at \"%s\"",pth);

	::flux::fil fil;

	::flux::err err = fil.op(pth,::flux::md::rd,::flux::keep);
	
	if (err != ::flux::err::ok) [[unlikely]] {
		bow_logErr("unable to open save file \"%s\"",pth);
		
		return ::bow::newSav(plDat);
	}

	::zap::i8 rawDat[::bow::savLen];
	err = fil.rd(rawDat,::bow::savLen);
	
	if (err != ::flux::err::ok) [[unlikely]] {
		fil.cl();
		
		if (err == ::flux::err::eof) bow_logErr("corrupt save file at \"%s\"",pth);
		else                         bow_logErr("unable to read file at \"%s\"",pth);
		
		return ::bow::newSav(plDat);
	}
	
	fil.cl();
	
	::bow::savDat dat;
	
	::bow::decSav(dat,rawDat);
	
	if (dat.fmtVer != ::bow::savVer) [[unlikely]] {
		bow_logErr("invalid format (%" PRIX64 ") of save file at \"%s\"",dat.fmtVer,pth);
		
		return ::bow::newSav(plDat);
	}
	if (dat.shipTyp > ::bow::maxShipId) [[unlikely]] {
		bow_logErr("invalid ship type (%" PRIX8 ")",dat.shipTyp);
		
		return ::bow::newSav(plDat);
	}

	plDat = ::bow::plDat {
		.tm            = dat.tm,
		.sysId         = dat.sysId,
		.ship          = {
			.shipTyp = (::bow::ship)dat.shipTyp,
			.pos     = {
				.x   = dat.shipPosX,
				.y   = dat.shipPosY,
				.z   = dat.shipPosZ,
			},
			.rot     = {
				.x   = dat.shipRotX,
				.y   = dat.shipRotY,
				.z   = dat.shipRotZ,
			},
			.posVel  = {
				.x   = dat.shipPosVelX,
				.y   = dat.shipPosVelY,
				.z   = dat.shipPosVelZ,
			},
			.rotVel  = {
				.x   = dat.shipRotVelX,
				.y   = dat.shipRotVelY,
				.z   = dat.shipRotVelZ,
			},
		},
	};
	::zap::cp(plDat.nm,dat.cmdrNm,::bow::cmdrNmLen);
	plDat.nm[::bow::cmdrNmLen] = '\x00';
	
	::bow::genDat(plDat);

	bow_log("welcome back, commander %s",plDat.nm);
}
