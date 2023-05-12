// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.hxx>

#include <zp/mem>

auto ::bow::decsav(::bow::savdat & buf,::zp::i8 const * dat) noexcept -> void {
	auto const decVal = [&dat]<typename typ>(typ & buf) {
		dat = ::zp::memcpy(&buf,dat,sizeof (buf)).src;
	};

	decVal(buf.fmtVer);     // fmtver
	decVal(buf.cmdnam);     // cmdnam
	decVal(buf.tim);        // tim
	decVal(buf.sysidt);     // sysidt
	decVal(buf.shptyp);     // shptyp
	decVal(buf.shpposx);    // shpposx
	decVal(buf.shpposy);    // shpposy
	decVal(buf.shpposz);    // shpposz
	decVal(buf.shprotx);    // shprotx
	decVal(buf.shproty);    // shproty
	decVal(buf.shprotz);    // shprotz
	decVal(buf.shpposvelx); // shpposvelx
	decVal(buf.shpposvely); // shpposvely
	decVal(buf.shpposvelz); // shpposvelz
	decVal(buf.shprotvelx); // shprotvelx
	decVal(buf.shprotvely); // shprotvely
	decVal(buf.shprotvelz); // shprotvelz
}
