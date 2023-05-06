// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <ly/io>
#include <ly/fs>
#include <cstdlib>
#include <stdexcept>

void ::bow::bow::cred() noexcept {
	char const * const pth = bow_datDir "/CREDITS.txt";

	::zp::siz const filsiz = [&pth]() {
		::ly::pthinf pthinf;
		::ly::sttpth(pthinf,pth);

		return pthinf.siz;
	}();

	::ly::fil fil;
	::ly::err err = fil.opn(pth,::ly::mod::red,::ly::kep);

	if (err != ::ly::err::ok) [[unlikely]] {
		bow_logErr("unable to open credits file");

		::std::exit(EXIT_FAILURE);
	}

	char * cred;

	try {cred = new char[filsiz + 0x3u];}
	catch (::std::bad_alloc const & e) {
		bow_logErr("unable to allocate memory");
		
		::std::exit(EXIT_FAILURE);
	}

	char * const credstart = cred;

	*cred++ = '\n';

	fil.red(cred,filsiz);
	fil.cls();
	cred += filsiz;

	*cred++ = '\n';
	*cred++ = '\x00';

	cred = credstart;

	::ly::dflout.wrt(cred,filsiz + 0x3u);

	if (err != ::ly::err::ok) {
		bow_logErr("unable to write to defout");

		::std::exit(EXIT_FAILURE);
	}

	delete[] cred;

	::std::exit(EXIT_SUCCESS);
}
