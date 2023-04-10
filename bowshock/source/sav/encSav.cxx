// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.hxx>

#include <zap/mem.hh>

void ::bow::encSav(::zap::i8 * buf,::bow::savDat const & dat) noexcept {
	auto const encVal = [&buf]<typename typ>(typ const & val) {
		buf = ::zap::bytecp(buf,&val,sizeof (val)).dest;
	};

	encVal(dat.fmtVer);      // fmtver
	encVal(dat.cmdrNm);      // cmdrnm
	encVal(dat.tm);          // tm
	encVal(dat.sysId);       // sysid
	encVal(dat.shipTyp);     // shiptyp
	encVal(dat.shipPosX);    // shipposx
	encVal(dat.shipPosY);    // shipposy
	encVal(dat.shipPosZ);    // shipposz
	encVal(dat.shipRotX);    // shiprotx
	encVal(dat.shipRotY);    // shiproty
	encVal(dat.shipRotZ);    // shiprotz
	encVal(dat.shipPosVelX); // shipposelx
	encVal(dat.shipPosVelY); // shipposely
	encVal(dat.shipPosVelZ); // shipposelz
	encVal(dat.shipRotVelX); // shiprotelx
	encVal(dat.shipRotVelY); // shiprotely
	encVal(dat.shipRotVelZ); // shiprotelz
}
