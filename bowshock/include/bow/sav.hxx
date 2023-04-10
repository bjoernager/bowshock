// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/bs.hxx>

namespace bow {
	constexpr ::zap::i04 savVer = 0x6u;

	constexpr ::zap::sz savLen = 0x79u+::bow::cmdrNmLen; 

	constexpr ::zap::i8 maxShipId = static_cast<::zap::i8>(::bow::ship::vip);

	/*
		Save format:

		offset: id:         size [bytes]: format:

		0x00    fmtver      8             unsigned
		0x08    cmdrnm      E             UTF-8
		0x16    tm          8             unsigned
		0x1E    sysid       8             unsigned
		0x1F    shiptyp     1             unsigned
		0x27    shipposx    8             binary64
		0x2F    shipposy    8             binary64
		0x37    shipposz    8             binary64
		0x3F    shiprotx    8             binary64
		0x47    shiproty    8             binary64
		0x4F    shiprotz    8             binary64
		0x57    shipposvelx 8             binary64
		0x5F    shipposvely 8             binary64
		0x67    shipposvelz 8             binary64
		0x6F    shiprotvelx 8             binary64
		0x77    shiprotvely 8             binary64
		0x7F    shiprotvelz 8             binary64
	*/

	struct savDat {
		::zap::i04 fmtVer;
		char       cmdrNm[::bow::cmdrNmLen];
		::zap::i04 tm;
		::zap::i04 sysId;
		::zap::i8  shipTyp;
		double     shipPosX;
		double     shipPosY;
		double     shipPosZ;
		double     shipRotX;
		double     shipRotY;
		double     shipRotZ;
		double     shipPosVelX;
		double     shipPosVelY;
		double     shipPosVelZ;
		double     shipRotVelX;
		double     shipRotVelY;
		double     shipRotVelZ;
	};

	void decSav(::bow::savDat & buf,::zap::i8 const *     dat) noexcept;
	void encSav(::zap::i8 *     buf,::bow::savDat const & dat) noexcept;

	void newSav(::bow::plDat & dat) noexcept;

	void cont(  ::bow::plDat & dat,char const * fil) noexcept;
	void genDat(::bow::plDat & dat)                  noexcept;

	void sav(char const * fil,::bow::plDat const & dat) noexcept;
}
