#if !defined(bow_hdr_sav)
#define bow_hdr_sav

#include <bow/bs.h>

#include <zap/bs.h>

constexpr zap_i04 bow_savfmtver = 0x4u;

typedef struct {
	zap_i04 fmtver;
	char    cmdrnm[bow_cmdrnmlen];
	zap_i04 sysid;
	zap_i04 tm;
	bow_xyz shippos;
	bow_xyz shiprot;
	bow_xyz shipvel;
} bow_savdat;

void bow_cont(char const * fil,bow_playdat *       dat);
void bow_sav( char const * fil,bow_playdat const * dat);

#endif
