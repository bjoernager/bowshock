// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.hxx>
#include <bow/sav.hxx>

#include <ly/io>
#include <zp/mem>

auto ::bow::sav(char const * const pth,::bow::plydat const & plydat) noexcept -> void {
	bow_log("saving commander %s at \"%s\"",plydat.nam,pth);
	
	::ly::fil fil;
	::ly::err err = fil.crt(pth,0644u);
	
	if (err != ::ly::err::ok) [[unlikely]] {
		bow_logerr("unable to open save file \"%s\"",pth);
		::bow::abr();
	}
	
	::zp::i8 dat[::bow::savlen];

	::bow::savdat savdat = {
		.fmtVer     = ::bow::savver,
		.tim        = plydat.tim,
		.sysidt     = plydat.sysidt,
		.shptyp     = static_cast<::zp::i8>(plydat.shp.shptyp),
		.shpposx    = plydat.shp.pos.x,
		.shpposy    = plydat.shp.pos.y,
		.shpposz    = plydat.shp.pos.z,
		.shprotx    = plydat.shp.rot.x,
		.shproty    = plydat.shp.rot.y,
		.shprotz    = plydat.shp.rot.z,
		.shpposvelx = plydat.shp.posVel.x,
		.shpposvely = plydat.shp.posVel.y,
		.shpposvelz = plydat.shp.posVel.z,
		.shprotvelx = plydat.shp.rotVel.x,
		.shprotvely = plydat.shp.rotVel.y,
		.shprotvelz = plydat.shp.rotVel.z,
	};
	::zp::cpy(savdat.cmdnam,plydat.nam,sizeof (savdat.cmdnam));

	::bow::encsav(dat,savdat);
	
	fil.wrt(dat,::bow::savlen);
	fil.cls();
}
