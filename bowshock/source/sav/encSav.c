// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.h>

#include <zap/mem.h>

void bow_encSav(zap_i8 * buf,bow_plDat const * const dat) {
	buf = zap_cp(buf,(zap_i04[0x1u]) {bow_savVer},0x8u).dest;         // fmtver
	buf = zap_cp(buf,dat->nm,                    bow_cmdrNmLen).dest; // cmdrnm
	buf = zap_cp(buf,&dat->tm,                   0x8u).dest;         // tm
	buf = zap_cp(buf,&dat->sysId,                0x8u).dest;         // sysId
	buf = zap_cp(buf,&dat->ship.shipTyp,         0x1u).dest;         // shipTyp
	buf = zap_cp(buf,&dat->ship.pos.x,           0x8u).dest;         // shipposx
	buf = zap_cp(buf,&dat->ship.pos.y,           0x8u).dest;         // shipposy
	buf = zap_cp(buf,&dat->ship.pos.z,           0x8u).dest;         // shipposz
	buf = zap_cp(buf,&dat->ship.rot.x,           0x8u).dest;         // shiprotx
	buf = zap_cp(buf,&dat->ship.rot.y,           0x8u).dest;         // shiproty
	buf = zap_cp(buf,&dat->ship.rot.z,           0x8u).dest;         // shiprotz
	buf = zap_cp(buf,&dat->ship.posVel.x,        0x8u).dest;         // shipposVelx
	buf = zap_cp(buf,&dat->ship.posVel.y,        0x8u).dest;         // shipposVely
	buf = zap_cp(buf,&dat->ship.posVel.z,        0x8u).dest;         // shipposVelz
	buf = zap_cp(buf,&dat->ship.rotVel.x,        0x8u).dest;         // shiprotVelx
	buf = zap_cp(buf,&dat->ship.rotVel.y,        0x8u).dest;         // shiprotVely
	      zap_cp(buf,&dat->ship.rotVel.z,        0x8u);              // shiprotVelz
}
