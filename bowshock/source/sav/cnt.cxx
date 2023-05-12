// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.hxx>

#include <cinttypes>
#include <ly/io>
#include <zp/mem>

auto ::bow::cnt(::bow::plydat & plydat,char const * const pth) noexcept -> void {
	bow_log("loading save file at \"%s\"",pth);

	::ly::fil fil;

	::ly::err err = fil.opn(pth,::ly::mod::red,::ly::kep);
	
	if (err != ::ly::err::ok) [[unlikely]] {
		bow_logerr("unable to open save file \"%s\"",pth);
		
		return ::bow::newsav(plydat);
	}

	::zp::i8 rawDat[::bow::savlen];
	err = fil.red(rawDat,::bow::savlen);
	
	if (err != ::ly::err::ok) [[unlikely]] {
		fil.cls();
		
		if (err == ::ly::err::eof) bow_logerr("corrupt save file at \"%s\"",pth);
		else                       bow_logerr("unable to read file at \"%s\"",pth);
		
		return ::bow::newsav(plydat);
	}
	
	fil.cls();
	
	::bow::savdat dat;
	
	::bow::decsav(dat,rawDat);
	
	if (dat.fmtVer != ::bow::savver) [[unlikely]] {
		bow_logerr("invalid format (%" PRIX64 ") of save file at \"%s\"",dat.fmtVer,pth);
		
		return ::bow::newsav(plydat);
	}
	if (dat.shptyp > ::bow::maxshpid) [[unlikely]] {
		bow_logerr("invalid shp type (%" PRIX8 ")",dat.shptyp);
		
		return ::bow::newsav(plydat);
	}

	plydat = ::bow::plydat {
		.tim            = dat.tim,
		.sysidt         = dat.sysidt,
		.shp          = {
			.shptyp = (::bow::shp)dat.shptyp,
			.pos     = {
				.x   = dat.shpposx,
				.y   = dat.shpposy,
				.z   = dat.shpposz,
			},
			.rot     = {
				.x   = dat.shprotx,
				.y   = dat.shproty,
				.z   = dat.shprotz,
			},
			.posVel  = {
				.x   = dat.shpposvelx,
				.y   = dat.shpposvely,
				.z   = dat.shpposvelz,
			},
			.rotVel  = {
				.x   = dat.shprotvelx,
				.y   = dat.shprotvely,
				.z   = dat.shprotvelz,
			},
		},
	};
	::zp::cpy(plydat.nam,dat.cmdnam,::bow::cmdnamlen);
	plydat.nam[::bow::cmdnamlen] = '\x00';
	
	::bow::gendat(plydat);

	bow_log("welcome back, commander %s",plydat.nam);
}
