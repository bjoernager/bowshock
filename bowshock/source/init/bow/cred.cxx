// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <flux/io.h>
#include <cstdio>
#include <cstdlib>

void ::bow::bow::cred() noexcept {
	FILE * fp = ::std::fopen(bow_datDir "/CREDITS.txt","r");

	::std::fseek(fp,0x0,SEEK_END);
	::zap::sz const filsz = (::zap::sz)ftell(fp);
	::std::rewind(fp);

	char *       cred      = new char[filsz + 0x3u];
	char * const credstart = cred;

	if (cred == nullptr) {
		bow_logErr("unable to allocate memory");
		::std::exit(EXIT_FAILURE);
	}

	*cred++ = '\n';

	cred += ::std::fread(cred,sizeof (char),filsz,fp);
	::std::fclose(fp);

	*cred++ = '\n';
	*cred++ = '\x00';

	cred = credstart;

	::flux_err err = ::flux_wrstr(::flux_defout,cred);

	if (err) {
		bow_logErr("unable to write to defout");
	}

	delete[] cred;

	::std::exit(EXIT_SUCCESS);
}
