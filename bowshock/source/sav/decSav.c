// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.h>

#include <zap/mem.h>

void bow_decSav(bow_savDat * buf,zap_i8 const * dat) {
	dat = zap_cp(&buf->fmtVer,     dat,0x8u).src;
	dat = zap_cp(&buf->cmdrNm,     dat,bow_cmdrNmLen).src;
	dat = zap_cp(&buf->tm,         dat,0x8u).src;
	dat = zap_cp(&buf->sysId,      dat,0x8u).src;
	dat = zap_cp(&buf->shipTyp,    dat,0x1u).src;
	dat = zap_cp(&buf->shipPosX,   dat,0x8u).src;
	dat = zap_cp(&buf->shipPosY,   dat,0x8u).src;
	dat = zap_cp(&buf->shipPosZ,   dat,0x8u).src;
	dat = zap_cp(&buf->shipRotX,   dat,0x8u).src;
	dat = zap_cp(&buf->shipRotY,   dat,0x8u).src;
	dat = zap_cp(&buf->shipRotZ,   dat,0x8u).src;
	dat = zap_cp(&buf->shipPosVelX,dat,0x8u).src;
	dat = zap_cp(&buf->shipPosVelY,dat,0x8u).src;
	dat = zap_cp(&buf->shipPosVelZ,dat,0x8u).src;
	dat = zap_cp(&buf->shipRotVelX,dat,0x8u).src;
	dat = zap_cp(&buf->shipRotVelY,dat,0x8u).src;
	      zap_cp(&buf->shipRotVelZ,dat,0x8u);
}
