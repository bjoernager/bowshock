// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.hxx>
#include <bow/sav.hxx>

#include <ly/io>
#include <zp/mem>

auto ::bow::sav(char const * const pth,::bow::pldat const & pldat) noexcept -> void {
	bow_log("saving commander %s at \"%s\"",pldat.nam,pth);
	
	::ly::fil fil;
	::ly::err err = fil.crt(pth,0644u);
	
	if (err != ::ly::err::ok) [[unlikely]] {
		bow_logerr("unable to open save file \"%s\"",pth);
		::bow::abr();
	}
	
	::zp::i8 dat[::bow::savlen];

	::bow::savdat savdat = {
		.fmtVer      = ::bow::savver,
		.tim          = pldat.tim,
		.sysidt       = pldat.sysidt,
		.shptyp     = static_cast<::zp::i8>(pldat.shp.shptyp),
		.shpposx    = pldat.shp.pos.x,
		.shpposy    = pldat.shp.pos.y,
		.shpposz    = pldat.shp.pos.z,
		.shprotx    = pldat.shp.rot.x,
		.shproty    = pldat.shp.rot.y,
		.shprotz    = pldat.shp.rot.z,
		.shpposvelx = pldat.shp.posVel.x,
		.shpposvely = pldat.shp.posVel.y,
		.shpposvelz = pldat.shp.posVel.z,
		.shprotvelx = pldat.shp.rotVel.x,
		.shprotvely = pldat.shp.rotVel.y,
		.shprotvelz = pldat.shp.rotVel.z,
	};
	::zp::cpy(savdat.cmdnam,pldat.nam,sizeof (savdat.cmdnam));

	::bow::encsav(dat,savdat);
	
	fil.wrt(dat,::bow::savlen);
	fil.cls();
}
