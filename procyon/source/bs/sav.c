#include <acm/bs.h>

#include <flux.h>
#include <stdio.h>

void acm_sav(acm_pldat const * const _pldat) {
	acm_log("Saving\n");
	flux_err fluxerr;
	flux_fil savfil;
	fluxerr = flux_mkfil(&savfil,acm_dat.savloc,0644u);
	if (fluxerr) {
		if (fluxerr != flux_err_exist) {
			fprintf(stderr,"Unable to create save file (\"%s\"): %s\n",acm_dat.savloc,flux_errstr(fluxerr));
			acm_exit(acm_stat_err);
		}
		acm_log("Save file already exists, overwritting\n");
		fluxerr = flux_op(&savfil,acm_dat.savloc,flux_md_wr,flux_disc);
		if (fluxerr) {
			fprintf(stderr,"Unable to open save file: %s\n",flux_errstr(fluxerr));
			acm_exit(acm_stat_err);
		}
	}
	{
		uint_least64_t const savver = acm_savver;
		fluxerr = flux_wr(savfil,&savver,sizeof (savver));
	}
	if (!fluxerr) {
		fluxerr = flux_wr(savfil,_pldat,sizeof (*_pldat));
	}
	if (fluxerr) {
		fprintf(stderr,"Unable to write to save file: %s\n",flux_errstr(fluxerr));
		acm_exit(acm_stat_err);
	}
	flux_cl(savfil);
}
