// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/bs.h>

#define bow_savLen ((zap_sz)((zap_sz)0x79u+(zap_sz)bow_cmdrNmLen))

constexpr zap_i04 bow_savVer = 0x6u;

constexpr zap_i8 bow_maxShipId = bow_ship_vip;

/*
	Save format:

	id:         size [bytes]: format:
	fmtver      8             unsigned
	cmdrnm      E             UTF-8
	tm          8             unsigned
	sysid       8             unsigned
	shiptyp     1             unsigned
	shipposx    8             binary64
	shipposy    8             binary64
	shipposz    8             binary64
	shiprotx    8             binary64
	shiproty    8             binary64
	shiprotz    8             binary64
	shipposvelx 8             binary64
	shipposvely 8             binary64
	shipposvelz 8             binary64
	shiprotvelx 8             binary64
	shiprotvely 8             binary64
	shiprotvelz 8             binary64
*/

typedef struct {
	zap_i04 fmtVer;
	char    cmdrNm[bow_cmdrNmLen];
	zap_i04 tm;
	zap_i04 sysId;
	zap_i8  shipTyp;
	double  shipPosX;
	double  shipPosY;
	double  shipPosZ;
	double  shipRotX;
	double  shipRotY;
	double  shipRotZ;
	double  shipPosVelX;
	double  shipPosVelY;
	double  shipPosVelZ;
	double  shipRotVelX;
	double  shipRotVelY;
	double  shipRotVelZ;
} bow_savDat;

void bow_decSav(bow_savDat * buf,zap_i8 const *    dat);
void bow_encSav(zap_i8 *     buf,bow_plDat const * dat);

void bow_new(bow_plDat * dat);

void bow_cont(  bow_plDat * dat,char const *  fil);
void bow_genDat(bow_plDat * dat);

void bow_sav(char const * fil,bow_plDat const * dat);
