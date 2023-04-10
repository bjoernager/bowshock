// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.hxx>

#include <zap/mem.hh>

void ::bow::decSav(::bow::savDat & buf,::zap::i8 const * dat) noexcept {
	auto const decVal = [&dat]<typename typ>(typ & buf) {
		dat = ::zap::bytecp(&buf,dat,sizeof (buf)).src;
	};

	decVal(buf.fmtVer);      // fmtver
	decVal(buf.cmdrNm);      // cmdrnm
	decVal(buf.tm);          // tm
	decVal(buf.sysId);       // sysId
	decVal(buf.shipTyp);     // shipTyp
	decVal(buf.shipPosX);    // shipposx
	decVal(buf.shipPosY);    // shipposy
	decVal(buf.shipPosZ);    // shipposz
	decVal(buf.shipRotX);    // shiprotx
	decVal(buf.shipRotY);    // shiproty
	decVal(buf.shipRotZ);    // shiprotz
	decVal(buf.shipPosVelX); // shipposVelx
	decVal(buf.shipPosVelY); // shipposVely
	decVal(buf.shipPosVelZ); // shipposVelz
	decVal(buf.shipRotVelX); // shiprotVelx
	decVal(buf.shipRotVelY); // shiprotVely
	decVal(buf.shipRotVelZ); // shiprotVelz
}
