// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.h>

#include <flux/io.h>
#include <stdio.h>
#include <stdlib.h>

void bow_cred(void) {
	FILE * fp = fopen(bow_datDir "/CREDITS.txt","r");

	fseek(fp,0x0,SEEK_END);
	zap_sz const filsz = (zap_sz)ftell(fp);
	rewind(fp);

	char *       cred      = malloc(filsz + 0x3u);
	char * const credstart = cred;

	if (cred == nullptr) {
		bow_logErr("unable to allocate memory");
		exit(EXIT_FAILURE);
	}

	*cred++ = '\n';

	cred += fread(cred,sizeof (char),filsz,fp);
	fclose(fp);

	*cred++ = '\n';
	*cred++ = '\x00';

	cred = credstart;

	flux_err err = flux_wrstr(flux_defout,cred);

	if (err) {
		bow_logErr("unable to write to defout");
	}

	free(cred);

	exit(EXIT_SUCCESS);
}
