// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <flux/io.hh>
#include <flux/stats.hh>
#include <cstdlib>
#include <stdexcept>

void ::bow::bow::cred() noexcept {
	char const * const pth = bow_datDir "/CREDITS.txt";

	::zap::sz const filsz = [&pth]() {
		::flux::stats stats;
		::flux::stat(stats,pth);

		return stats.sz;
	}();

	::flux::fil fil;
	::flux::err err = fil.op(pth,::flux::md::rd,::flux::keep);

	if (err != ::flux::err::ok) [[unlikely]] {
		bow_logErr("unable to open credits file");

		::std::exit(EXIT_FAILURE);
	}

	char * cred;

	try {cred = new char[filsz + 0x3u];}
	catch (::std::bad_alloc const & e) {
		bow_logErr("unable to allocate memory");
		
		::std::exit(EXIT_FAILURE);
	}

	char * const credstart = cred;

	*cred++ = '\n';

	fil.rd(cred,filsz);
	fil.cl();
	cred += filsz;

	*cred++ = '\n';
	*cred++ = '\x00';

	cred = credstart;

	::flux::dflout.wr(cred,filsz + 0x3u);

	if (err != ::flux::err::ok) {
		bow_logErr("unable to write to defout");

		::std::exit(EXIT_FAILURE);
	}

	delete[] cred;

	::std::exit(EXIT_SUCCESS);
}
