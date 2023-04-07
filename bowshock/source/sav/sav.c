// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.h>
#include <bow/sav.h>

#include <flux/io.h>

void bow_sav(char const * const pth,bow_plDat const * const plDat) {
	bow_log("saving commander %s at \"%s\"",plDat->nm,pth);
	
	flux_fil * fil;
	flux_err err = flux_mkfil(&fil,pth,0644);
	
	unlikely (err) {
		unlikely (err != flux_err_exist) {
			bow_logErr("unable to open save file \"%s\"",pth);
			bow_abrt();
		}
	
		err = flux_op(&fil,pth,flux_md_wr,flux_disc);
		unlikely (err) {
			bow_logErr("unable to create save file \"%s\"",pth);
			bow_abrt();
		}
	}
	
	zap_i8 dat[bow_savLen];
	bow_encSav(dat,plDat);
	
	flux_wr(fil,dat,bow_savLen);
	flux_cl(fil);
}
