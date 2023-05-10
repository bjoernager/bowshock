// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.hxx>

#include <zp/mem>

auto ::bow::encsav(::zp::i8 * buf,::bow::savdat const & dat) noexcept -> void {
	auto const encVal = [&buf]<typename typ>(typ const & val) {
		buf = ::zp::memcpy(buf,&val,sizeof (val)).dst;
	};

	encVal(dat.fmtVer);     // fmtver
	encVal(dat.cmdnam);     // cmdnam
	encVal(dat.tim);        // tim
	encVal(dat.sysidt);     // sysidt
	encVal(dat.shptyp);     // shptyp
	encVal(dat.shpposx);    // shpposx
	encVal(dat.shpposy);    // shpposy
	encVal(dat.shpposz);    // shpposz
	encVal(dat.shprotx);    // shprotx
	encVal(dat.shproty);    // shproty
	encVal(dat.shprotz);    // shprotz
	encVal(dat.shpposvelx); // shpposelx
	encVal(dat.shpposvely); // shpposely
	encVal(dat.shpposvelz); // shpposelz
	encVal(dat.shprotvelx); // shprotelx
	encVal(dat.shprotvely); // shprotely
	encVal(dat.shprotvelz); // shprotelz
}
