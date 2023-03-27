#pragma once

#include <bow/bs.h>

#include <zap/bs.h>

constexpr zap_i04 bow_savver = 0x6u;

#define bow_savlen ((zap_sz)((zap_sz)0x79u+(zap_sz)bow_cmdrnmlen))

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
	zap_i04  fmtver;
	char     cmdrnm[bow_cmdrnmlen];
	zap_i04  tm;
	zap_i04  sysid;
	zap_i8   shiptyp;
	double   shipposx;
	double   shipposy;
	double   shipposz;
	double   shiprotx;
	double   shiproty;
	double   shiprotz;
	double   shipposvelx;
	double   shipposvely;
	double   shipposvelz;
	double   shiprotvelx;
	double   shiprotvely;
	double   shiprotvelz;
} bow_savdat;

void bow_cont(char const * fil,bow_playdat *       dat);
void bow_sav( char const * fil,bow_playdat const * dat);
