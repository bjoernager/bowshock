#include <acm/bs.h>

#include <flux.h>
#include <inttypes.h>
#include <zap/mem.h>

static_assert(sizeof (acm_dflplnm) == acm_plnmlen);

void acm_cont(acm_pldat * const _pldat) {
	acm_log("Continuing\n");
	acm_pldat      pldat;
	uint_least64_t savver;
	flux_err fluxerr;
	flux_fil savfil;
	fluxerr = flux_op(&savfil,acm_dat.savloc,flux_md_rd,flux_keep);
	if (fluxerr) {
		acm_log("Unable to open save file, starting new game: %s\n",flux_errstr(fluxerr));
		goto new;
	}
	fluxerr = flux_rd(savfil,sizeof (savver),&savver,nullptr);
	if (!fluxerr) {
		fluxerr = flux_rd(savfil,sizeof (pldat),&pldat,nullptr);
	}
	flux_cl(savfil);
	if (fluxerr) {
		acm_log("Unable to read save file, starting new game: %s\n",flux_errstr(fluxerr));
		goto new;
	}
	if (savver != acm_savver) {
		printf("Old save version (%" PRIXLEAST64 "), starting new game: %s\n",savver,flux_errstr(fluxerr));
		goto new;
	}
	acm_log("Validating commander name\n");
	bool validnm = false;
	for (zap_sz n = 0x0u;n < acm_plnmlen + 0x1u;++n) {
		if (pldat.nm[n] == '\x0') {
			if (n == 0x0u) {
				break;
			}
			validnm = true;
			break;
		}
	}
	if (!validnm) {
		acm_log("Invalid commander name (corrupt save file), starting new game\n");
		acm_log(
			"Commander name:\n"
			"    %hhX %hhX %hhX %hhX\n"
			"    %hhX %hhX %hhX %hhX\n"
			"    %hhX %hhX %hhX %hhX\n"
			"    %hhX %hhX %hhX %hhX\n"
			"    %hhX\n",
			pldat.nm[0x0u],pldat.nm[0x1u],pldat.nm[0x2u],pldat.nm[0x3u],
			pldat.nm[0x4u],pldat.nm[0x5u],pldat.nm[0x6u],pldat.nm[0x7u],
			pldat.nm[0x8u],pldat.nm[0x9u],pldat.nm[0xAu],pldat.nm[0xBu],
			pldat.nm[0xCu],pldat.nm[0xDu],pldat.nm[0xEu],pldat.nm[0xFu],
			pldat.nm[0x10u]
		);
		goto new;
	}
	printf("Loaded CMDR %s, %s @ %" PRIiLEAST64 "\n",pldat.nm,acm_shipnm(pldat.ship),pldat.tm);
	*_pldat = pldat;
	return;
new:;
	pldat.heat   = 0x120u; /* 288K */
	pldat.pos.px = 0x0u;
	pldat.pos.py = 0x0u;
	pldat.pos.pz = 0x0u;
	pldat.pos.rx = 0x0u;
	pldat.pos.ry = 0x0u;
	pldat.pos.rz = 0x0u;
	pldat.pos.vx = 0x0u;
	pldat.pos.vy = 0x0u;
	pldat.pos.vz = 0x0u;
	pldat.ship   = acm_ship_side;
	pldat.tm     = 0x9679C2B40u; /* 3250-01-01T12:00:00Z */
	zap_memcp(acm_dflplnm,acm_plnmlen + 0x1u,pldat.nm);
	*_pldat = pldat;
}
